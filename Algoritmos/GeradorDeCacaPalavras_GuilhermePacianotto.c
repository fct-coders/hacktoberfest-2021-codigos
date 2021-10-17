#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#define MAX 20
#define LimiteTentativas 1000
#define ANSI_COLOR_RED      "\x1b[31m"

double tentativas = 0;

typedef struct palavras{

    char palavra[20];

    struct palavras *proxima;
    int linha;
    int coluna;
    int limite;

} Palavra;

typedef struct Lista{

    Palavra *inicio;
    Palavra *fim;

}listaPalavras;

int tamanhoString(char *string){

    int i = 0;

    while(*(string + i) != '\0')
    {
        i++;
    }
    return i;

}
void normalizaToUpper(char *s){

    int tamanho = tamanhoString(s);

    for(int i = 0; i < tamanho; i++){

        *(s + i) = toupper(*(s + i));

    }

}
void inicializaCacaPalavras(char *cp){

    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            *(cp + i*MAX + j) = NULL;
}
void printarCacaPalavras(char *cp){

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){

            if(*(cp + i*MAX + j) == NULL){

                printf(" 0 ");

            }
            else{

                printf(" %c ",*(cp+i*MAX+j));

            }

        }
        printf("\n");
    }
}


int comparaStrings(char *string1, char *string2)
{
    int eh_igual = 0, tamanho1, tamanho2, contador = 0;

    tamanho1 = tamanhoString(string1);
    tamanho2 = tamanhoString(string2);

    if(tamanho1 != tamanho2)
    {
        return 0;
    }
    else{

        while(contador < tamanho1)
        {
            if(*(string1 + contador) != *(string2 + contador))
            {
                return 0;
            }
            contador++;
        }


    }

    return 1;
}

void copiaString(char *string1, char *string2){

    int tamanho1 = tamanhoString(string1);
    int tamanho2 = tamanhoString(string2);
    int contador = 0;

    while(contador < tamanho2){

        *(string1 + contador) = *(string2 + contador);

        contador++;
    }
    *(string1 + contador) = '\0';
    return;

}

void insereLista(char *string, listaPalavras *l){

    int tamanho = tamanhoString(string);
    Palavra *nova = (Palavra*)malloc(sizeof(Palavra));


    if(l->inicio == NULL || l->fim == NULL){

        copiaString(nova->palavra, string);
        nova->proxima = NULL;
        l->inicio = nova;
        l->fim = nova;
    }
    else{

        copiaString(nova->palavra, string);

        nova->proxima = NULL;
        l->fim->proxima = nova;
        l->fim = nova;
    }

}

