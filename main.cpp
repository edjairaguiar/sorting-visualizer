/** UNIVERSIDADE FEDERAL DO VALE DO SÃO FRANCISCO
    COLEGIADO DE ENGENHARIA DA COMPUTAÇÃO
    COMPUTAÇÃO GRÁFICA - PROJETO FINAL
    VISUALIZAÇÃO DE ALGORITMOS DE ORDENAÇÃO
    PROFESSOR: JORGE CAVALCANTI
    ALUNOS: EDJAIR AGUIAR, LEONARDO MIRANDA e JULIANA FIRMO **/

#include<windows.h>
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <time.h>
#define max 300

//#define delayTime 0.2

struct color {
	int r,g,b;
};
color x[] = {{0,0,1},
			 {1,0,0},
		     {0,1,0},
			 {0,0,1},
			 {1,1,0},
			 {0,1,1},
			 {1,0,1}};

struct line {
	int len;
	color c;
};
line ln[max],sortln[max],temp[max];

int min=0,count=0,finished=0, init=0, page=0;
int sorttype=0,inptype=0;
float delayTime=1.0;

// Prototipagem de funções
void drawlines();
void input(int);
void display();
void initialscreen();
void screeninstructions();
void screenbubble();
void screenselection();
void screenmerge();
void screenquick();
void screeninsert();
void screentutorial();

void alfanumerico(unsigned char key, int x, int y){
    if(key == 49)
        delayTime = 1.0;

    if(key == 50)
        delayTime = 0.75;

    if(key == 51)
        delayTime = 0.5;

    if (key == 52)
        delayTime = 0.25;

    if (key == 53)
        delayTime = 0.0;

    if (key==105)
    {
        init=0;
        glutPostRedisplay();
        glutDisplayFunc(screentutorial);
    }

    glutPostRedisplay();
}

void teclado(int key, int x, int y){
    if(key == GLUT_KEY_UP)
        init=1;

    if(key == GLUT_KEY_RIGHT)
        page++;

    if(key == GLUT_KEY_LEFT)
        page--;

    if (key == GLUT_KEY_DOWN)
        init=0;

    glutPostRedisplay();
}

void screentutorial(){

     glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

    // Título
	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "TUTORIAL";
	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);

    // Descrição
    p = (char*) "1. Para navegar entre os algoritmos, utilize o menu clicando com o botao DIREITO do mouse;";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 370.0);
    p = (char*) "2. Para alterar a velocidade de ordenacao, utilize o teclado numerico;";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 340.0);
    p = (char*) "3. Utilize a tecla     para ler a descricao do algoritmo em execucao;";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

     // INDICADOR DE TECLA PARA BAIXO
    glBegin(GL_TRIANGLES);
        glVertex2f( 94.0, 340.0);
        glVertex2f( 92.0, 344.0);
        glVertex2f( 96.0, 344.0 );
    glEnd();

    // Legendas
    // Legenda direita
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Voltar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();

    glutSwapBuffers();

    if (init==1)
    {
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }

}

