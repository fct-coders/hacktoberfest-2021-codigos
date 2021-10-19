#include <stdio.h>
#include <math.h>

float a;
float b;
float c;
float raiz1 = 0;
float raiz2 = 0;
float delta = 0;

int main(void){
    printf("Digite um valor para A: ");
    scanf("%f", &a);
    printf("Digite um valor para B: ");
    scanf("%f", &b);
    printf("Digite um valor para C: ");
    scanf("%f", &c);

    delta = (b*b)-(4*a*c);
    printf("O delta dessa função é %f \n\n", delta);

    if(delta > 0){
        raiz1 = (-b + sqrt(delta))/2*a;
        raiz2 = (-b - sqrt(delta))/2*a;
        printf("As raízes são reais, sendo elas: \n\n");
        printf("Raiz 1 = %f \n\n", raiz1);
        printf("Raiz 2 = %f \n\n", raiz2);
    }else if(delta = 0){
        raiz1 = (-b + sqrt(delta))/2*a;
        printf("As raízes são reais e iguais, sendo: %f\n\n", raiz1);
    }else
        printf("As raízes são complexas!\n\n");
}