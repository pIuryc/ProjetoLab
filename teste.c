#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void quantizacao(int *dados, int tamanho, int niveis) {
    for (int i = 0; i < tamanho; i++) {
        dados[i] = (dados[i] * niveis) / 255;
    }
}

int main(int argc, char *argv[]) {
   
    char nomeArquivo[] = "img01_SAIDA.txt";
    int *dados;
    int c, r, niveis, mv;

    printf("Digite o número de níveis de quantização (8 ou 16): ");
    scanf("%d", &niveis);

   FILE *fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
  char formato[3];
  fscanf(fp, "%s", formato);


  if (strcmp(formato, "P2") != 0) {
      printf("Formato do arquivo não suportado. Este programa suporta apenas PGM (P2).\n");
      fclose(fp);
      return 1;
  }

  fscanf(fp, "%d %d", &c, &r);
  fscanf(fp, "%d", &mv);

    dados = (int *)malloc(c*r * sizeof(int));

  for (int i = 0; i < c * r; i++) {
      fscanf(fp, "%d", &dados[i]);
  }
    fclose(fp);

    quantizacao(dados, c*r, niveis);

    printf("Dados quantizados:\n");
    for (int i = 0; i <  c*r; i++) {
        printf("%d ", dados[i]);
    }
    printf("\n");

  
    free(dados);

    return 0;
}
