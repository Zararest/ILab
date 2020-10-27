#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


int my_strcmp(char* str1, char* str2) //������ ��������� �����
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


void add_to_mas(int pos_of_val, struct note **root_of_mas, char* val) //��������� ������� � ������ �� ����� pos_of_val
{
    struct note* tmp = (struct note*) calloc (1, sizeof(struct note));
    struct note* point = (struct note*) calloc (1, sizeof(struct note));
    char* val_tmp = (char*) calloc (len_str(val), sizeof(char));
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




void insert_and_del(int from, int to, struct note **root_of_mas)//� ������� from ��������� ������� �� ����� to
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

char* val(int num_of_val, struct note **root_of_mas)//�������� �������� �� num_of_val
{
    struct note* point;
    int i;

    point = (struct note*) calloc (1, sizeof(struct note  ));

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

void sort_my(int sort_from, int sort_to, struct note **root_of_mas)// ��������� ������ � ��������� �� sort_from �� sort_to
{

    int main_num = round( (sort_from + sort_to)/2 );//����� ������� ������� ��� �������
    char* main_val = val(main_num, root_of_mas);
    int i = 0;

    if (sort_to > (sort_from + 1) )//���� ��������� ������ 2 ��������� ��
    {
        for (i = sort_from; i < main_num; i++)//� ������(����������) ������� �������� ��� �������� ����� �� �������
        {

            if ( my_strcmp( val(i, root_of_mas), main_val ) == 1 )//���� ������� ������ �������� �� ������������ ��� ������
            {
                if ( (main_num + 1) > sort_to )//��������� ��� ����(� �� ����� �������������) ������������ ������� ���������� � �������� �� ��� �������������
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


        for (i = (main_num + 1); i <= sort_to; i++)//���������� ��� ��������� ������ ��
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

        sort_my(sort_from, (main_num - 1), root_of_mas);//��������� ��� �� ������� ��� ����� �����
        sort_my( (main_num), sort_to, root_of_mas);//��������� ��� ������ �����
    } else
    {
        if (sort_to == (sort_from + 1))//������ ��� ���������� 2 ���������
        {
            if ( my_strcmp( val(sort_from, root_of_mas), val(sort_to, root_of_mas)) == 1)
            {
                insert_and_del(sort_from, (sort_from + 1), root_of_mas );
            }
        }
    }



}

main()
{
    FILE* fp = fopen("input.txt", "r");
    struct note* point_mas = NULL;
    char* str = (char*) calloc (10, sizeof(char));
    int i = 0;

    for (i = 1; i <= 9; i++)
    {
        fscanf(fp, "%s", str);
        add_to_mas(i, &point_mas, str);
        printf("scan is ok i == %i str == |%s|\n", i ,str);
    }

    sort_my(1, 9, &point_mas);

    printf("------in main print------\n");
    print_list(1, 9, &point_mas);

    fclose(fp);
}
