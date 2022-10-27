#include<stdio.h>
int main()
{
  int numero=rand();
  numero=numero%100+1;
  printf("Bem-vindo ao jogo\n");
  printf("Acho que um número entre 0-100 tens 5 escolhas");
  int x=0;
  scanf("%d",&x);
   for(int i=5; i>=0; i--)
   {
    if(x==numero)printf("Ganhaste");
    else if(x<numero){
        printf("Incresca a sua estimativa");
    }
    else printf("Diminua a sua estimativa");
   }
    return 0;
}