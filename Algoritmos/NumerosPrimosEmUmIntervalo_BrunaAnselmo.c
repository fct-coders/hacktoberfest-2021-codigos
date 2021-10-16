#include <math.h>
#include <stdio.h>

int a, b, num, lim, cont = 2, aux = 1;

int main(void)
{
    printf("\nEnter a positive integer number: ");
    scanf("%d", &a);
    printf("\nEnter a positive integer number: ");
    scanf("%d", &b);

    if (a > b)
    {
        num = b;
        lim = a;
    }
    else
    {
        num = a;
        lim = b;
    }

    printf("\n\nThe prime numbers in the range [%d, %d] are \n\n", num, lim);

    while (num <= lim)
    {
        while (cont < num)
        {
            if ((num % cont) == 0)
            {
                aux = 0;
                break;
            }
            cont++;
        }
        if (aux)
        {
            printf("\n %d", num);
        }
        cont = 2;
        num++;
        aux = 1;
    }
}