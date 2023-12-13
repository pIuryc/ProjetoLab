#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#define DIRETORIO_IMAGENS "./image"

struct pgm
{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

void geraCSV(unsigned int, char *);
void preencheCSV(int *, unsigned int, char *, unsigned char);
void readPGMImage(struct pgm *, char *);
void writeSCMImage(int **, char *, int);
void quantizeImage(unsigned char *, int, int, int);
int valorVizinho(struct pgm *, int, int, int, int);
void aplicaFiltro(int *, int, int, int, unsigned char *);
void filtraMatriz(unsigned char *, int, int, int);
void criaCoocorrencias(int *, unsigned char *, unsigned char *, int);
void viewPGMImage(struct pgm *pio);
void gerarSCM(unsigned char *, unsigned char *, char *, int);
