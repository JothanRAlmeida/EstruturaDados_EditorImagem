#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"
#include "Filtros.h"

void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   - v) >= 0 ? (pixel.cor[RED]   - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? (pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  - v) >= 0 ? (pixel.cor[BLUE]  - v) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void clarearImagem(Imagem *img){
    int v;
    printf("Digite o fator de claridade: ");
    scanf("%d", &v);

    for (int i = 0; i < obtemAltura(img); i++) {
        for (int j = 0; j < obtemLargura(img); j++) {
            Pixel pixel = obtemPixel(img, i, j);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   + v) <= 255 ? (pixel.cor[RED]   + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? (pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  + v) <= 255 ? (pixel.cor[BLUE]  + v) : 255);
            recolorePixel(img, i, j, pixel);
        }
    }

}

void escalaDeCinzaImagem(Imagem *img){
    for (int i = 0; i < obtemAltura(img); i++) {
        for (int j = 0; j < obtemLargura(img); j++) {
            Pixel pixel = obtemPixel(img, i, j);
            int valor = ((pixel.cor[RED]+pixel.cor[GREEN]+pixel.cor[BLUE])/3);
            pixel.cor[RED]  = valor;
            pixel.cor[GREEN] = valor;
            pixel.cor[BLUE] = valor;
            recolorePixel(img, i, j, pixel);
        }
    }

}

void filtroSobel(Imagem *img){

    Imagem *copia=copiaImagem(img);

    for (int i = 1; i < obtemAltura(img)-1; i++) {
        for (int j = 1; j < obtemLargura(img)-1; j++) {
            Pixel pixel = obtemPixel(img,i,j);

            int gy_red = (((int)obtemPixel(copia,i-1,j-1).cor[RED]) + ((int)obtemPixel(copia,i-1,j).cor[RED]*(2)) + ((int)obtemPixel(copia,i-1,j+1).cor[RED]) + ((int)obtemPixel(copia,i+1,j-1).cor[RED]*(-1)) + ((int)obtemPixel(copia,i+1,j).cor[RED]*(-2))+((int)obtemPixel(copia,i+1,j+1).cor[RED]*(-1)));
            int gy_green = (((int)obtemPixel(copia,i-1,j-1).cor[GREEN]) + ((int)obtemPixel(copia,i-1,j).cor[GREEN]*(2)) + ((int)obtemPixel(copia,i-1,j+1).cor[GREEN]) + ((int)obtemPixel(copia,i+1,j-1).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i+1,j).cor[GREEN]*(-2))+((int)obtemPixel(copia,i+1,j+1).cor[GREEN]*(-1)));
            int gy_blue = (((int)obtemPixel(copia,i-1,j-1).cor[BLUE]) + ((int)obtemPixel(copia,i-1,j).cor[BLUE]*(2)) + ((int)obtemPixel(copia,i-1,j+1).cor[BLUE]) + ((int)obtemPixel(copia,i+1,j-1).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i+1,j).cor[BLUE]*(-2))+((int)obtemPixel(img,i+1,j+1).cor[BLUE]*(-1)));

            int gx_red = (((int)obtemPixel(copia,i-1,j-1).cor[RED]) + ((int)obtemPixel(copia,i,j-1).cor[RED]*(2)) + ((int)obtemPixel(copia,i+1,j-1).cor[RED]) + ((int)obtemPixel(copia,i-1,j+1).cor[RED]*(-1)) + ((int)obtemPixel(copia,i,j+1).cor[RED]*(-2))+((int)obtemPixel(copia,i+1,j+1).cor[RED]*(-1)));
            int gx_green = (((int)obtemPixel(copia,i-1,j-1).cor[GREEN]) + ((int)obtemPixel(copia,i,j-1).cor[GREEN]*(2)) + ((int)obtemPixel(copia,i+1,j-1).cor[GREEN]) + ((int)obtemPixel(copia,i-1,j+1).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i,j+1).cor[GREEN]*(-2))+((int)obtemPixel(copia,i+1,j+1).cor[GREEN]*(-1)));
            int gx_blue = (((int)obtemPixel(copia,i-1,j-1).cor[BLUE]) + ((int)obtemPixel(copia,i,j-1).cor[BLUE]*(2)) + ((int)obtemPixel(copia,i+1,j-1).cor[BLUE]) + ((int)obtemPixel(copia,i-1,j+1).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i,j+1).cor[BLUE]*(-2))+((int)obtemPixel(copia,i+1,j+1).cor[BLUE]*(-1)));

            if(gy_red<=0)gy_red=0;
            if(gy_green<=0)gy_green=0;
            if(gy_blue<=0)gy_blue=0;

            if(gy_red>=255)gy_red=255;
            if(gy_green>=255)gy_green=255;
            if(gy_blue>=255)gy_blue=255;

            if(gx_red<=0)gx_red=0;
            if(gx_green<=0)gx_green=0;
            if(gx_blue<=0)gx_blue=0;

            if(gx_red>=255)gx_red=255;
            if(gx_green>=255)gx_green=255;
            if(gx_blue>=255)gx_blue=255;

            pixel.cor[RED]=((gy_red+gx_red)/2);
            pixel.cor[GREEN]=((gy_green+gx_green)/2);
            pixel.cor[BLUE]=((gy_blue+gx_blue)/2);

            recolorePixel(img, i, j, pixel);
        }
    }
    liberaImagem(copia);
}