void screeninstructions(){
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

    // Título
	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "SOBRE O PROJETO";
	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);

    // Descrição
    p = (char*) "Este eh um projeto criado em OpenGL, que busca mostrar a visualização de algoritmos de ordenacao ja conhecidos.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 380.0);
    p = (char*) "Ao passar para o lado direito com as teclas direcionais do teclado, voce podera conhecer informacoes sobre os";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 360.0);
    p = (char*) "algoritmos tratados. A qualquer momento, voce podera iniciar a visualizacao ao clicar a seta direcional para cima.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 320.0);
    p = (char*) "Ao clicar com o botao direito do mouse, voce podera navegar entre as opcoes e selecionar qual o algoritmo voce deseja";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 300.0);
    p = (char*) "visualizar. Buscando fins de comparacao, todos os algoritmos utilizam o mesmo tempo de execucao. Para alternar entre";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 280.0);
    p = (char*) "os tempos de execucao, utilize o teclado numerico. Os numeros para ordenacao sao gerados aleatoriamente. Sao utilizados";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 260.0);
    p = (char*) "utilizados um total de 30 numeros para todos os algoritmos. Para acessar o tutorial durante a execucao da ordenacao,";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 240.0);
    p = (char*) "pressione i. ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 200.0);
    p = (char*) "Esse projeto eh apresentado como requisito da nota final da disciplina Computacao Grafica, ministrada pelo";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 180.0);
    p = (char*) "professor Jorge Cavalcanti. Os seus desenvolvedores sao (em ordem alfabetica): Edjair Aguiar, Juliana Firmo";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 160.0);
    p = (char*) "e Leonardo Miranda.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 120.0);
    p = (char*) "Bom aprendizado!";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Legendas
    // Legenda direita
    glRasterPos2f(360.5, 15.0);
    p = (char*) "Bubble Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda esquerda
    glRasterPos2f(10.0, 15.0);
    p = (char*) "Tela inicial";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();
    // PARA DIREITA
    glBegin(GL_TRIANGLES);
        glVertex2f( 354.0, 15.0);
        glVertex2f( 354.0, 23.0);
        glVertex2f( 358.0, 19.0 );
    glEnd();
    // PARA ESQUERDA
    glBegin(GL_TRIANGLES);
        glVertex2f( 36.0, 15.0);
        glVertex2f( 36.0, 23.0);
        glVertex2f( 32.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page==0)
    {
        glutPostRedisplay();
        glutDisplayFunc(initialscreen);
    }

    if (page==2)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenbubble);
    }

    if (init==1)
    {
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }

}

void screenbubble(){
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "BUBBLE SORT";

	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);
    p = (char*) "Bubble Sort eh um algoritmo de ordenacao que pode ser aplicado em arrays e listas dinamicas. A ideia eh";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 380.0);
    p = (char*) "percorrer o vetor varias vezes, e a cada passagem fazer flutuar para o topo o maior elemento da sequencia.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 360.0);
    p = (char*) "Essa movimentacao lembra a forma como as bolhas em um tanque de agua procuram seu proprio nivel.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 320.0);
    p = (char*) "Se o objetivo eh ordenar os valores em forma decrescente, entao a posicao atual eh comparada com a";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 300.0);
    p = (char*) "proxima posicao e, se a posicao atual for maior que a posicao posterior, eh realizada a troca de";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 280.0);
    p = (char*) "valores nessa posicao. Caso contrario, nao eh realizada a troca, passando para a proxima comparacao.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 240.0);
    p = (char*) "Se o objetivo eh ordenar os valores em forma crescente, entao a posicao atual eh comparada com a";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 220.0);
    p = (char*) "proxima posicao e, se a posicao atual for menor que a posicao posterior, eh realizada a troca. Caso";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 200.0);
    p = (char*) "contrario, a troca nao eh feita e passa-se para o proximo par de comparacao.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Legendas
    // Legenda direita
    glRasterPos2f(360.5, 15.0);
    p = (char*) "Selection Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda esquerda
    glRasterPos2f(10.0, 15.0);
    p = (char*) "Sobre o projeto";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();
    // PARA DIREITA
    glBegin(GL_TRIANGLES);
        glVertex2f( 354.0, 15.0);
        glVertex2f( 354.0, 23.0);
        glVertex2f( 358.0, 19.0 );
    glEnd();
    // PARA ESQUERDA
    glBegin(GL_TRIANGLES);
        glVertex2f( 49.0, 15.0);
        glVertex2f( 49.0, 23.0);
        glVertex2f( 45.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page==1)
    {
        glutPostRedisplay();
        glutDisplayFunc(screeninstructions);
    }

    if (page==3)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenselection);
    }

    if (init==1)
    {
        sorttype = 0;
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }

}

