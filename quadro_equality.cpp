#include <stdio.h>
#include <cmath>


float linsolv(float,float);
float quadrosolv(float,float,float);


main ()
{

    float a,b,c;

    printf("\n"
           "This programme was created by Pascal user to solve equations like: ax^2+bx+c=0\n" );
    printf("Enter constants a,b and c in order to solve ax^2+bx+c=0\n"
           "a:=");
    scanf("%f",&a);
    printf("\n"
           "b:=");
    scanf("%f",&b);
    printf("\n"
           "c:=");
    scanf("%f",&c);

    if (a==0)
    {
        if (b==0 && c==0)
        {
                printf("\n"
                       "every number is an answer");
        } else
            {
                if (b==0 && c!=0)
                {
                    printf("\n"
                           "neither of numbers is an answer");
                } else
                {
                    printf("\n"
                           "your answer is:%f",linsolv(b,c));
                }
            }
    } else
    {
        if (b*b-4*a*c>0)
        {
            printf("\n"
                   "your answers are:");
            printf("%f",quadrosolv(a,b,c));
        } else
        {
            if (b*b-4*a*c==0)
            {
                printf("\n"
                       "your answer is: %f",-b/(2*a));
            } else
            {
                printf("\n"
                       "choose better constants");
            }


        }

    }

    return(0);
}


float quadrosolv(float a, float b, float c)
{
    printf("%f ",(-sqrt(b*b-4*a*c)-b)/(2*a) );
    return ((sqrt(b*b-4*a*c)-b)/(2*a));
}

float linsolv(float b,float c)
{
    return((-1)*c/b);
}
