#include <stdio.h>
#include <math.h>

#define MAXLEN 100
#define FALSE 0
#define TRUE 1
#define NUMBER_OF_TESTS 7

int check(char, double);
double powe(double, int);
double to_float(char, double);
int solve(double, double, double, double, double);
double aprox(double);


double powe(double bas, int step)
{
    double rez = 1;
    int i = 1;

    if (step > 0)
    {
        for (i = 1; i <= step; i++)
        {
            rez = bas*rez;
        }
    }


    if (step < 0)
    {
        for (i = 1; i <= -step; i++)
        {
            rez = rez/bas;
        }
    }


    if (step = 0)
    {
        rez = 1;
    }

    return rez;
}

double to_float(char str[MAXLEN], double rez)
{
    int dot_pos = 0;
    int len = 0;
    int j, digit_of_str;


    while (str[len] != '\0')
    {
        if (str[len] == '.')
        {
            dot_pos = len;
        }
        len++;
    }


    if (dot_pos == 0)
    {
      dot_pos = len;
      str[len] = '.';
      str[len+1] = '0';

    }

    rez = 0;


    for (j = 1; j <= len-dot_pos-1; j++)
    {
        digit_of_str = str[j+dot_pos] - '0';
        rez = digit_of_str * powe(10, -j) + rez;
    }

    for (j = 0; j <= dot_pos - 1; j++)
    {
        digit_of_str = str[dot_pos - j - 1] - '0';
        rez = digit_of_str * powe(10, j) + rez;
    }

    return rez;

}


int check(char str[MAXLEN],double *rez)
{
    int flag;
    int i;
    int sign_of_str=1;


    if (str[0] == '-')
    {
        for (i=0; str[i+1] != '\0'; i++)
        {
            str[i] = str[i+1];
        }

        str[i]='\0';
        sign_of_str = -1;
    }


    flag = FALSE;
    for (i = 0; str[i+1] != '\0'; i++)
    {
        if ( ( str[i] < '0' || str[i] > '9' ) && ( str[i] != '.' ) )
        {
            flag = TRUE;
        }
    }



    if (flag == TRUE)
    {
        return 1;
    } else
    {
        *rez = sign_of_str * to_float(str, *rez);

        return 0;
    }

}

double aprox(double x)
{
    if (abs(x) < 0.0001)
    {
        return 0;
    } else
    {
        return x;
    }
}

int solve(double a, double b, double c, double *x1, double *x2)
{
    double deskr;

    deskr=b*b - 4*a*c;

    if (a != 0 && aprox(deskr) > 0)
    {
        *x1 = (-b - sqrt( deskr )) / (2*a);
        *x2 = (-b + sqrt( deskr )) / (2*a);
        return 2;
    }

    if (a != 0 && aprox(deskr) == 0)
    {
        *x1=-b / (2*a);
        return 1;
    }

    if (a != 0 && deskr < 0)
    {
        return 0;
    }

    if (a == 0 && b == 0 && c == 0)
    {
        return 3;
    }

    if (a == 0 && b == 0 && c != 0)
    {
        return 0;
    }

    if (a == 0 && b != 0 )
    {
        *x1 = -c / b;
        return 1;
    }

}


void test_unit(void)
{
    int i;
    double x1, x2;
    int test_num[NUMBER_OF_TESTS], flag = 0;


    for (i=0; i<=NUMBER_OF_TESTS; i++)
    {
        test_num[i] = 0;
    }


    if (  ( solve(4, -5, -6, &x1, &x2) != 2 ) ||  ( x1 != -0.75 ) || ( x2 != 2 )  )
    {
        test_num[0] = 1;
        flag = 1;

    }

    if (   (solve(0, -5, -6, &x1, &x2 ) != 1 ) || ( x1 != -1.2 ) )
    {
        test_num[1] = 1;
        flag = 1;
    }

    if (   (solve(0, -5, 0, &x1, &x2 ) != 1 ) || ( x1 != 0 )  )
    {
        test_num[2] = 1;
        flag = 1;
    }

    if (   (solve(0, 0, -1, &x1, &x2 ) != 0 ) )
    {
        test_num[3] = 1;
        flag = 1;
    }

    if (  (solve(0, 0, 0, &x1, &x2 ) != 3 ) )
    {
        test_num[4] = 1;
        flag = 1;
    }

    if (   (solve(1, 4, 4, &x1, &x2 ) != 1 ) || ( x1 != -2 ) )
    {
        test_num[5] = 1;
        flag = 1;
    }

    if (flag == 1)
    {
        printf("This program has failed tests N:");
    } else
    {
        printf("All tests passed successfully");
    }


    for (i = 0; i <= NUMBER_OF_TESTS; i++)
    {
        if (test_num[i] == 1)
        {
            printf("N%i ", i);
        }
    }

    printf("\n");
    printf("\n");


}

main ()
{
    double a, b, c, x1, x2;
    char a_char[MAXLEN], b_char[MAXLEN], c_char[MAXLEN], test;
    int rez[NUMBER_OF_TESTS], i;

    printf("\n"
           "This program was created by Pascal user to solve equations like: ax^2+bx+c=0\n"
           "\n" );

    printf("Do you want to test this program?\n"
           "Press F to test this program or press Enter to start calculations\n" );

    scanf("%c", &test);

    if (test == 'F')
    {
        test_unit(  );
    }

    printf("Enter constants a,b and c in order to solve ax^2+bx+c=0\n"
           "\n"
           "a:=");
    gets(a_char);

    printf("\n"
           "b:=");
    gets(b_char);

    printf("\n"
           "c:=");
    gets(c_char);


    if ( check(a_char, &a) == 1 || check(b_char, &b) == 1 || check(c_char, &c) == 1 )
    {
        printf("Your constants have wrong type");
    } else
    {
        if ( solve(a, b, c, &x1, &x2) == 2 )
        {
            if ( aprox(x1) != aprox(x2) )
            {
                printf("\n"
                   "your answers are:");
                printf("%lf and %lf", aprox(x1), aprox(x2));
            } else
            {
                printf("\n"
                       "your answer is: %lf", aprox(x1));
            }

        }

        if (solve(a, b, c, &x1, &x2) == 1)
        {
            printf("\n"
                       "your answer is: %lf", aprox(x1));
        }

        if (solve(a, b, c, &x1, &x2) == 0)
        {
            printf("\n"
                       "the equation has no solutions");
        }

        if (solve(a, b, c, &x1, &x2) == 3)
        {
            printf("\n"
                       "every number is an answer");
        }

    }


    return 0;

}
