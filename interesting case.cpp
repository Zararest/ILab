#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <sys/stat.h>

const int MAXLEN = 400;

void zero_char(char str[MAXLEN])
{
    int i = 0;

    for (i = 0; i < MAXLEN; i++)
    {
        str[i] = '\0';
    }

}


void str_to_normstr(char str[MAXLEN], char str_f[MAXLEN])
{

    int i = 0, j = 0;

    while (str[i] != '\0')
    {
        if ( ( (str[i] >= 'A') && (str[i] <= 'Z') ) || ( (str[i] >= 'a') && (str[i] <= 'z') ) || ( (str[i] >= '0') && (str[i] <= '9') ) )
        {
            str_f[j] = str[i];
            j++;
        }
        i++;
    }

    return ;
}


int my_strcmp(char str1[MAXLEN], char str2[MAXLEN])
{
    int i = 0;
    char str1_form[MAXLEN] = {'\0'}, str2_form[MAXLEN] = {'\0'};

    str_to_normstr( str1, str1_form );
    str_to_normstr( str2, str2_form );

    while ( (str1_form[i] == str2_form[i]) && ( str1_form[i] != '\0' ) && ( str2_form[i] != '\0' ) )
    {
        i++;
    }


    if ( (str1_form[i] == '\0') && (str2_form[i] == '\0') )
    {
        return 0;
    } else
    {
        if ( str1_form[i] > str2_form[i] )
        {
            return 1;
        } else
        {
            return -1;
        }

    }

}

void gachi_sort(char** mas_of_str, int kol_str)
{
    char* tmp;
    int i = 0, j = 0;

    for (j = 0; j < kol_str; j++)
    {
        for (i = 0; i < (kol_str - 1); i++)
        {
            if (my_strcmp(mas_of_str[i], mas_of_str[i + 1]) == 1)
            {
                tmp = mas_of_str[i];
                mas_of_str[i] = mas_of_str[i + 1];
                mas_of_str[i + 1] = tmp;
            }
        }
    }
}


void my_insert(char from_str[MAXLEN], char* to_str)
{
    int i = 0;

    while ( (from_str[i] != '\0') && (i < MAXLEN) )
    {
        to_str[i] = from_str[i];
        i++;
    }
}

void file_sort(char name_of_input_file[MAXLEN], char name_of_output_file[MAXLEN])
{
    FILE* p_input = fopen(name_of_input_file, "r");
    FILE* p_output = fopen(name_of_output_file, "w");
    char symbol = '-1';
    char** mas_of_point = NULL;
    char str[MAXLEN] = {'\0'};
    char* point_str = NULL;
    int i = 0, num_of_str = 0;
    struct stat statistika = {0};

    if ( p_input == NULL)
    {
        printf("Can't find such input file\n"
               "Please, enter file name, where the novel is\n");
        scanf("%s", name_of_input_file);
    }
    while ( (p_input = fopen(name_of_input_file, "r")) == NULL)
    {
        printf("Try again or enter <I'm too stupid for this> in order to stop program\n");
        scanf("%s", name_of_input_file);
        if (name_of_input_file == "I'm too stupid for this")
        {
            exit(0);
        }
    }
    if ( stat(name_of_input_file, &statistika) == -1 )
    {
        printf("Something went wrong(((\n");
        exit(1);
    }
    if ( p_output == NULL)
    {
        printf("Sorry, but this program can't print a novel to a file\n");
        exit(0);
    }
    if ( statistika.st_size == 0 )
    {
        printf("This bitch(file) is empty\n"
               "YEET");
        exit(0);
    }


    while ( symbol != EOF )
    {
        symbol = fgetc(p_input);

        if ( (symbol != '\n') && (symbol != EOF) )
        {
            if (i > (MAXLEN - 1))
            {
                printf("The string N%i  is too long", num_of_str);
                exit(-1);
            }
            str[i] = symbol;
            i++;
        } else
        {
            point_str = (char*) calloc(i + 2, sizeof(char) );

            my_insert(str, point_str);

            point_str[i] = '\n';
            point_str[i + 1] = '\0';

            mas_of_point = (char**) realloc(mas_of_point, (num_of_str + 1)*sizeof(char*));
            if (mas_of_point == NULL)
            {
                printf("this bitch(RAM) is empty\n"
                       "YEET\n");
                exit(1);
            }

            mas_of_point[num_of_str] = point_str;

            num_of_str++;
            i = 0;
            zero_char(str);
        }


    }

    gachi_sort(mas_of_point, num_of_str);

    for (i = 0; i < num_of_str; i++)
    {
        fprintf(p_output, "%s", mas_of_point[i]);
    }

    fclose(p_input);
    fclose(p_output);
}




int main ()
{
    char name_of_input_file[MAXLEN], name_of_output_file[MAXLEN];

    printf("Do you want to sort the novel 'Eugene Onegin'?\n"
           "(Press ENTER to do that)\n");

    while ( getchar() != '\n' )
    {
        printf("Press 'F' to pay respect to Pushkin\n");
    }

    printf("Now enter file name, where the novel is\n");
    scanf("%s", name_of_input_file );

    printf("Where do you want to put the modified novel?\n");
    scanf("%s", name_of_output_file);


    file_sort(name_of_input_file, name_of_output_file);


    return 0;
}
