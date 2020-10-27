#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <sys/stat.h>
#include <math.h>

const int MAXLEN = 400;


struct note
{
    char* inf;
    struct note* p;
};

int len_str(char* val)
{
    int i = 0;

    while (val[i] != '\0')
    {
        i++;
    }
    i++;

    return i;
}

void my_copy(char* from, char* to)
{
    int i = 0;

    while (from[i] != '\0')
    {
        to[i] = from[i];
        i++;
    }
    i++;
    to[i] = '\0';
}


int my_strcmp(char* str1, char* str2)
{
    int i = 0;

    while ( (str1[i] == str2[i]) && ( str1[i] != '\0' ) && ( str2[i] != '\0' ) )
    {
        i++;
    }

    if ( (str1[i] == '\0') && (str2[i] == '\0') )
    {
        return 0;
    } else
    {
        if ( str1[i] > str2[i] )
        {
            return 1;
        } else
        {
            return -1;
        }

    }
}


void add_to_mas(int pos_of_val, struct note **root_of_mas, char* val)
{
    struct note* tmp = (struct note*) calloc (1, sizeof(struct note));
    struct note* point = (struct note*) calloc (1, sizeof(struct note));
    char* val_tmp = (char*) calloc (len_str(val) + 1, sizeof(char));
    int i = 0;

    my_copy(val, val_tmp);

    if (pos_of_val == 1)
    {
        tmp->inf = val_tmp;
        tmp->p = *root_of_mas;

        *root_of_mas = tmp;

    } else
    {
        point->p = *root_of_mas;

        for (i = 1; i < pos_of_val; i++)
        {
            if (point->p != NULL)
            {
                point = point->p;
            } else
            {
                printf("in add_mas stop when i == %i\n", i);
            }
        }

        tmp->p = point->p;
        tmp->inf = val_tmp;
        point->p = tmp;

    }

}




void insert_and_del(int from, int to, struct note **root_of_mas)
{
    struct note* tmp = (struct note*) calloc (1, sizeof(struct note ));
    struct note* point = (struct note*) calloc (1, sizeof(struct note ));
    struct note* point_tmp = (struct note*) calloc (1, sizeof(struct note ));
    char* val = NULL;
    int i = 0;

    if (from == 1)
    {
        point->p = *root_of_mas;
        point = point->p;

        val = point->inf;
        *root_of_mas = point->p;
    } else
    {
        point->p = *root_of_mas;

        for (i = 1; i < from; i++)
        {
            if (point->p != NULL)
            {
                point = point->p;
            } else
            {
                printf("in insert_and_del() smt went wrong on i = %i\n", i);
                point->inf = 0;
            }

        }

        point_tmp = point->p;
        val = point_tmp->inf;
        point->p = point_tmp->p;

        free(point_tmp);
    }


    add_to_mas(to, root_of_mas, val);

}

char* val(int num_of_val, struct note **root_of_mas)
{
    struct note* point;
    int i;

    point = (struct note*) calloc (1, sizeof(struct note));

    point->p = *root_of_mas;

    for (i = 1; i <= num_of_val; i++)
    {
        if (point->p != NULL)
        {
            point = point->p;
        } else
        {
            printf("in val() smt went wrong on i = %i\n", i);
            point->inf = 0;
        }

    }

    return point->inf;
}

void print_list(int from, int to, struct note **root_of_mas)
{
    int i = 1;

    for (i = from; i <= to; i++)
    {
        printf("%i elem in print = |%s|\n", i, val(i, root_of_mas));
    }
}

void sort_my(int sort_from, int sort_to, struct note **root_of_mas)
{

    int main_num = round( (sort_from + sort_to)/2 );
    char* main_val = val(main_num, root_of_mas);
    int i = 0;

    if (sort_to > (sort_from + 1) )
    {
        for (i = sort_from; i < main_num; i++)
        {

            if ( my_strcmp( val(i, root_of_mas), main_val ) == 1 )
            {
                if ( (main_num + 1) > sort_to )
                {
                    insert_and_del(i, main_num - 1, root_of_mas);
                } else
                {
                    insert_and_del(i, main_num, root_of_mas);
                }
                main_num--;
                i--;
            }
        }


        for (i = (main_num + 1); i <= sort_to; i++)
        {

            if ( my_strcmp( val(i, root_of_mas), main_val) == -1 )
            {
                if ( (main_num - 1) < sort_from)
                {
                    insert_and_del(i, main_num, root_of_mas);
                } else
                {
                    insert_and_del(i, main_num - 1, root_of_mas);
                }
                main_num++;
            }
        }

        sort_my(sort_from, (main_num - 1), root_of_mas);
        sort_my( (main_num), sort_to, root_of_mas);
    } else
    {
        if (sort_to == (sort_from + 1))
        {
            if ( my_strcmp( val(sort_from, root_of_mas), val(sort_to, root_of_mas)) == 1)
            {
                insert_and_del(sort_from, (sort_from + 1), root_of_mas );
            }
        }
    }



}

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



void my_insert(char from_str[MAXLEN], char* to_str)
{
    int i = 0;

    while ( (from_str[i] != '\0') && (i < MAXLEN) )
    {
        to_str[i] = from_str[i];
        i++;
    }
}

void fprint_list(int from, int to, struct note **root_of_mas, char name_of_output_file[MAXLEN])
{
    int i = 1;
    FILE* p_output = fopen(name_of_output_file, "w");
    struct note* point = (struct note*) calloc (1, sizeof(struct note));

    if ( p_output == NULL)
    {
        printf("Sorry, but this program can't print a novel to a file\n");
        exit(0);
    }
    if (point == NULL)
    {
        printf("smt wrong with memory\n");
        exit(1);
    }
    if (*root_of_mas == NULL)
    {
        printf("list of lines is empty\n");
        exit(0);
    }
    point->p = *root_of_mas;

    for (i = 1; i <= to; i++)
    {
        if (point->p != NULL)
        {
            point = point->p;
            fprintf(p_output, "%s", point->inf);
        } else
        {
            printf("in val() smt went wrong on i = %i\n", i);
            point->inf = 0;
        }

    }

    fclose(p_output);
}


void file_sort(char name_of_input_file[MAXLEN], char name_of_output_file[MAXLEN])
{
    FILE* p_input = fopen(name_of_input_file, "r");

    char symbol = '-1';
    struct note* mas_of_point = NULL;
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

            add_to_mas(1, &mas_of_point, point_str);
            num_of_str++;
            i = 0;
            zero_char(str);
        }


    }

    sort_my(1, num_of_str, &mas_of_point);

    fprint_list(1, num_of_str, &mas_of_point, name_of_output_file);

    fclose(p_input);

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
