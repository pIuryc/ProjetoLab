#include <stdio.h>
#include <stdlib.h>

#define N 7

void vetorAleatorio(int *x, int *y, int n);
void criaCoocorrencias(int n,int *x, int *y, int M[][N]);

int main() {
  int *vetorx, *vetory, tam, M[N][N];

  printf("Escolha o tamanho dos vetores X e Y: ");
  scanf("%d", &tam);

  vetorx = (int *)(malloc(tam * sizeof(int)));
  vetory = (int *)(malloc(tam * sizeof(int)));

  for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
          M[i][j] = 0;
      }
  }

    vetorAleatorio(vetorx, vetory, tam);
    criaCoocorrencias(tam, vetorx, vetory, M);

    printf("Vetor X: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", *(vetorx + i));
    }
    printf("\n");

    printf("Vetor Y: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", *(vetory + i));
    }
    printf("\n");

    printf("Matriz de coocorrências:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

free(vetorx);
free(vetory);
    
    return 0;
}

void vetorAleatorio(int *x, int *y, int n){
  for(int i = 0; i < n; i++){
    *(x+i) = rand() % N;
    *(y+i) = rand() % N;
  }
}

void criaCoocorrencias(int n,int *x, int *y, int M[][N]) {
    for (int i = 0; i < n; i++) {
         M[*(x+i)][*(y+i)]++;
     }
 }