void screenselection(){
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "SELECTION SORT";

	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);
    p = (char*) "Selection Sort eh um algoritmo de ordenacao baseado em se passar sempre o menor valor do vetor para a primeira";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 380.0);
    p = (char*) "posicao (ou maior, dependendo da ordem requerida), depois o de segundo menor valor para a segunda posicao e";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 360.0);
    p = (char*) "assim por diante. Assim eh feito sucessivamente com os n-1 elementos restantes, ate os ultimos dois elementos.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 320.0);
    p = (char*) "Seu algoritmo eh composto por dois lacos - um externo e um interno. O laco externo serve para controlar o ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 300.0);
    p = (char*) "indice inicial, enquanto o interno percorre todo o vetor. Na primeira iteracao do laco externo, o indice ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 280.0);
    p = (char*) "comeca de zero e a cada iteracao ele soma uma unidade ate o final do vetor; o laco interno percorre o";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 260.0);
    p = (char*) "o vetor comecando desse indice externo + 1 ate o final do vetor.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 220.0);
    p = (char*) "Apesar de pouco estavel, eh um dos mais velozes na ordenacao de vetores de tamanho pequeno. Alem disso,";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 200.0);
    p = (char*) "por nao usar um vetor auxiliar para realizara ordenacao, ele ocupa menos memoria.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Legendas
    // Legenda direita
    glRasterPos2f(360.5, 15.0);
    p = (char*) "Merge Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda esquerda
    glRasterPos2f(10.0, 15.0);
    p = (char*) "Bubble Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();
    // PARA DIREITA
    glBegin(GL_TRIANGLES);
        glVertex2f( 354.0, 15.0);
        glVertex2f( 354.0, 23.0);
        glVertex2f( 358.0, 19.0 );
    glEnd();
    // PARA ESQUERDA
    glBegin(GL_TRIANGLES);
        glVertex2f( 40.0, 15.0);
        glVertex2f( 40.0, 23.0);
        glVertex2f( 36.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page==2)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenbubble);
    }

    if (page==4)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenmerge);
    }

    if (init==1)
    {
        sorttype = 1;
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }

}

void screenmerge(){
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "MERGE SORT";

	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);
    p = (char*) "Tambem chamado de ordenacao por mistura. Eh um exemplo de algoritmo de ordenacao 'dividir para conquistar'. ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 380.0);
    p = (char*) "Sua ideia basica consistem em dividir o problema em varios subproblemas e resolver esses subproblemas";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 360.0);
    p = (char*) "atraves da recursividade. Apos todos os subproblemas terem sido resolvidos, ocorre a conquista - a uniao";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 340.0);
    p = (char*) "das resolucoes dos subproblemas.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 300.0);
    p = (char*) "Como o Merge Sort utiliza a recursividade, ha um alto consumo de memoria e tempo de execucao, tornando essa";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 280.0);
    p = (char*) "tecnica pouco eficiente na aplicacao de muitos problemas. ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 240.0);
    p = (char*) "Em comparacao aos algoritmos mais basicos, como bubble, insertion e selection sort, o merge eh mais rapido";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 220.0);
    p = (char*) "e eficiente quando eh utilizado sobre uma grande quantidade de dados. Para entradas pequenas, os algoritmos de";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 200.0);
    p = (char*) "ordenacao por comparacao mais basicos sao pro-eficientes.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Legendas
    // Legenda direita
    glRasterPos2f(360.5, 15.0);
    p = (char*) "Quick Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda esquerda
    glRasterPos2f(10.0, 15.0);
    p = (char*) "Selection Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();
    // PARA DIREITA
    glBegin(GL_TRIANGLES);
        glVertex2f( 354.0, 15.0);
        glVertex2f( 354.0, 23.0);
        glVertex2f( 358.0, 19.0 );
    glEnd();
    // PARA ESQUERDA
    glBegin(GL_TRIANGLES);
        glVertex2f( 45.0, 15.0);
        glVertex2f( 45.0, 23.0);
        glVertex2f( 41.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page==3)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenselection);
    }

    if (page==5)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenquick);
    }

    if (init==1)
    {
        sorttype = 2;
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }

}

