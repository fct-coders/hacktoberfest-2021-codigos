#include <stdio.h>
#include <stdlib.h>

void relaxa(int u, int v, int *M, int n, int *d, int *pai, FILE *arq){
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		fprintf(arq,"Encontrado um caminho menos custoso para o vértice %d.\n",v);
		*(d+v) = *(d+u) + *(M + u*n + v);
		fprintf(arq,"Vértice %d agora tem distância %d\n",v,*(d+v));
		*(pai+v) = u;
		fprintf(arq,"Vértice %d agora tem como pai o vértice %d\n",v,u);
		
	}
	
}

bool vazio(bool *v, int n){
	
	for(int i=0; i<n; i++){
		
		if((*(v+i)) == true) return false;
		
	}
	
	return true;
	
}

void dijkstra(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("dijkstra.txt","w");
	fprintf(arq,"Aplicando o algoritmo de Dijkstra em um grafo com %d vértices, partindo do vértice %d\n",n,raiz);
	bool Q[n];
	bool S[n];
	int d[n];
	int pai[n];
	fputs("Inicializando os vértices...\n",arq);
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		Q[i] = true;
		
	}
	d[raiz] = 0;
	fprintf(arq,"Distância do vértice %d: 0\n",raiz);
	int menor, menorind, aux;
	while(!vazio(Q,n)){
		
		aux = 0;
		
		for(int i=0; i<n; i++){
			
			if((Q[i] == true) && (d[i] != -1)){
				
				if(!aux){
					
					aux = 1;
					menor = d[i];
					menorind = i;
					
				}
				
				if(d[i] < menor){
					
					menor = d[i];
					menorind = i;
					
				}
				
			}
			
		}
		
		fprintf(arq,"Extraindo, para processamento, o vértice de menor distância que ainda não foi processado. (Vértice %d)\n",menorind);
		S[menorind] = true;
		Q[menorind] = false;
		for(int i=0; i<n; i++){
			
			if(*(M + menorind*n + i) != -1){
				
				fprintf(arq,"Aplicando a função relaxa no vértice %d, em relação ao seu vizinho %d\n",menorind,i);
				relaxa(menorind, i, M, n, d, pai, arq);
				
			}
			
		}
		
	}
	fputs("Vértice   Distância   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %d           %d\n",i,d[i],pai[i]);
	fclose(arq);
	
}

int main(void){
	
	int grafos[5][5] = {
		{-1, 10, -1, 5, -1},
		{-1, -1, 1, 2, -1},
		{-1, -1, -1, -1, 4},
		{-1, 3, 9, -1, 2},
		{7, -1, 6, -1, -1},
	};
	dijkstra(*grafos, 5, 0);
	return 0;
	
}
