#include <stdio.h>
#include <stdlib.h>


const int MAXLEN = 10;
const int MAX_NUM_OF_VAL = 4;
const int MAX_OF_MAXLEN = 50; //MAX_NUM_OF_VAL * MAXLEN

/////----------------------------------------

const int LEN_DELIM = 9;
const char delim[LEN_DELIM] = {',', '.', '!', '?', ';', ':', ' ', '\0', '\n'};

int pos(char, char);
int my_strcmp(char, char);
void str_to_normstr(char, char);
char my_strcat(char, char );
char my_strtok(char, const char );
int zero_matrix(char, int, int );
void my_matr_print(char, int);


int pos(char elem, const char delim[LEN_DELIM])
{
    int i = 0, exist_in_delim = 0;

    while  (i <= LEN_DELIM-1)
    {
        if (delim[i] == elem)
        {
            exist_in_delim = 1;
        }
        i++;
    }

    return exist_in_delim;
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

char * my_strcat(char fir_part[MAXLEN], char sec_part[MAXLEN])
{
    int i = 0;
    int len_fir_part = 0;

    while (fir_part[len_fir_part] != '\0')
    {
        len_fir_part++;
    }


    for (i = 0; sec_part[i] != '\0'; i++)
    {
        fir_part[len_fir_part +  i] = sec_part[i];
        printf("fir_part %i = %c \n", i + len_fir_part, fir_part[len_fir_part + i] );

    }
    fir_part[len_fir_part + i] = '\0';

    return fir_part;
}


char * my_strtok(char str[MAXLEN], const char delim[LEN_DELIM])
{
    static int pos_poin = 0;

    int i = 0;
    char * output = (char*) calloc(MAXLEN, sizeof(char));

    if ( (str == NULL) || ( (pos_poin != 0) && (str[pos_poin - 1] == '\0') ) )
    {
        pos_poin = 0;
        return NULL;
    }


    while  ( pos( str[pos_poin], delim ) == 0 )
    {
        output[i] = str[pos_poin];
        i++;
        pos_poin++;

    }

    output[i] = '\0';
    pos_poin++;

    return output;
}

/////-----------------------------------------


void my_matr_print(char str[][MAXLEN], int y)
{
    int i = 0;

    while ( (str[y][i] != '\0') && (i <= MAXLEN - 1) )
    {
        printf("%c", str[y][i]);
        i++;
    }

    return;
}

void zero_matrix(char* matrix, int size_y, int size_x)
{
    int y = 0, x = 0;

    for (y = 0; y <= size_y - 1; y++)
    {
        for (x = 0; x <= size_x - 1; x++)
        {
            *(matrix + y*size_x + x) = '0';
        }
    }

    return ;
}


void my_insert(char* str1, char str2[MAXLEN], int point)
{
    int i = 0, j = 0;

    for (i = point; i <= point + MAXLEN; i++)
    {
        str1[i] = str2[j];

        j++;
    }
}




char* my_gets(char instruction[][MAXLEN], int number_of_instr, int *num_of_val )
{
    char stop_s[10] = {'s', 't', 'o', 'p'};
    char str[MAXLEN];
    char* results;
    int i = 0;

    printf("in func num_of_val before= %i \n", *num_of_val);
    while ( (i <= MAX_NUM_OF_VAL) && ( my_strcmp(str, stop_s) != 0 ) )
    {
        if (i <= number_of_instr)
        {
            my_matr_print(instruction, i);
            printf("\n");
        }

        scanf("%s", str);

        if ( my_strcmp(str, stop_s) != 0 )
        {
            (*num_of_val)++;

            if (i == 0)
            {
                results = (char*)calloc ( MAXLEN, sizeof(char));

                my_insert(results, str, MAXLEN*i);
            } else
            {
                results = (char*)realloc( results, MAXLEN*sizeof(char));

                my_insert(results, str, MAXLEN*i);
            }
        }


        i++;
    }
    printf("in func num_of_val = %i and i = %is\n", *num_of_val, i);

    return results;
}


main()
{
    int x = 0, y = 0;
    int len = MAXLEN;
    int num_of_val = 0;
    char instruction[MAX_NUM_OF_VAL][MAXLEN];
    char* res;
    int i = 0, j = 0;

    zero_matrix( (char*) instruction, MAX_NUM_OF_VAL, len);

    res = my_gets(instruction, 3, &num_of_val); //instruction - матрица с инструкциями, которые выводятся перед считыванием значения, 3 - кол-во инструкций, num_of_val - количество считанных значений

    printf("||num_of_val = %i||\n", num_of_val );

    for (i = 0; i <= num_of_val - 1; i++ )
    {
        j = 0;
        while (res[i*MAXLEN + j] != '\0')
        {
            printf("%c", res[i*MAXLEN + j]);
            j++;
        }
        printf("\n");
    }
}