void printarLista(listaPalavras *l){

    Palavra *pivo;
    pivo = l->inicio;
    int contador = 1;


    while(pivo != NULL){

        printf("%d - %s \n",contador,pivo->palavra);
        contador++;
        pivo = pivo->proxima;
    }

}
int podeInserirEsquerdaDireita(char *cp, int tamanho, int i, int j){

    int c = 0;

    while(c < tamanho){

        if(*(cp + j*MAX + i) != NULL)
        {
            return 0;
        }
        i++;
        c++;
    }

    return 1;

}
int insereEsquerdaDireita(char *cp, char *p, Palavra *pal){

    int tamanho = tamanhoString(p);
    int i, j, c = 0;
    i = rand()%(MAX-tamanho);
    j = rand()%MAX;
    while(podeInserirEsquerdaDireita(cp, tamanho, i, j) == 0){

        if(tentativas > LimiteTentativas){
            tentativas = 0;
            return 0;
        }

        i = rand()%(MAX-tamanho);
        j = rand()%MAX;
        tentativas++;
    }
    tentativas = 0;
    pal->linha = j;
    pal->coluna = i;
    pal->limite = tamanho - 1;
    while(*(p + c) != '\0'){
        *(cp + j*MAX + i) = *(p + c);
        i++;
        c++;
    }
    return 1;
}
int insereDireitaEsquerda(char *cp, char *p, Palavra *pal){

    int tamanho = tamanhoString(p);
    int i = 0, j = tamanho - 1;

    char auxiliar[tamanho];

    copiaString(auxiliar, p);


    for(i=0; i<tamanho; i++){

        *(p + i) = auxiliar[j];

        j--;
    }

    if(insereEsquerdaDireita(cp, p, pal) == 1){
        return 1;
    }
    else{
        return 0;
    }

}
int podeInserirCimaBaixo(char *cp, int tamanho, int i, int j){

    int c = 0;

    while(c < tamanho){

        if(*(cp + j*MAX + i) != NULL)
        {
            return 0;
        }

        j++;
        c++;
    }

    return 1;

}
int insereCimaBaixo(char *cp, char *p, Palavra *pal){

    int tamanho = tamanhoString(p);
    int i, j, c = 0;

    j = rand()%(MAX-tamanho);
    i = rand()%MAX;

    while(podeInserirCimaBaixo(cp, tamanho, i, j) == 0){

        if(tentativas > LimiteTentativas){
            tentativas = 0;
            return 0;
        }

        j = rand()%(MAX-tamanho);
        i = rand()%MAX;

        tentativas++;
    }

    tentativas = 0;

    pal->linha = j;
    pal->coluna = i;
    pal->limite = tamanho - 1;

    while(*(p + c) != '\0'){

        *(cp + j*MAX + i) = *(p + c);
        j++;
        c++;
    }

    return 1;

}
int insereBaixoCima(char *cp, char *p, Palavra *pal){

    int tamanho = tamanhoString(p);
    int i = 0, j = tamanho - 1;

    char auxiliar[tamanho];

    copiaString(auxiliar, p);


    for(i=0; i<tamanho; i++){

        *(p + i) = auxiliar[j];

        j--;
    }


    if(insereCimaBaixo(cp, p, pal) == 1)
    {

        return 1;
    }
    else
    {
        return 0;
    }

}
int podeInserirDiagonalPrincipal(char *cp, int tamanho, int i, int j){

    int c = 0;

    while(c < tamanho){

        if(*(cp + j*MAX + i) != NULL)
        {
            return 0;
        }
        j++;
        i++;
        c++;
    }

    return 1;

}
int insereDiagonalPrincipal(char *cp, char*p, Palavra *pal){

    int tamanho = tamanhoString(p);
    int i, j, c = 0;

    i = rand()%(MAX-tamanho);
    j = rand()%(MAX-tamanho);

    while(podeInserirDiagonalPrincipal(cp, tamanho, i, j) == 0){

        if(tentativas > LimiteTentativas){
            tentativas = 0;
            return 0;
        }

        i = rand()%(MAX-tamanho);
        j = rand()%(MAX-tamanho);
        tentativas++;
    }
    tentativas = 0;
    pal->linha = j;
    pal->coluna = i;
    pal->limite = tamanho - 1;
    while(*(p + c) != '\0'){

        *(cp + j*MAX + i) = *(p + c);
        j++;
        i++;
        c++;
    }
    return 1;
}
int podeInserirDiagonalSecundaria(char *cp, int tamanho, int i, int j){

    int c = 0;

    while(c < tamanho){

        if(*(cp + j*MAX + i) != NULL)
        {
            return 0;
        }
        j++;
        i--;
        c++;
    }

    return 1;

}
int insereDiagonalSecundaria(char *cp, char *p, Palavra *pal){

    int tamanho = tamanhoString(p);
    int i, j, c = 0;

    i = tamanho + rand()%(MAX-tamanho);
    j = tamanho + rand()%(MAX-tamanho);


    while(podeInserirDiagonalSecundaria(cp, tamanho, i, j) == 0){

        if(tentativas > LimiteTentativas){
            tentativas = 0;
            return 0;
        }

        i = tamanho + rand()%(MAX-tamanho);
        j = tamanho + rand()%(MAX-tamanho);

        tentativas++;

    }
    tentativas = 0;
    pal->linha = j;
    pal->coluna = i;
    pal->limite = tamanho - 1;
    while(*(p + c) != '\0'){

        *(cp + j*MAX + i) = *(p + c);
        j++;
        i--;
        c++;
    }
    return 1;
}
int gerarCacaPalavras(char *cp, listaPalavras *l){


    Palavra *pivo;
    pivo = l->inicio;
    int contador = 0;
    char auxiliar[MAX];

    while(pivo != NULL)
    {
        copiaString(auxiliar, pivo->palavra);

        if(contador % 6 == 0)
        {
            //printf("\nentrou em %d a palavra: %s \n",(contador%6), (auxiliar));
            if(insereEsquerdaDireita(cp, auxiliar, pivo) == 0)
            {
                inicializaCacaPalavras(cp);
                return 0;
            }

            //insere da esquerda pra direita na horizontal
        }
        else if(contador % 6 == 1)
        {
            //printf("\nentrou em %d a palavra: %s \n",(contador%6), (auxiliar));
            if(insereDireitaEsquerda(cp, auxiliar, pivo) == 0)
            {
                inicializaCacaPalavras(cp);
                return 0;
            }

            //insere da direita pra esquerda na horizontal
        }
        else if(contador % 6 == 2)
        {
            //printf("\nentrou em %d a palavra: %s \n",(contador%6), (auxiliar));
            if(insereCimaBaixo(cp, auxiliar, pivo) == 0)
            {
                inicializaCacaPalavras(cp);
                return 0;
            }

            //insere de cima para baixo
        }
        else if(contador % 6 == 3){
            //printf("\nentrou em %d a palavra: %s \n",(contador%6), (auxiliar));
            if(insereBaixoCima(cp, auxiliar, pivo) == 0)
            {
                inicializaCacaPalavras(cp);
                return 0;
            }

            //insere de baixo para cima
        }
        else if(contador % 6 == 4){
            //printf("\nentrou em %d a palavra: %s \n",(contador%6), (auxiliar));
            if(insereDiagonalPrincipal(cp, auxiliar, pivo) == 0)
            {
                inicializaCacaPalavras(cp);
                return 0;
            }

            //insere em paralelas � diagonal principal
        }
        else if(contador % 6 == 5){
            //printf("\nentrou em %d a palavra: %s \n",(contador%6), (auxiliar));
            if(insereDiagonalSecundaria(cp, auxiliar, pivo) == 0)
            {
                inicializaCacaPalavras(cp);
                return 0;
            }

            //insere em paralelas � diagonal secund�ria
        }

        contador++;
        pivo = pivo->proxima;
    }

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            if(*(cp + i*MAX + j) == NULL)
            {
                *(cp + i*MAX + j) = 'A' + rand()%26;
            }
        }
    }
    return 1;
}

