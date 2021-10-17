#include <math.h>
#include <stdio.h>
#include <locale.h>

float lado1;
float lado2;
float lado3;


int main(void){
    setlocale(LC_ALL, "Portuguese");

    printf("\n\n Digite o valor do lado 1 do triângulo: ");
    scanf("%f", &lado1);
    printf("\n\n Digite o valor do lado 2 do triângulo: ");
    scanf("%f", &lado2);
    printf("\n\n Digite o valor do lado 3 do triângulo: ");
    scanf("%f", &lado3);

    if((lado1 < lado2 + lado3)&&(lado2 < lado1 + lado3)&&(lado3 < lado2 + lado1)){
        if(lado1 == lado2){
            if(lado1 == lado3){
                printf("\n\n O triângulo é equilátero!");
            }else{
                printf("\n\n O triângulo é isosceles!");
            }
        }else if(lado1 == lado3){
            printf("\n\n O triângulo é isosceles!");
        }else if(lado2 == lado3){
            printf("\n\n O triângulo é isosceles!");
        }else
            printf("\n\n O triângulo é escaleno!");
    }else
        printf("\n\n Os valores inseridos não correspondem à um triângulo!!");

}