void screenquick(){
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "QUICK SORT";

	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);
    p = (char*) "O Quick Sort eh um metodo de ordenacao muito rapido e eficiente, inventado por C.A.R Hoare em 1960,  ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 380.0);
    p = (char*) "quando visitou a Universidade de Moscovo como estudante. Naquela epoca, Hoare trabalhou num projeto de";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 360.0);
    p = (char*) "traducao de maquina para o National Physical Laboratory. Ele criou o Quick Sort ao tentar traduzir um";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 340.0);
    p = (char*) "dicionario do ingles para o russo, ordenando palavras ao reduzir o problema original em subproblemas.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 300.0);
    p = (char*) "O Quick Sort, assim como o merge, adota a estrategia de divisao e conquista. Sua estratagema consiste em";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 280.0);
    p = (char*) "rearranjar as chaves de modo que as chaves 'menores' precedam as chaves 'maiores'. Em seguida, o Quick Sort ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 260.0);
    p = (char*) "ordena as duas sublistas de chaves menores e maiores recursivamente, ate que a lista completa se encontre ordenada.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Legendas
    // Legenda direita
    glRasterPos2f(360.5, 15.0);
    p = (char*) "Insertion Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda esquerda
    glRasterPos2f(10.0, 15.0);
    p = (char*) "Merge Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();
    // PARA DIREITA
    glBegin(GL_TRIANGLES);
        glVertex2f( 354.0, 15.0);
        glVertex2f( 354.0, 23.0);
        glVertex2f( 358.0, 19.0 );
    glEnd();
    // PARA ESQUERDA
    glBegin(GL_TRIANGLES);
        glVertex2f( 39.0, 15.0);
        glVertex2f( 39.0, 23.0);
        glVertex2f( 35.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page==4)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenmerge);
    }

    if (page==6)
    {
        glutPostRedisplay();
        glutDisplayFunc(screeninsert);
    }

    if (init==1)
    {
        sorttype = 3;
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }

}

void screeninsert(){
    glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

	// Título - Nome do algoritmo
	glRasterPos2f(50.0, 450.0);
	char* p = (char*) "INSERTION SORT";
	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }
    glRasterPos2f(50.0, 400.0);

    // Descrição do algoritmo
    p = (char*) "O algoritmo de ordenacao por insercao eh o algoritmo que, dado uma estrutura (array, lista), constroi uma";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 380.0);
    p = (char*) "matriz final com um elemento de cada vez, uma insercao por vez. Assim, como os algoritmo de insercao quadratica,";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 360.0);
    p = (char*) "eh bastante eficiente para problemas com pequenas entradas, sendo o mais eficiente entre os algoritmos dessa";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 340.0);
    p = (char*) "ordem de classificacao.";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 300.0);
    p = (char*) "O Insertion Sort eh frequentemente comparado a organizacao de um baralho num jogo - voce deve recebe uma nova carta";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 280.0);
    p = (char*) "e deve coloca-la na posicao correta na sua mao ja ordenada. A cada nova carta adicionada a sua mao, voce comeca a";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    glRasterPos2f(50.0, 260.0);
    p = (char*) "compara-la com as cartas na sua mao ate encontrar a posicao correta. Isso prossegue ate que voce nao receba mais cartas. ";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
    // Legenda esquerda
    glRasterPos2f(10.0, 15.0);
    p = (char*) "Quick Sort";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 194.0, 27.0);
        glVertex2f( 196.0, 31.0);
        glVertex2f( 198.0, 27.0);
    glEnd();
    // PARA ESQUERDA
    glBegin(GL_TRIANGLES);
        glVertex2f( 38.0, 15.0);
        glVertex2f( 38.0, 23.0);
        glVertex2f( 34.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page==5)
    {
        glutPostRedisplay();
        glutDisplayFunc(screenquick);
    }

    if (page>=6)
    {
        page=6;
    }

    if (init==1)
    {
        sorttype = 4;
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }
}

