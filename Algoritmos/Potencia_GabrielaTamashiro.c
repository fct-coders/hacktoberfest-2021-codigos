#include <math.h>
#include <stdio.h>

int a, b, pot = 1, aux = 1;

int main(void)
{
    printf("\n\n Enter a real number for base ");
    scanf("%d", &a);
    printf("\n\n Enter an integer for the exponent: ");
    scanf("%d", &b);

    while (aux <= b)
    {
        pot *= a;
        aux++;
    }

    printf("\n\n The result of power is %d \n\n", pot);
}