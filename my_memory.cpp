#include <stdio.h>
#include <stdlib.h>

class Memory
{
public:

    void* calloc_class(int num_of_elem, int size_of_elem)
    {
        char* tmp = (char*)calloc(num_of_elem * size_of_elem + 2 * sizeof(char), 1);
        tmp[0] = 'F';
        tmp[num_of_elem * size_of_elem + 1] = 'F';
        void* tmp_void = (void*) ( tmp + 1 );


        mas_of_canary = (char**) realloc(mas_of_canary, (canary_count + 2)*sizeof(char*));
        mas_of_canary[canary_count] = &tmp[0];
        mas_of_canary[canary_count + 1] = &tmp[num_of_elem * size_of_elem + 1];

        canary_count++;
        canary_count++;

        return tmp_void;

    }

    void* realloc_class(void* prev_point, int num_of_byte)
    {
        int num_of_prev_canary = 0;
        char* prev_pre_canary = 0;
        char* prev_post_canary = 0;
        char* new_line = NULL;
        void* tmp_void;


        while ( (((char*) prev_point) - 1)  != mas_of_canary[num_of_prev_canary])
        {
            num_of_prev_canary++;
        }

        new_line = (char*) realloc(prev_point - 1, num_of_byte + 2);

        new_line[0] = 'F';
        new_line[num_of_byte + 1] = 'F';


        mas_of_canary[num_of_prev_canary] = &new_line[0];
        mas_of_canary[num_of_prev_canary + 1] = &new_line[num_of_byte + 1];
        tmp_void = (void*) (new_line + 1);

        return tmp_void;
    }

    void free_class(void* point)
    {
        char* char_point = (char*) point;
        int num_of_prev_canary = 0;

        if (  *(char_point - 1) == 'F' )
        {
            while ( (((char*) point) - 1)  != mas_of_canary[num_of_prev_canary])
            {
                num_of_prev_canary++;
            }

            mas_of_canary[num_of_prev_canary] = NULL;
            mas_of_canary[num_of_prev_canary + 1] = NULL;

            free(char_point - 1);
        } else
        {
            printf("guys, we have some problems with free().\n"
                   "This function work only with memory, witch was created by my_calloc or my_realloc\n ");
        }
    }

    int light_check()
    {
        int i = 0;
        int mas_of_err[canary_count] = {0};
        int num_of_err = 0;

        printf("in check can count = %i\n", canary_count);
        for (i = 0; i < canary_count; i++)
        {
            if ( (*mas_of_canary[i] != 'F') && (*mas_of_canary[i] != NULL) )
            {
                num_of_err++;
                mas_of_err[i] = 1;
            }
        }

        if (num_of_err != 0)
        {
            FILE* file_of_err = fopen("errors.txt", "w");
            fprintf(file_of_err, "Pre_canary - canary, which stands before memory\n");
            fprintf(file_of_err, "Post_canary - canary, which stands after memory\n");

            fprintf(file_of_err, "The total number of deaths of Canaries is:|%i|\n", num_of_err);
            for (i = 0; i <= canary_count; i++)
            {

                if ((mas_of_err[i] = 1) && ( (i % 2) == 0) )
                {
                    fprintf(file_of_err, "The pre_canary number[%i] didn't survive your shit-code\n\n", i/2 + 1);
                }

                if ((mas_of_err[i] = 1) && ( (i % 2) == 1) )
                {
                    fprintf(file_of_err, "The post_canary number[%i] died in agoni\n\n", i/2 + 1);
                }
            }
            exit(1);
        }
    }

private:
    static char** mas_of_canary;
    static int canary_count;
};

char** Memory::mas_of_canary{ NULL };
int Memory::canary_count{ 0 };


void my_free(void* point)
{
    Memory tmp;
    tmp.free_class(point);
}

void check()
{
    Memory tmp;
    tmp.light_check();
}

void* my_calloc(int num_of_elem, int size_of_elem)
{
    Memory tmp;
    return tmp.calloc_class(num_of_elem, size_of_elem);
}

void* my_realloc(void* prev_point, int num_of_byte)
{
    Memory tmp;
    return tmp.realloc_class(prev_point, num_of_byte);
}



main()
{
    Memory start;
    float* start_char;
    char* test;
    int start_int;
    FILE* p_input = fopen("romeo.txt", "r");
    char symbol = '-1';
    char* buffer;
    int i = 0;
    FILE* p_output = fopen("test_output.txt", "w");

    test = (char*) my_calloc(10, sizeof(char));

    check();
    buffer = (char*) my_calloc(1, sizeof(char));

    while ( symbol != EOF )
    {
        check();

        printf("------i love DRAM i = |%d|\n", i);
        symbol = fgetc(p_input);
        test = (char*) my_calloc(10, sizeof(char));
        buffer = (char*) my_realloc(buffer, (i + 3) * sizeof(char) );
        buffer[i] = symbol;
        i++;
    }

    buffer[i] = '\0';
    i = 0;

    while (buffer[i] != '\0')
    {
        fprintf(p_output, "%c", buffer[i]);
        i++;
    }

    fclose(p_output);
    fclose(p_input);
    free(buffer);


}

