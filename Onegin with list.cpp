#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <sys/stat.h>
#include <math.h>
#include <clocale>

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


int str_len(char* str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int my_strcmp_rev(char* str1, char* str2)
{
    int i = 0, j =0;
    i = str_len(str1);
    j = str_len(str2);

    while ( (str1[i] == str2[j]) && ( j > 0 ) && ( i > 0 ) )
    {
        i--;
        j--;
    }

    if ( (i == 0) && (j == 0) )
    {
        return 0;
    } else
    {
        if (i == 0)
        {
            return 1;
        }

        if (j == 0)
        {
            return -1;
        }


        if ( ( str1[i] > str2[j] ) && (i != 0) && (j != 0) )
        {
            return 1;
        }
        if ( ( str1[i] <= str2[j] ) && (i != 0) && (j != 0) )
        {
            return -1;
        }

    }

}


void add_to_mas(int pos_of_val, struct note **root_of_mas, char* val)
{
    struct note* tmp = (struct note*) calloc (1, sizeof(struct note));
    struct note* point = (struct note*) calloc (1, sizeof(struct note));
    //char* val_tmp = (char*) calloc (len_str(val) + 1, sizeof(char));
    int i = 0;

    //my_copy(val, val_tmp);

    if (pos_of_val == 1)
    {
        tmp->inf = val;
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
        tmp->inf = val;
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



void sort_my_reverse(int sort_from, int sort_to, struct note **root_of_mas)
{

    int main_num = round( (sort_from + sort_to)/2 );
    char* main_val = val(main_num, root_of_mas);
    int i = 0;

    if (sort_to > (sort_from + 1) )
    {
        for (i = sort_from; i < main_num; i++)
        {

            if ( my_strcmp_rev( val(i, root_of_mas), main_val ) == 1 )
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

            if ( my_strcmp_rev( val(i, root_of_mas), main_val) == -1 )
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

        sort_my_reverse(sort_from, (main_num - 1), root_of_mas);
        sort_my_reverse( (main_num), sort_to, root_of_mas);
    } else
    {
        if (sort_to == (sort_from + 1))
        {
            if ( my_strcmp_rev( val(sort_from, root_of_mas), val(sort_to, root_of_mas)) == 1)
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
    char *locale = setlocale( LC_ALL,"Russian" );
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
            fprintf(p_output, "%s\n", point->inf);
        } else
        {
            printf("in val() smt went wrong on i = %i\n", i);
            point->inf = 0;
        }

    }

    fclose(p_output);
}


void file_sort(char name_of_input_file[MAXLEN], char name_of_output_file[MAXLEN], int sort_type)
{
    char *locale = setlocale( LC_ALL,"Russian" );
    FILE* p_input = fopen(name_of_input_file, "r");

    int i = 0, num_of_str = 0;
    struct stat statistika;

    stat(name_of_input_file, &statistika);
    printf("stat == %i\n", statistika.st_size + 1);
    char* buffer = (char*) calloc(statistika.st_size + 1, sizeof(char));
    char symbol = '-1';
    struct note* mas_of_point = NULL;
    char* point_str = &buffer[0];




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

            buffer[i] = symbol;
            i++;
        } else
        {
            printf("i love DRAM\n");
            buffer[i] = '\0';
            i++;

            add_to_mas(1, &mas_of_point, point_str);
            num_of_str++;

            point_str = &buffer[i];

        }


    }

    if (sort_type == 1)
    {
        sort_my(1, num_of_str, &mas_of_point);
    } else
    {
        printf("==%i==", sort_type);
        sort_my_reverse(1, num_of_str, &mas_of_point);
    }


    fprint_list(1, num_of_str, &mas_of_point, name_of_output_file);

    fclose(p_input);

}


int main ()
{
    char *locale = setlocale(LC_ALL, "Russian");
    char name_of_input_file[MAXLEN], name_of_output_file[MAXLEN];
    char input_check;
    int sort_type = 1;

    printf("Do you want to sort the novel 'Eugene Onegin'?\n"
           "(Press ENTER to do that)\n");

    while ( getchar() != '\n' )
    {
        printf("Press ENTER to pay respect to Pushkin\n");
    }

    printf("How do you want to sort novel?\n"
           "Type 'b' to sort from the beginning or 'e' to sort from the end\n");

    scanf("%c", &input_check);
    while ( (input_check != 'b') && (input_check != 'e'))
    {
        printf("This program can't sort novel like |%c|\n", input_check);
        printf("Please, try again\n");
        scanf("%c", &input_check);
    }

    if (input_check == 'b')
    {
        sort_type = 1;
    } else
    {
        sort_type = -1;
    }

    printf("Now enter file name, where the novel is\n");
    scanf("%s", name_of_input_file );

    printf("Where do you want to put the modified novel?\n");
    scanf("%s", name_of_output_file);

    file_sort(name_of_input_file, name_of_output_file, sort_type);

    return 0;
}