void initialscreen(){

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);

	glColor3f(1, 1, 1);

    // Título
	glRasterPos2f(50.0, 250.0);
	char* p = (char*) "COMPUTACAO GRAFICA - PROJETO FINAL - ALGORITMOS DE ORDENACAO";

	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
        }

    // Cabeçalho - Nome dos membros do grupo
    glRasterPos2f(150.0, 235.0);
    p = (char*) "Alunos: Edjair Aguiar, Leonardo Miranda e Juliana Firmo";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    // Legendas
    // Legenda direita
    glRasterPos2f(350.5, 15.0);
    p = (char*) "Sobre o projeto";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }
    //Legenda central
    glRasterPos2f(190.5, 15.0);
    p = (char*) "Iniciar";
    while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p++);
        }

    // Indicadores de direcional
    // PARA CIMA
    glBegin(GL_TRIANGLES);
        glVertex2f( 196.0, 27.0);
        glVertex2f( 198.0, 31.0);
        glVertex2f( 200.0, 27.0);
    glEnd();
    // PARA DIREITA
    glBegin(GL_TRIANGLES);
        glVertex2f( 342.0, 15.0);
        glVertex2f( 342.0, 23.0);
        glVertex2f( 346.0, 19.0 );
    glEnd();

    glutSwapBuffers();

    if (page<=0)
    {
        page=0;
    }

    if (page==1)
    {
        glutPostRedisplay();
        glutDisplayFunc(screeninstructions);
    }

    if (init==1)
    {
        glutPostRedisplay();
        glutDisplayFunc(display);
        //glutSwapBuffers();
    }
}

void delay(float delay1){
   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;
}

void cabecalho(){
    glColor3f(0, 0, 0);

	glRasterPos2f(10.0, 520.5);
    char* p = (char*) "Para acessar o tutorial, pressione i";
	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }

    glRasterPos2f(185.0, 520.5);
    p = (char*) "Computacao Grafica | Edjair Aguiar, Leonardo Miranda e Juliana Firmo | Professor: Jorge Cavalcanti";

	while (*p != '\0')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *p++);
        }
}

void merge(int l,int m,int r){
int	i=l,j=m+1,k=l;
	while(i<=m && j<=r){
		if(sortln[i].len<=sortln[j].len)
		{
			temp[k].c.r=sortln[i].c.r;
			temp[k].c.g=sortln[i].c.g;
			temp[k].c.b=sortln[i].c.b;
			temp[k].len=sortln[i].len;
		i++;k++;
		}else
		{
			temp[k].c.r=sortln[j].c.r;
			temp[k].c.g=sortln[j].c.g;
			temp[k].c.b=sortln[j].c.b;
			temp[k].len=sortln[j].len;
			j++;k++;
		}
	}
	while(i<=m){
		    temp[k].c.r=sortln[i].c.r;
			temp[k].c.g=sortln[i].c.g;
			temp[k].c.b=sortln[i].c.b;
		    temp[k].len=sortln[i].len;
		i++;k++;
	}
	while(j<=r){
		    temp[k].c.r=sortln[j].c.r;
			temp[k].c.g=sortln[j].c.g;
			temp[k].c.b=sortln[j].c.b;
		    temp[k].len=sortln[j].len;
		j++;k++;
	}
	for(i=l;i<=r;i++){
		sortln[i].c.r=temp[i].c.r;
		sortln[i].c.g=temp[i].c.g;
		sortln[i].c.b=temp[i].c.b;
		sortln[i].len=temp[i].len;
		glClear(GL_COLOR_BUFFER_BIT);
		cabecalho();
		drawlines();
		glutSwapBuffers();
	}
}

void mergesort(int l , int r){
	if(l<r){
		int m=(l+r)/2;
		mergesort(l,m);
	    mergesort(m+1,r);
	    merge(l,m,r);
	    delay(delayTime);
	}
}

int partition(int l,int r){
	line temp;
	int i,j,pivot;
	pivot=sortln[l].len;
	i=l+1;
	j=r;
	while(i<=j){
	while(pivot>=sortln[i].len && i<=r)
		i++;
	while(pivot<=sortln[j].len && j>l)
		j--;
	if(i<j){
		temp=sortln[i];
		sortln[i]=sortln[j];
		sortln[j]=temp;
		glClear(GL_COLOR_BUFFER_BIT);
		drawlines();
		glutSwapBuffers();
	}
	}
	    temp=sortln[l];
		sortln[l]=sortln[j];
		sortln[j]=temp;
		glClear(GL_COLOR_BUFFER_BIT);
        cabecalho();
		drawlines();
		glutSwapBuffers();
	return j;
}

