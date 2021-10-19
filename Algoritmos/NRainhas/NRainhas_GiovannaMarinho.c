#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <stdlib.h>
#include <stdio.h>

#define LARGURA_TELA 640
#define ALTURA_TELA  640

void Inicializa_Tabuleiro(int *Tabuleiro, int N);
void Imprime_Tabuleiro(int *Tabuleiro, int N);
void Solucao(int *Tabuleiro, int N, int Coluna);
short Posiciona(int *Tabuleiro, int N, int Linha, int Coluna);

//OBS: implementacao desenvolvida em 2018 para o trabalho da disciplina de ATP-II
//Existem algumas limitacoes de interface que podem ser melhoradas, como a entrada de dados
//Foi utilizada a biblioteca de interface grafica Allegro5 (seu arquivo .dll pode ser encontrado nesta pasta)

int main (void)
{
    int N;
    printf("   ---------------------------------------------------------------------\n");
    printf("   ------------------------PROBLEMA DAS N RAINHAS-----------------------\n");
    printf("   ----------------------GIOVANNA CARREIRA MARINHO----------------------\n");
    printf("   ---------------------------------------------------------------------\n\n");
    printf("   DIGITE A QUANTIDADE DE RAINHAS / TAMANHO DO TABULEIRO: ");
    scanf("%d", &N);
    int Tabuleiro[N][N];

    al_init();                      //<Allegro> Inicializando a biblioteca.

    al_init_primitives_addon();     //<Allegro> Inicializando a biblioteca de primitivas (para fazer o tabuleiro).
    ALLEGRO_DISPLAY *janela = NULL; //<Allegro> Criando e inicializando a variável que representa a janela principal.
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);//<Allegro> Criando a janela, cujo a altura e largura são estipuladas pelas variaveis LARGURA_TELA e ALTURA_TELA.

    Inicializa_Tabuleiro(&Tabuleiro[0][0], N);
    Solucao(&Tabuleiro[0][0], N, 0);

    al_destroy_display(janela);     //<Allegro> Finalizando a janela.

    system("pause");
    return 0;
}

