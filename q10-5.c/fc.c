#include "ff.h"

void gerarSCM(unsigned char *dados, unsigned char *dadosF, char *filename, int niveis)
{
    char fimImagem[20];
    char nomeArquivo[20];
    int *matrix = NULL;
    FILE *fp;
    int count = 0;

    sprintf(nomeArquivo, "SCM_%d.txt", niveis);

    fp = fopen(nomeArquivo, "a");

    if (fp == NULL)
    {
        puts("Erro ao abrir o arquivo");
        exit(1);
    }

    if (count<1)
    {
        for (int i = 1; i <= niveis * niveis; i++)
        {
            fprintf(fp, "%d, ", i);
        }
        fputc('\n', fp);
        fprintf(fp,"%d", niveis*niveis + 1 );
        count++;
    }

    if (!(matrix = calloc(niveis * niveis, sizeof(int))))
    {
        puts("Memória Insuficiente");
        exit(3);
    }

    criaCoocorrencias(matrix, dados, dadosF, niveis);

    for (int i = 0; i < niveis * niveis; i++)
    {
        fprintf(fp, "%d, ", *(matrix + i));
    }

    if (*filename == '1')
    {
        strcpy(fimImagem, "stroma");
    }
    else
    {
        strcpy(fimImagem, "epithelium");
    }

    fprintf(fp, "%s", fimImagem);
    fputc('\n', fp);

    fclose(fp);
}

void readPGMImage(struct pgm *pio, char *filename)
{
    FILE *fp;
    char ch;

    if (!(fp = fopen(filename, "r")))
    {
        perror("Erro.");
        exit(1);
    }
    printf("nome arq :%s\n", filename);

    if ((ch = getc(fp)) != 'P')
    {
        puts("A imagem fornecida não está no formato pgm");
        exit(2);
    }

    pio->tipo = getc(fp) - 48;

    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#')
    {
        while ((ch = getc(fp)) != '\n')
            ;
    }

    fseek(fp, -2, SEEK_CUR);

    fscanf(fp, "%d %d", &pio->c, &pio->r);

    if (ferror(fp))
    {
        perror(NULL);
        exit(3);
    }
    fscanf(fp, "%d", &pio->mv);
    fseek(fp, 0, SEEK_CUR);

    pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));

    switch (pio->tipo)
    {
    case 2:
        puts("Lendo imagem PGM (dados em texto)");
        for (int k = 0; k < (pio->r * pio->c); k++)
        {
            fscanf(fp, "%hhu", pio->pData + k);
        }
        break;
    case 5:
        puts("Lendo imagem PGM (dados em binário)");
        fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
        break;
    default:
        puts("Não está implementado");
    }
    fclose(fp);
}

void writeSCMImage(int **scm, char *filename, int niveis)
{
    printf("Chamando writeSCMImage com niveis=%d, filename=%s\n", niveis, filename);

    FILE *fp;

    if (!(fp = fopen(filename, "a+")))
    {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < niveis; i++)
    {
        for (int j = 0; j < niveis; j++)
        {
            fprintf(fp, "%d ", scm[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void viewPGMImage(struct pgm *pio)
{
    printf("Tipo: %d\n", pio->tipo);
    printf("Dimensoes: [%d %d]\n", (pio->c), pio->r);
    printf("Max: %d\n", pio->mv);
}

void quantizeImage(unsigned char *dados, int linha, int coluna, int nivel)
{
    int quantizedValue;

    for (int i = 0; i < linha * coluna; i++)
    {
        quantizedValue = (dados[i] * nivel) / 255;
        // Atualiza o valor na imagem
        dados[i] = (unsigned char)quantizedValue;
    }
    quantizedValue = 0;
}

int valorVizinho(struct pgm *pio, int linhas, int colunas, int linha, int coluna)
{
    return (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) ? pio->pData[linha * colunas + coluna] : 0;
}

void filtraMatriz(unsigned char *dados, int linha, int coluna, int filtro)
{
    if (filtro != 3 && filtro != 5 && filtro != 7)
    {
        fprintf(stderr, "Erro: O número de filtro deve ser 3, 5 ou 7.\n");
        exit(EXIT_FAILURE);
    }

    int soma = 0;
    int media = 0;

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            soma = 0;
            for (int x = i - filtro / 2; x <= i + filtro / 2; x++) 
            {
                for (int y = j - filtro / 2; y <= j + filtro / 2; y++)
                {
                    if (x >= 0 && x < linha && y >= 0 && y < coluna)
                    {
                        soma += dados[x * linha + y];
                    }
                }
            }
            media = soma / (filtro * filtro); 

            dados[i * coluna + j] = media;
        }
    }
}

void criaCoocorrencias(int *matriz, unsigned char *dados, unsigned char *dadosF, int niveis)
{
    for (int i = 0; i < (niveis * niveis); i++)
    {
        int indice = 0;

        indice = (int)(*(dados) * niveis) + *(dadosF);
        *(matriz + indice) += 1;
        
    }
}
