#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h> /* funcoes do glut */
#endif

#include "Imagem.h"
#include "Filtros.h"

/*-------------------------------------------------------------*/
/* Funções e variáveis static são visíveis apenas no módulo    */
/*-------------------------------------------------------------*/

/* Protótipo das funções */
void alteraTamanhoJanela(int w, int h);
void gerenciaTeclado(unsigned char key, int x, int y);
void desenha();
void opcoes();

/* Variáveis global */
static Imagem *imagem = NULL;
static Imagem *copiaDaImagem = NULL;
static Imagem *imagemOriginal = NULL;
static bool imagemFoiModificada = false;

void inicializa(int *argc, char *argv[], Imagem *img){

    imagem = img;
    copiaDaImagem = copiaImagem(imagem);
    imagemOriginal = copiaImagem(imagem);

    /* GLUT */
    glutInit(argc, argv);
    /* inicialize o glut */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    /* crie uma janela */
    glutInitWindowSize(obtemLargura(imagem), obtemAltura(imagem));

    glutCreateWindow("FotoXop");

    glutKeyboardFunc(gerenciaTeclado);
    glutReshapeFunc(alteraTamanhoJanela);
    glutDisplayFunc(desenha);

    opcoes();

    glutMainLoop();
}

void desenha() {
    int col, lin;
    glBegin(GL_POINTS);
    for (int h = 0; h < obtemAltura(imagem); h++) {
        for (int w = 0; w < obtemLargura(imagem); w++) {
            Pixel pixel = obtemPixel(imagem, h, w);
            glColor3ubv(pixel.cor);
            glVertex2f(w, obtemAltura(imagem) - h - 1);
        }
    }
    glEnd();

    /* mostra o buffer */
    glutSwapBuffers();
}
void alteraTamanhoJanela(int col, int lin) {
    glViewport(0, 0, col, lin);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, col, 0, lin);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void gerenciaTeclado(unsigned char key, int mx, int my) {
    char nomeArq[100];
    switch (key) {
    /* Filtro: escurecerImagem */
    case '1':
        AVISO(Grafico: escurecendo a imagem.);
        copiaDaImagem = copiaImagem(imagem);
        escurecerImagem(imagem);
        imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao escurecerImagem.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: clarearImagem */
    case '2':
        AVISO(Grafico: clareando a imagem.);
        copiaDaImagem = copiaImagem(imagem);
        clarearImagem(imagem);
        imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao clarearImagem.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: escalaDeCinzaImagem */
    case '3':
        AVISO(Grafico: realcando a imagem.);
        copiaDaImagem = copiaImagem(imagem);
        escalaDeCinzaImagem(imagem);
        imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao escalaDeCinzaImagem.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: Filtro de Sobel */
    case '4':
        AVISO(Grafico: aplicando o filtro de Sobel na imagem.);
        copiaDaImagem = copiaImagem(imagem);
        filtroSobel(imagem);
        imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao filtroSobel.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: deteccaoBordasLaplace */
    case '5':
        AVISO(Grafico: aplicando a detecção de bordas de Laplace na imagem.);
        copiaDaImagem = copiaImagem(imagem);
        deteccaoBordasLaplace(imagem);
        imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao deteccaoBordasLaplace.\n);
        opcoes();
        desenha();
        break;
    /* Filtro: meuFiltro */
    case 'm':
    case 'M':
        AVISO(Grafico: aplicando o Meu Filtro na imagem.);
        copiaDaImagem = copiaImagem(imagem);
        meuFiltro(imagem);
        imagemFoiModificada = true;
        AVISO(Grafico: voltei da funcao meuFiltro.\n);
        opcoes();
        desenha();
        break;
    /* Volta para a imagem original */
    case 'o':
    case 'O':
        AVISO(Grafico: voltando para a imagem original.);
        liberaImagem(imagem);
        imagem = copiaImagem(imagemOriginal);
        imagemFoiModificada = false;
        AVISO(Grafico: exibindo imagem original.\n);
        opcoes();
        desenha();
        break;
    /* Desfaz a última modificação */
    case 'z':
    case 'Z':
        AVISO(Grafico: desfazendo a ultima modificacao.);
        if (imagemFoiModificada){
            liberaImagem(imagem);
            imagem = copiaImagem(copiaDaImagem);
            imagemFoiModificada = false;
        }
        else{
            AVISO(Grafico: Nada a ser desfeito!);
        }
        AVISO(Grafico: voltei da funcao desfazOperacao.\n);
        opcoes();
        desenha();
        break;
    /* Salva a imagem */
    case 's':
    case 'S':
        AVISO(Grafico: chamando a funcao salvaImagem.);
        printf("Informe o nome do arquivo para a gravação: ");
        scanf("%s", nomeArq);
        salvaImagem(imagem, nomeArq);
        AVISO(Grafico: voltei da funcao salvaImagem.\n);
        opcoes();
        break;
    /* termina a execucao do programa  */
    case 27: // tecla ESC
    case 'x':
    case 'X':
        liberaImagem(imagem);
        liberaImagem(copiaDaImagem);
        liberaImagem(imagemOriginal);
        exit(EXIT_SUCCESS);
        break;
    default:
        break;
    }
}

void opcoes() {
    printf("Escolha uma opção:\n"
           " '1' para escurecer a imagem\n"
           " '2' para clarear a imagem\n"
           " '3' para deixar a imagem em escala de cinza\n"
           " '4' para aplicar o filtro de Sobel\n"
           " '5' para aplicar a detecção de bordas de Laplace\n"
           " 'm' para aplicar o Meu Filtro\n"
           " 'o' para voltar a imagem original\n"
           " 'z' para desfazer a última modificação\n"
           " 's' para salvar a imagem atual\n"
           " 'x' para encerrar o programa\n");
}