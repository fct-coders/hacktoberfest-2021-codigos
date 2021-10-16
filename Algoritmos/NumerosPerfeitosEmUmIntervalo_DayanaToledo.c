#include <math.h>
#include <stdio.h>

#define LIM 100000

int num = 2, cont = 2, soma = 1;

int main (void) {
    printf("\n\n\n Perfect numbers of intervals [2, 100000] \n\n");
        
    while (num <= LIM) {
        while (cont < num) {
            if ((num % cont) == 0) {
                soma = soma + cont;
            }
            cont++;
        }
        if (soma == num) {
            printf("\n %d", num);
        }
        cont = 2;
        num++;
        soma = 1;
    }
    
    return 0;
}