void deteccaoBordasLaplace(Imagem *img) {

    Imagem *copia=copiaImagem(img);

    for (int i = 1; i < obtemAltura(img)-1; i++) {
        for (int j = 1; j < obtemLargura(img)-1; j++) {

            Pixel pixel = obtemPixel(img, i, j);

            int valor_red = ((int)obtemPixel(copia,i-1,j).cor[RED]*(-1)) + ((int)obtemPixel(copia,i,j-1).cor[RED]*(-1)) + ((int)obtemPixel(copia,i,j).cor[RED]*(4)) + ((int)obtemPixel(copia,i,j+1).cor[RED]*(-1)) + ((int)obtemPixel(copia,i+1,j).cor[RED]*(-1));
            int valor_green = ((int)obtemPixel(copia,i-1,j).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i,j-1).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i,j).cor[GREEN]*(4)) + ((int)obtemPixel(copia,i,j+1).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i+1,j).cor[GREEN]*(-1));
            int valor_blue = ((int)obtemPixel(copia,i-1,j).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i,j-1).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i,j).cor[BLUE]*(4)) + ((int)obtemPixel(copia,i,j+1).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i+1,j).cor[BLUE]*(-1));

            if(valor_blue<=0)valor_blue=0;
            if(valor_green<=0)valor_green=0;
            if(valor_red<=0)valor_red=0;

            if(valor_blue>=255)valor_blue=255;
            if(valor_green>=255)valor_green=255;
            if(valor_red>=255)valor_red=255;

            pixel.cor[RED]  = valor_red;
            pixel.cor[GREEN] = valor_green;
            pixel.cor[BLUE] = valor_blue;

            recolorePixel(img, i, j, pixel);
        }
    }
    liberaImagem(copia);
}

void meuFiltro(Imagem *img){
    AVISO(Filtros.c: Ainda nao implementei a funcao 'meuFiltro'); //Retire esssa mensagem ao implementar a fução

    Imagem *copia=copiaImagem(img);

    for (int i = 1; i < obtemAltura(img)-1; i++) {
        for (int j = 1; j < obtemLargura(img)-1; j++) {

            Pixel pixel = obtemPixel(img, i, j);

            int valor_red = ((int)obtemPixel(copia,i-1,j-1).cor[RED]*(-2)) + ((int)obtemPixel(copia,i-1,j).cor[RED]*(-1)) + ((int)obtemPixel(copia,i-1,j+1).cor[RED]*0) + ((int)obtemPixel(copia,i,j-1).cor[RED]*(-1)) + ((int)obtemPixel(copia,i,j).cor[RED])+((int)obtemPixel(copia,i,j+1).cor[RED])+((int)obtemPixel(copia,i+1,j-1).cor[RED]*0)+((int)obtemPixel(copia,i+1,j).cor[RED])+((int)obtemPixel(copia,i+1,j+1).cor[RED]*2);
            int valor_green = ((int)obtemPixel(copia,i-1,j-1).cor[GREEN]*(-2)) + ((int)obtemPixel(copia,i-1,j).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i-1,j+1).cor[GREEN]*0) + ((int)obtemPixel(copia,i,j-1).cor[GREEN]*(-1)) + ((int)obtemPixel(copia,i,j).cor[GREEN])+((int)obtemPixel(copia,i,j+1).cor[GREEN])+((int)obtemPixel(copia,i+1,j-1).cor[GREEN]*0)+((int)obtemPixel(copia,i+1,j).cor[GREEN])+((int)obtemPixel(copia,i+1,j+1).cor[GREEN]*2);
            int valor_blue = ((int)obtemPixel(copia,i-1,j-1).cor[BLUE]*(-2)) + ((int)obtemPixel(copia,i-1,j).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i-1,j+1).cor[BLUE]*0) + ((int)obtemPixel(copia,i,j-1).cor[BLUE]*(-1)) + ((int)obtemPixel(copia,i,j).cor[BLUE])+((int)obtemPixel(copia,i,j+1).cor[BLUE])+((int)obtemPixel(copia,i+1,j-1).cor[BLUE]*0)+((int)obtemPixel(copia,i+1,j).cor[BLUE])+((int)obtemPixel(copia,i+1,j+1).cor[BLUE]*2);

            if(valor_blue<=0)valor_blue=0;
            if(valor_green<=0)valor_green=0;
            if(valor_red<=0)valor_red=0;

            if(valor_blue>=255)valor_blue=255;
            if(valor_green>=255)valor_green=255;
            if(valor_red>=255)valor_red=255;

            pixel.cor[RED]  = valor_red;
            pixel.cor[GREEN] = valor_green;
            pixel.cor[BLUE] = valor_blue;

            recolorePixel(img, i, j, pixel);
        }
    }
    liberaImagem(copia);
}
