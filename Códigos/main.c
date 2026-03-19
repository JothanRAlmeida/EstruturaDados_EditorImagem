#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Imagem.h"
#include "Grafico.h"

int main(int argc, char *argv[]) {

    Imagem* imagem = NULL; //Ponteiro para a imagem
    char nomeArq[100];  //Nome do arquivo

    if(argc == 2) {
        strcpy(nomeArq, argv[1]);
    }
    else {
        printf("Digite o nome do arquivo ppm: ");
        scanf("%99s[^\n]", nomeArq);
    }

    imagem = carregaImagem(nomeArq);

    if (imagem == NULL) {
        AVISO("Erro ao carregar a imagem");
        return 0;
    }

    inicializa(&argc, argv, imagem);

    return 0;
}