void quicksort(int l,int r){
	int pos;
	if(l<r){
	pos=partition(l,r);
	quicksort(l,pos-1);
	quicksort(pos+1,r);
	delay(delayTime);
	}
}

void insertion(){
	int i,j;
	line temp;
	for(i=1;i<max;i++){
    temp=sortln[i];
	j=i-1;
	while(j>=0&&sortln[j].len>temp.len)
	{
	sortln[j+1]=sortln[j];
	j=j-1;
	glClear(GL_COLOR_BUFFER_BIT);
	cabecalho();
	drawlines();
    glutSwapBuffers();
    delay(delayTime);
	}
	sortln[j+1]=temp;
	glClear(GL_COLOR_BUFFER_BIT);
	drawlines();
    glutSwapBuffers();

	}
}

void sort(){
	line temp;
	int a=0;
	switch(sorttype){
	case 0:
		for(int j=0;j<max-1;j++){
            cabecalho();
			if(sortln[j].len>sortln[j+1].len){
			  temp=sortln[j];
			  sortln[j]=sortln[j+1];
			  sortln[j+1]=temp;
			  delay(delayTime);
			  glutPostRedisplay();
			  break;
			}
		}
		break;

	case 1: min=count;
		for(int i=count+1;i<max;i++)
		{
		    cabecalho();
			if(sortln[min].len>sortln[i].len)
			{
			min=i;
			}
		}
			  temp=sortln[min];
			  sortln[min]=sortln[count];
			  sortln[count]=temp;
			  count++;
			  delay(delayTime);
			  glutPostRedisplay();
			  break;
	case 2:
	    mergesort(0,max-1);
		   break;

	case 3:quicksort(0,max-1);
		   break;
	case 4:insertion();
		   break;
	}
}

void drawlines(){
	int start=50;
	int aux, i;
	for(int i=0;i<max;i++){

    glColor3f((1.0/500)*sortln[i].len,
              0,
              1-(1.0/500)*sortln[i].len);

		//glColor3f(1.0,1.0,1.0);

		glBegin(GL_LINES);
		glVertex2f(start,10);
		glVertex2f(start,10+sortln[i].len);
		glEnd();
		start+=10;
	}
}

void display(){

    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,max*10+100,0,550);
	glLineWidth(3);
	drawlines();
	cabecalho();
	glutSwapBuffers();
	sort();

    if (init==0)
    {
        void screenbubble();
        void screenselection();
        void screenmerge();
        void screenquick();
        void screeninsert();

        switch (sorttype)
        {
            case 0:
                glutPostRedisplay();
                glutDisplayFunc(screenbubble);
            break;

            case 1:
                glutPostRedisplay();
                glutDisplayFunc(screenselection);
            break;

            case 2:
                glutPostRedisplay();
                glutDisplayFunc(screenmerge);
            break;

            case 3:
                glutPostRedisplay();
                glutDisplayFunc(screenquick);
            break;

            case 4:
                glutPostRedisplay();
                glutDisplayFunc(screeninsert);
            break;
        }
        //glutSwapBuffers();
    }
}

void randomize(){
int a;
	for(int i=0;i<max;i++){
		ln[i].len=(rand()%500);
		a=rand()%7;
		ln[i].c=x[a];
	}
}

void choice(int ch){
	sorttype=ch;
	count=0;min=0;
	for(int i=0;i<max;i++)
	sortln[i]=ln[i];
	display();
}

int main(int argc,char** argv){
	randomize();
	for(int i=0;i<max;i++)
	sortln[i]=ln[i];
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(250,50);
	glutInitWindowSize(900,600);
	glutCreateWindow("Computação Gráfica - Projeto Final");
	glutCreateMenu(choice);
	glutDisplayFunc(initialscreen);
	glutAddMenuEntry("Bubble Sort",0);
	glutAddMenuEntry("Selection Sort",1);
	glutAddMenuEntry("Merge Sort",2);
	glutAddMenuEntry("Quick Sort",3);
	glutAddMenuEntry("Insertion Sort",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(alfanumerico);
	glutSpecialFunc(teclado);
	glutMainLoop();
}
