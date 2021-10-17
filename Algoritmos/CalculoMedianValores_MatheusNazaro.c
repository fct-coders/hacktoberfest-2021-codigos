#include <stdio.h>

int main (){

int n, i;
float soma, a, media;
    printf("Insert how many value have in your average: ");
    scanf("%d",&n);
    soma = 0;
for (i = 1; i <= n; i++){
    printf("Insert a number: ");
    scanf("%f", &a);
    soma = soma + a;
}
media = soma / n;
printf("Media = %.2f \n", media);
return 0;
}
