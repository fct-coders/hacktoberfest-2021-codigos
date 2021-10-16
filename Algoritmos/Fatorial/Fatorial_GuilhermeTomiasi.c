#include <stdio.h>

long long fatorial (int n) {
    int i = 2;
    long long produto = 1;

    for (; i < n; i++)
        produto *= i;

    return produto;
}

int main (void) {
    int entrada;
    long long saida;

    printf("Enter a number: ");
    scanf("%d", &entrada);

    saida = fatorial(entrada);
    printf("The factorial of the input is: %lld\n", saida);

    return 0;
}