void mostrarResposta(char *cp, listaPalavras *l){


    Palavra *pivo;
    int pinta;
    int contador = 0, contadorParalelo = 0;


    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            pinta = 0;
            pivo = l->inicio;
            if(*(cp + i*MAX + j) == NULL){

                printf(" 0 ");

            }
            else{
                contador = 0;
                while(pivo != NULL){

                    if((pivo->linha == i) && (pivo->coluna == j)){

                        if(contador % 6 == 0)
                        {
                            if(pivo->limite > 0)
                            {
                                pivo->limite = pivo->limite - 1;
                                pivo->coluna = pivo->coluna + 1;
                            }
                            //insere da esquerda pra direita na horizontal
                        }
                        else if(contador % 6 == 1)
                        {
                            if(pivo->limite > 0)
                            {
                                pivo->limite = pivo->limite - 1;
                                pivo->coluna = pivo->coluna + 1;
                            }
                            //insere da direita pra esquerda na horizontal
                        }
                        else if(contador % 6 == 2)
                        {
                            if(pivo->limite > 0)
                            {
                                pivo->limite = pivo->limite - 1;
                                pivo->linha = pivo->linha + 1;
                            }
                            //insere de cima para baixo
                        }
                        else if(contador % 6 == 3){

                            if(pivo->limite > 0)
                            {
                                pivo->limite = pivo->limite - 1;
                                pivo->linha = pivo->linha + 1;
                            }

                            //insere de baixo para cima
                        }
                        else if(contador % 6 == 4){
                            if(pivo->limite > 0)
                            {
                                pivo->limite = pivo->limite - 1;
                                pivo->coluna = pivo->coluna + 1;
                                pivo->linha = pivo->linha + 1;
                            }

                            //insere em paralelas � diagonal principal
                        }
                        else if(contador % 6 == 5){
                            if(pivo->limite > 0)
                            {
                                pivo->limite = pivo->limite - 1;
                                pivo->coluna = pivo->coluna - 1;
                                pivo->linha = pivo->linha + 1;
                            }
                            //insere em paralelas � diagonal secund�ria
                        }

                        pinta = 1;
                        break;

                    }
                    contador++;
                    pivo = pivo->proxima;
                }
                if(pinta == 1)
                {
                    ;
                    printf("\x1b[31m %c \e[0;37m",*(cp+i*MAX+j));
                }
                else{

                    printf(" %c ",*(cp+i*MAX+j));

                }


            }
        }
        printf("\n");
    }


}