void Imprime_Tabuleiro(int *Tabuleiro, int N) //<Allegro>
{
    //Função de impressão do tabuleiro. Além disso mostra qual é a solução. Toda vez que a função é chamada a variavel "solucao" é incrementada
    //isso justifica o fato de ser "static".
    //Ela não imprime aquele tabuleiro que foi inicializado na função Inicializa_Tabuleiro, e sim o tabuleiro visual para o usuário.

    ALLEGRO_FONT* font = al_create_builtin_font();

    static int solucao=0;
    int i, j, p=1, t=LARGURA_TELA/N; //<Allegro> "t" é o tamanho de cada quadrado do tabuleiro.
    for(i=0 ; i<N ; i++) //<Allegro> Impressão do tabuleiro
    {
        for(j=0 ; j<N ; j++)
        {
            p = !p;  //Toda vez que se muda de posição da matriz, a variavel p recebe 0 ou 1, dessa forma, dependendo do seu valor, o quadrado desenhado é de cor diferente.
            p ?  al_draw_filled_rectangle(i*t, j*t, i*t + t, j*t + t, al_map_rgb(255, 255, 255)):
            al_draw_filled_rectangle(i*t, j*t, i*t + t, j*t + t, al_map_rgb(145, 145, 145));
        }
        if (N%2 == 0)
            p = !p;
    }

    for ( i=0; i < N ; i++) //<Allegro> Dispondo as rainhas de acordo com o tabuleiro da lógica do jogo.
    {
        for (j=0; j < N; j++)
        {
            if(*(Tabuleiro + i*N + j) == 1)
            {
                al_draw_filled_circle(j*t + (t/2), i*t + (t/2), t/4, al_map_rgb(0, 0, 0));
            }
        }
    }

    al_draw_textf(font, al_map_rgb(255, 0, 0), LARGURA_TELA -10, ALTURA_TELA - 30, ALLEGRO_ALIGN_RIGHT, "-GIOVANNA CARREIRA MARINHO");
    al_draw_textf(font, al_map_rgb(0, 0, 0), LARGURA_TELA -10, ALTURA_TELA - 20, ALLEGRO_ALIGN_RIGHT, "-NUMERO DE RAINHAS : %d", N);
    al_draw_textf(font, al_map_rgb(0, 0, 0), LARGURA_TELA -10, ALTURA_TELA - 10, ALLEGRO_ALIGN_RIGHT, "-SOLUCAO : %d", ++solucao);
    al_flip_display();  //<Allegro> Atualiza janela.
    al_rest(1.0);  //<Allegro> Segura a execução por 1 segundo.
    return;
}
void Inicializa_Tabuleiro(int *Tabuleiro, int N)
{
    //Diferente da estratégia do cavalo, esse tabuleiro é inicializado apenas com 0, ou seja, não tem a borda limitadora.
    int i, j;
    for(i=0; i < N; i++)
    {
        for(j=0; j < N; j++)
        {
            *(Tabuleiro + i*N + j) = 0;
        }
    }
    return;
}
void Solucao(int *Tabuleiro, int N, int Linha)
{
    int i;
    if(Linha == N)                      //Todas as rainhas já foram posicionadas. (Caso base do passo de recursão.
    {
        Imprime_Tabuleiro(Tabuleiro, N);//É feito várias impressoes de acordo com a quantidade de soluções. Além disso, ao chegar na posição final(Solucao(Tabuleiro, N, N);), é realizado uma nova tentativa de
        return;                         //configuração do tabuleiro (posto que *(Tabuleiro + Linha*N + N-1)=0), até que se esgote todas as possibilidades e se mostre todas as soluções possíveis.
    }
    for(i=0 ; i<N ; i++)
    {
        if(Posiciona(Tabuleiro, N, Linha, i))  //Verifica se pode posicionar a rainha naquela no posição.
        {
            *(Tabuleiro + Linha*N + i) = 1;    //Se puder, a posição recebe "1", significando que a rainha já foi posicionada.
            Solucao(Tabuleiro, N, Linha + 1);  //Realiza o procedimento para a proxima linha de maneira recursiva.
            *(Tabuleiro + Linha*N + i) = 0;    //Se não conseguir posicionar na próxima linha [linha+1], a posição anterior [linha] recebe "0". Ou seja, a rainha é removida daquela posição
        }                                      //e é analisado a possibilidade de posicioná-la em outra coluna da linha, dessa forma a variavel "i" é incrementada (caso seja menor que N)
    }                                          //de modo a tentar posionar a rainha na proxima coluna. (BACKTRACK)
}                                              //Se não der (ou seja, já foi analisado todas as possibilidades de modo que i>=N), volta à [linha-1], o "i" será incrementado a partir da coluna que estava... e assim por diante.
//Ou seja, se não achar uma solução para a próxima posição, é procurado uma nova solução para a posição anterior. Caso não há uma solução para essa posição anterior, é feio para a anterior, e assim por diante.
short Posiciona(int *Tabuleiro, int N, int Linha, int Coluna)
{
    //É irredundante verificar nas linhas após a rainha, pois é evidente que não tem outras rainhas naquelas próximas posições, logo será
    //verificado apenas nas linhas acima da rainha.
    int i, j;
    //------------------------Linha e coluna-------------------------
    for(i=0 ; i<Linha ; i++)
    {
        if(*(Tabuleiro + i*N + Coluna))//Se encontrar o valor "1" quer dizer que há uma rainha naquela coluna;
            return 0;                  //logo, é retornado o valor "0", ou seja, ela não pode ficar naquela posicao;
    }
    for(i=0 ; i<Coluna ; i++)
    {
        if(*(Tabuleiro + Linha*N + i)) //Se encontrar o valor "1" quer dizer que há uma rainha naquela linha;
            return 0;                  //logo, é retornado o valor "0", ou seja, ela não pode ficar naquela posicao;
    }
    //------------------------Diagonal principal---------------------
    for(i=Linha, j=Coluna ; i>=0 && j>=0 ; i--, j--) //É necessario verificar apenas acima da diagonal principal
    {
        if(*(Tabuleiro + i*N + j))
            return 0;
    }
    //------------------------Diagonal secundária--------------------
    for(i=Linha, j=Coluna ; i>=0 && j<N ; i--, j++) //É necessario verificar apenas acima da diagonal secundária
    {
        if(*(Tabuleiro + i*N + j))
            return 0;
    }
    //Após todas as verificacões é retornado "1".
    return 1;
}
