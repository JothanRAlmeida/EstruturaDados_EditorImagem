#ifndef IMAGEM_H
#define IMAGEM_H

#define AVISO(msg) fprintf(stdout, "AVISO: %s\n", #msg)
#define ERRO(msg) fprintf(stderr, "ERRO: %s\n", #msg)

enum Cores {
    RED   /* = 0 */,
    GREEN /* = 1 */,
    BLUE  /* = 2 */
};


typedef enum {
    false,
    true
} bool;

/* Byte = valores entre 0 e 255 (8 bits) */
typedef unsigned char Byte;

typedef struct pixel {
     Byte cor[3];
     /* cor[RED]   eh um valor entre 0 e 255 */
     /* cor[GREEN] eh um valor entre 0 e 255 */
     /* cor[BLUE]  eh um valor entre 0 e 255*/
} Pixel;

typedef struct imagem Imagem;


Imagem* alocaImagem(int largura, int altura);

void liberaImagem(Imagem *img);

int obtemLargura(Imagem *img);

int obtemAltura(Imagem *img);

Pixel obtemPixel(Imagem *img, int l, int c);

void recolorePixel(Imagem *img, int l, int c, Pixel pixel);

Imagem* copiaImagem(Imagem *origem);

Imagem *carregaImagem(const char *nomeArquivo);

void salvaImagem(Imagem *img, const char *nomeArquivo);

#endif /* IMAGEM_H */