int main(void){

    srand(time(NULL));
    char cacaPalavras[MAX][MAX];
    int contadorPalavras = 1;
    char aux[MAX], aux2[MAX];
    int insercao = 0, tentativasCacaPalavras = 0;

    inicializaCacaPalavras(cacaPalavras);

    listaPalavras Lista1;
    Lista1.inicio = NULL;
    Lista1.fim = NULL;


    setlocale(LC_ALL, "Portuguese");

    while(insercao<1 || insercao>2){

        printf("Deseja uma inser��o:\n\n1 - Manual\n2 - Autom�tica\n");

        scanf("%d",&insercao);
        fflush(stdin);
        system("cls");
    }

    if(insercao == 1)
    {
        printf("Aten��o: se deseja parar a inser��o, digite '/s' \n\n");
        printf("N�mero m�ximo de palavras: %d \n",MAX);
        printf("\ninsira as palavras que deseja colocar no ca�a palavras\n\n");
        printf("Insira a %d� Palavra: ",contadorPalavras);
        gets(aux);
        //copiaString(aux2,aux);
        normalizaToUpper(aux);
        insereLista(aux,&Lista1);

        contadorPalavras++;


        while(contadorPalavras < (MAX + 1)){

            printf("Insira a %d� Palavra: ",contadorPalavras);
            gets(aux);

            if(comparaStrings(aux,"/s") == 1){
                break;
            }
            normalizaToUpper(aux);
            insereLista(aux,&Lista1);

            contadorPalavras++;
        }
    }
    else if (insercao == 2){

        insereLista("BARCELONA",&Lista1);
        insereLista("BRATISLAVA",&Lista1);
        insereLista("CAMBRIDGE",&Lista1);
        insereLista("COPENHAGUE",&Lista1);
        insereLista("DUSSELDORF",&Lista1);
        insereLista("EDIMBURGO",&Lista1);
        insereLista("FRANKFURT",&Lista1);
        insereLista("KIEV",&Lista1);
        insereLista("LIVERPOOL",&Lista1);
        insereLista("LEEDS",&Lista1);
        insereLista("MAASTRICHT",&Lista1);
        insereLista("MADRID",&Lista1);
        insereLista("MANCHESTER",&Lista1);
        insereLista("LISBOA",&Lista1);
        insereLista("LONDRES",&Lista1);
        insereLista("PALERMO",&Lista1);
        insereLista("PARIS",&Lista1);
        insereLista("SERVILHA",&Lista1);
        insereLista("SHEFFIED",&Lista1);
        insereLista("TURIM",&Lista1);


    }

    printf("\nPalavras da lista: \n\n");

    printarLista(&Lista1);

    system("pause");

    printf("\n\n");

    printf("Ca�a palavras: \n");

    //printarCacaPalavras(cacaPalavras);

    printf("\n\n");

    while(gerarCacaPalavras(cacaPalavras, &Lista1) == 0){

        tentativasCacaPalavras++;
    }


    printarCacaPalavras(cacaPalavras);

    printf("\nPressione qualquer bot�o para mostrar a resposta\n\n");

    system("pause");

    mostrarResposta(cacaPalavras, &Lista1);

    printf("\nPressione qualquer bot�o para mostrar as tentativas\n\n");

    system("pause");

    system("cls");

    printf("\n O computador tentou montar esse ca�a palavras %d vezes\n\n",tentativasCacaPalavras);

}
