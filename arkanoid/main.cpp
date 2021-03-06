#include <iostream>
using namespace std;
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "codefun.h"

#define TAM_X 29    /// TAMANHO X DO MAPA
#define TAM_Y 29    /// TAMANHO Y DO MAPA

#define CENTRO_MAP 31    // constante para alinhar as colunas do mapa ao centro da janela

#define fence -1    // paredes do mapa
#define brk 2       // blocos do mapa
#define spc 20      // blocos especiais (+ pontos) do mapa
#define table -2    // tabua
#define black 0     // espaco vazio no mapa

void invis_cursor() {
        //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
}

void loading() {    /// Transicao entre a tela inicial e o jogo
    system("cls");  // Limpa a tela

    gotoxy(53,15);  // Posiciona o cursor no meio da tela

    cout << "Carregando";

    for(int i=0; i < 2; i++) {  // Laco que anima as reticencias
        gotoxy(63,15);
        for(int j=0; j < 3; j++) {
            cout << ".";
            Sleep(500); // Atraso entre cada ponto
        }
        gotoxy(63,15);  // Apaga as reticencias para reiniciar a animacao
        cout << "   ";
    }
}

void imprime_titulo(int j_max, int mat[], int sel_funcao) {     /// Imprime as artes do titulo, game over e vitoria
    char solid = 219;   // Caractere para a arte
    int center_x, center_y;     // Coordenadas para posicionar a arte

    switch(sel_funcao) {    // Switch que configura o posicionamento e a cor inicial do texto para cada funcao
        case 0: // Titulo
            textcolor(LIGHTBLUE,0);
            center_x = 24;
            center_y = 5;
        break;
        case 1: // Game over
            textcolor(LIGHTRED,0);
            center_x = 13;
            center_y = 9;
        break;
        case 2: // Vitoria
            textcolor(LIGHTYELLOW,0);
            center_x = 28;
            center_y = 9;
        break;
    }

    for(int i=0; i < 6; i++) {
        gotoxy(center_x, i + center_y); // Posiciona o cursor na posicao inicial da linha

        for(int j=0; j < j_max; j++) {
            if(mat[(i*j_max) + j] == 1) // Imprime um caractere solido ao encontrar '1' no vetor origem
                cout << solid << solid;
            else
                cout << ' ' << ' ';     // Imprime espacos caso contrario

            if(sel_funcao != 1) // Habilita um delay de animacao do texto exceto na tela de game over
                Sleep(8);
        }
        cout << endl;

        switch(i) {     // Switch que muda a cor conforme a linha da arte
            case 2: // A partir da quarta linha
                if(sel_funcao == 2)
                    textcolor(YELLOW,0);    // Vitoria
                else
                    textcolor(WHITE,0);     // Titulo, Game over
            break;
            case 3: // A partir da quinta linha
                if(sel_funcao == 2)
                    textcolor(WHITE,0);     // Vitoria
                else
                    textcolor(BRIGHTWHITE,0);   // Titulo, Game over
            break;
            case 5: // Reinicia para a cor inicial
                switch(sel_funcao) {
                    case 0:
                        textcolor(LIGHTBLUE,0); // Titulo
                    break;
                    case 1:
                        textcolor(LIGHTRED,0);  // Game over
                    break;
                    case 2:
                        textcolor(LIGHTYELLOW,0);   // Vitoria
                    break;
                }
            break;
        }
    }
}

void menu() {   /// Tela inicial do jogo
    // Vetor de origem para arte do titulo
    int titulo[6 * 36] = {0, 0, 0, 1, 0,     1, 1, 1, 0, 0,      1, 0, 0, 0, 0,      0, 0, 0, 1, 0,      1, 0, 0, 1, 0,      0, 0, 0, 0, 0,      1, 0,       0, 1, 1, 0,
                          0, 0, 1, 1, 0,     1, 0, 0, 1, 0,      1, 0, 0, 1, 0,      0, 0, 1, 1, 0,      1, 1, 0, 1, 0,      0, 1, 1, 0, 0,      1, 0,       1, 0, 0, 1,
                          0, 1, 0, 1, 0,     1, 0, 1, 0, 0,      1, 0, 1, 0, 0,      0, 1, 0, 1, 0,      1, 1, 0, 1, 0,      1, 0, 0, 1, 0,      1, 0,       1, 0, 0, 1,
                          1, 0, 0, 1, 0,     1, 1, 1, 0, 0,      1, 1, 0, 0, 0,      1, 0, 0, 1, 0,      1, 0, 1, 1, 0,      1, 0, 0, 1, 0,      1, 0,       1, 0, 1, 0,
                          1, 0, 0, 1, 0,     1, 0, 1, 0, 0,      1, 0, 1, 0, 0,      1, 0, 0, 1, 0,      1, 0, 1, 1, 0,      1, 0, 0, 1, 0,      1, 0,       1, 0, 1, 0,
                          0, 1, 0, 1, 0,     1, 0, 0, 1, 0,      1, 0, 0, 1, 0,      0, 1, 0, 1, 0,      1, 0, 0, 1, 0,      0, 1, 1, 0, 0,      1, 0,       1, 1, 0, 0};

    bool blink = 1, wait = 1;   // Variaveis bool para fazer o texto piscar e esperar um comando do teclado

    imprime_titulo(36, titulo, 0);  // Chamada da funcao para imprimir o titulo

    gotoxy(38,25);
    cout << "Trabalho por Andre, Alexandre e Eduardo";

    while(wait) {   // Laco que faz o texto piscar e mantem a funcao rodando
        gotoxy(40,15);

        if(_kbhit()) {  // Escapa do laco ao pressionar uma tecla
            getch();
            wait = !wait;
        }

        if(blink)
            cout << "PRESSIONE QUALQUER TECLA PARA JOGAR";
        else
            cout << "                                   ";

        if(wait) {  // Aplica um delay e muda o bool que alterna entre o texto e os espacos
            Sleep(1000);
            blink = !blink;
        }
    }

    loading();  // Chama a funcao de transicao entre o menu e o jogo
}

void param_mapa(int mapa[][TAM_X], int &i, int &j) {    /// Imprime os caracteres na tela baseado no valor de cada posicao na matriz do mapa
    char hazy = 178, board = 223, brick = 177;  // Caracteres para a parede, tabua e tijolos, respectivamente

     if(i == TAM_Y - 2 and j > 0 and j < TAM_X - 1) {   // Imprime a linha de morte do mapa (parede vermelha)
        textcolor(LIGHTRED, 0);
        cout << hazy << hazy;
     } else if(mapa[i][j] == fence) {   // Imprime as paredes (parede branca)
        textcolor(BRIGHTWHITE, 0);
        cout << hazy << hazy;
    } else if(mapa[i][j] == brk) {  // Imprime os tijolos com pontuacao normal (tijolos de cores aleatorias)
        textcolor(rand()%5 + 9, 0);
        cout << brick << brick << brick << brick << brick << brick;
        j += 2;
    } else if(mapa[i][j] == spc) {  // Imprime os tijolos com pontuacao aumentada (tijolos amarelos)
        textcolor(LIGHTYELLOW, 0);
        cout << brick << brick << brick << brick << brick << brick;
        j += 2;
    }else if(mapa[i][j] == table) { // Imprime a tabua (tabua amarela)
        textcolor(LIGHTYELLOW, 0);
        cout << board << board;
    } else {    // Imprime espacos nas posicoes vazias
        cout << ' ' << ' ';
    }
}

void print_mapa(int mapa[][TAM_X], int sel_mapa) {  /// Define os valores da matriz do mapa, os tijolos especiais e imprime o layout dos pontos e das vidas
    system("cls");  // Limpa a tela

    if(sel_mapa == 0) {     // Define a matriz do nivel 01
        for(int i=0; i < TAM_Y; i++) {
            for(int j=0; j < TAM_X; j++) {
                if(i == 0 or i == TAM_Y - 1 or j == 0 or j == TAM_X - 1)    // Posiciona a parede nos cantos
                    mapa[i][j] = fence;
                else if((i > 0 and i < 4) and (j > 0 and j < TAM_X - 1))    // Posiciona os tijolos nas 3 primeiras linhas do campo
                    mapa[i][j] = brk;
                else if(i == TAM_Y - 4 and j > 12 and j < 16)   // Posiciona a tabua no meio do campo, duas posicoes acima da zona da morte
                    mapa[i][j] = table;
                else    // Preenche o resto da matriz com espacos vazios
                    mapa[i][j] = black;
            }
        }

        int i = 0;
        while(i < (3*9)*0.3) {  // Troca 30% dos tijolos aleatoriamente para tijolos de maior pontuacao
            int x, y;

            x = rand()%9;       // Geracao das coordenadas aleatorias
            y = rand()%3 + 1;

            if(mapa[y][x*3 + 1] != spc) {   // If que muda o valor do tijolo caso ainda nao seja um de maior pontuacao e aumenta o contador
                for(int cont = 3; cont > 0; cont--)
                    mapa[y][x*3 + cont] = spc;
                i++;
            }
        }
    } else if(sel_mapa == 1) {      // Define a matriz do nivel 02
        for(int i=0; i < TAM_Y; i++) {
            for(int j=0; j < TAM_X; j++) {
                if(i == 0 or i == TAM_Y - 1 or j == 0 or j == TAM_X - 1)    // Similar ao nivel 01
                    mapa[i][j] = fence;
                else if((i > 0 and i < 6) and (j > 0 and j < TAM_X - 1))    // Posiciona os tijolos nas 5 primeiras linhas do campo
                    mapa[i][j] = brk;
                else if(i == TAM_Y - 4 and j > 12 and j < 16)   // Similar ao nivel 01
                    mapa[i][j] = table;
                else    // Similar ao nivel 01
                    mapa[i][j] = black;
            }
        }

        int i = 0, j = 0;
        while(i < 3) {  // Troca 3 tijolos normais para blocos indestrutiveis
            int x, y;
            while(j < (5*9)*0.35) {  // Troca 35% dos tijolos aleatoriamente para tijolos de maior pontuacao
                x = rand()%9;        // Geracao das coordenadas aleatorias (tijolos especiais)
                y = rand()%5 + 1;

                if(mapa[y][x*3 + 1] == brk) {   // Similar ao nivel 01
                    for(int cont = 3; cont > 0; cont--)
                        mapa[y][x*3 + cont] = spc;
                    j++;
                }
            }

            x = rand()%9;            // Geracao das coordenadas aleatorias (blocos indestrutiveis)
            y = rand()%5 + 1;

            if(mapa[y][x*3 + 1] == brk) {   // If que muda o valor do tijolo caso ainda nao seja um bloco indestrutivel e aumenta o contador
                for(int cont = 3; cont > 0; cont--)
                    mapa[y][x*3 + cont] = fence;
                i++;
            }
        }
    }

    for(int i=0; i < TAM_Y; i++) {  // For que chama a funcao que imprime os caracteres correspondentes aos numeros na matriz
        gotoxy(CENTRO_MAP,i);
        for(int j=0; j < TAM_X; j++) {
            param_mapa(mapa, i, j);
        }
        cout << endl;
    }

    textcolor(BRIGHTWHITE, 0);  // Sequencia que reposiciona o cursor e imprime o layout lateral do jogo
    gotoxy(101, 7);
    cout << "ARKANOID";
    gotoxy(97, 11);
    cout << "Vidas:  ";
    textcolor(LIGHTAQUA, 0);
    cout << "<> <> <>";     // Contador de vidas
    textcolor(BRIGHTWHITE, 0);
    gotoxy(97, 12);
    cout << "Score:  ";

    gotoxy(56, TAM_Y/2 - 3);    // Reposiciona o cursor no centro do mapa e muda a cor do texto para branco
    textcolor(BRIGHTWHITE, 0);

    cout << "NIVEL 0" << sel_mapa + 1;  // Imprime o nome do nivel e aguarda por 3 segundos para apaga-lo e iniciar o jogo
    Sleep(3000);
    gotoxy(56, TAM_Y/2 - 3);
    cout << "        ";
}

int move_tabua (int tecla, int x, int mapa[][TAM_X]) {  ///Define a movimentacao da tabua, esquerda e direita.
    char board = 223;
    textcolor(LIGHTYELLOW,0);

    switch(tecla)  //setas
    {
        case 75:   //esquerda
            if(x > 2) {
                mapa[TAM_Y - 4][x + 1] = black;  //apaga espaco anterior ocupado pela tabua
                gotoxy(CENTRO_MAP + (x + 1)*2, TAM_Y - 4);
                cout << "  ";
                x--;
                mapa[TAM_Y - 4][x - 1] = table;  //imprime espaco novo ocupado pela tabua
                gotoxy(CENTRO_MAP + (x - 1)*2, TAM_Y - 4);
                cout << board << board;
            }
        break;
        case 77:   //direita
            if(x < 26) {
                mapa[TAM_Y - 4][x - 1] = black; //apaga espaco anterior ocupado pela tabua
                gotoxy(CENTRO_MAP + (x - 1)*2, TAM_Y - 4);
                cout << "  ";
                x++;
                mapa[TAM_Y - 4][x + 1] = table; //imprime espaco novo ocupado pela tabua
                gotoxy(CENTRO_MAP + (x + 1)*2, TAM_Y - 4);
                cout << board << board;
            }
        break;
    }

    return x;  //retorna o novo valor para o centro da tabua
}

int pontos(int score, int x, int y, int mapa[][TAM_X], int sel_mapa) { /// Define quanto vale os blocos e os adiciona no score quando quebrados
    if(sel_mapa == 0) {
        if(mapa[y][x] == brk) { // Pontuacao bloco simples
            score += 1;
        } else if(mapa[y][x] == spc) { // Pontuacao bloco especial fase 1
            score += 5;
        }
    } else if(sel_mapa == 1) {
        if(mapa[y][x] == brk) { // Pontuacao bloco simples fase 2
            score += 5;
        } else if(mapa[y][x] == spc) { // Pontuacao bloco especial fase 2
            score += 10;
        }
    }

    return score;   // Retorna a pontuacao atualizada
}

void quebra_bloco(int x, int y, int mapa[][TAM_X],int sel_mapa) {   /// Faz com que os blocos sumam ao serem tocados
    if(mapa[y][x] == brk or mapa[y][x] == spc){ //verifica se na posicao tem um bloco (normal ou especial)
        int i;
        if(x%3 == 0) //verifica aonde a bolinha tocou no bloco(esquerda, meio, direita)
            i = 3;
        else
            i = x%3;
            /* i = 1 => esquerda
               i = 2 => meio
               i = 3 => direita */

        for(int j = (x + 1 - i); j < (x + 4 - i); j++) { //reposiciona o cursor baseado aonde a bolinha bateu e apaga o bloco
            gotoxy(2*j + CENTRO_MAP, y);
            cout << "  ";
            if(mapa[y][j] == brk)
                mapa[y][j] -= brk; //apaga bloco normal
            else
                mapa[y][j] -= spc; //apaga bloco especial
        }
    }
}

void controle(int ciclos, int delay, int mapa[][TAM_X], bool reset) {   /// Define a posicao inicial da tabua e chama a funcao de movimentacao da mesma, alem de definir o intervalo entre as posicoes da bolinha
    static int x = 14; // Posicao inicial x da tabua

    if(reset) { // Retorna a tabua para a posicao inicial
        x = 14;
    } else {

         while(ciclos > 0) { // While que define intervalo entre os movimentos da bolinha, em ciclos de "delay" milisegundos
            if(_kbhit()){
                int tecla = getch();   // Capta entradas do teclado
                x = move_tabua(tecla, x, mapa); // Funcao de movimentacao, atualiza a sua posicao x
            }
            Sleep(delay);   // Intervalo entre os ciclos
            ciclos--;
        }
    }
}

void pos_bolinha(int &x, int &y, int &dir_x, int &dir_y, int sel_mapa) {    /// Define a posicao da bolinha e a direcao na qual ela ira se movimentar inicialmente
    x = rand()%27 + 1;  // Onde a bolinha ira iniciar no eixo x

    if(sel_mapa == 0)   // Onde a bolinha ira iniciar no eixo y dependendo do mapa
        y = 4;
    else
        y = 6;

    int vet_dir_x[3] = {-1, 0, 1};
    dir_x = vet_dir_x[rand()%3];    // Direcao da movimentacao

    dir_y = -1; // A bolinha sempre inicia indo para baixo
}

bool condicao_vitoria(int mapa [][TAM_X]) {     ///Verifica se o jogador ganhou o jogo
    bool vitoria = true;

    for(int i = 1; i < 6; i++)      //laco para verificar se ainda tem blocos no mapa (numeros positivos)
        for(int j = 1; j < 28; j++)
            if(mapa[i][j] > 0) {
                vitoria = !vitoria;
                i = 6;
                j = 28;
            }

    return vitoria; //retorna a condicao de vitoria
}

bool colisao_bolinha(int x, int y, int &dir_x, int &dir_y, int mapa[][TAM_X], int &colisoes, int &score, int sel_mapa) {    /// Define a colisao da bolinha com objetos solidos e a sua resposta as colisoes
    if(dir_x == 0 and dir_y == -1) {    // Excessao: bolinha indo reto para baixo
        if(mapa[y - dir_y][x] != black) {
            if(mapa[y - dir_y][x - 1] != table) // Comeca a ir para a diagonal esquerda ao bater no canto esquerdo da tabua
                dir_x = -1;
            else if(mapa[y - dir_y][x + 1] != table) // Comeca a ir para a diagonal direita ao bater no canto direito da tabua
                dir_x = 1;
        }   // Segue a colisao normal ao bater no centro da tabua (inverte somente a direcao no eixo y)
    }
    if(mapa[y][x + dir_x] != 0){    // Colisao com paredes
        if(mapa[y][x + dir_x] == brk or mapa[y][x + dir_x] == spc) {    // Colidir com tijolos chama as funcoes para quebra-los e soma-los a pontuacao
            score = pontos(score, x + dir_x, y, mapa, sel_mapa);
            quebra_bloco(x + dir_x, y, mapa, sel_mapa);
        }
        dir_x = -dir_x; // Inverte a direcao da bolinha no eixo x
        colisoes++;     // Aumenta o contador de colisoes
    }
    if(mapa[y - dir_y][x] != 0){    // Colisao com tetos
        if(mapa[y - dir_y][x] == brk or mapa[y - dir_y][x] == spc) {    // Similar a colisao com paredes
            score = pontos(score, x, y - dir_y, mapa, sel_mapa);
            quebra_bloco(x, y - dir_y, mapa, sel_mapa);
        }
        dir_y = -dir_y; // Inverte a direcao no eixo y
        colisoes++;     // Similar a colisao com paredes
    } if(mapa[y - dir_y][x + dir_x] != 0){
        if(mapa[y - dir_y][x + dir_x] == brk or mapa[y - dir_y][x + dir_x] == spc){ // Similar as outras colisoes
            score = pontos(score, x + dir_x, y - dir_y, mapa, sel_mapa);
            quebra_bloco(x + dir_x, y - dir_y, mapa, sel_mapa);
        }
        dir_x = -dir_x; // Inverte tanto a direcao no eixo x quanto no eixo y
        dir_y = -dir_y;
        colisoes++;     // Similar as outras colisoes
    }

    if(mapa[y - dir_y][x + dir_x] != 0) // Repete a funcao se a bolinha ainda encontrar uma parede no final dela
        colisao_bolinha(x,y,dir_x,dir_y,mapa, colisoes, score, sel_mapa);

    return condicao_vitoria(mapa);  // Retorna o estado da condicao de vitoria do nivel
}

void move_bolinha(int dir_x, int dir_y, int &x, int &y, int mapa[][TAM_X]) {    /// Movimentacao da bolinha
    gotoxy(CENTRO_MAP + 2*x,y);
    param_mapa(mapa, y, x);  //reimprime o caractere equivalente da posicao anterior, verificando a matriz
    x += dir_x; //movimenta no eixo X
    y -= dir_y; //movimenta no eixo Y

    textcolor(LIGHTAQUA, 0);
    gotoxy(CENTRO_MAP + 2*x,y); //atualiza a posicao da bolinha
    cout <<"<>"; //imprime a bolinha na posicao nova
}

void morte(int &vidas, int &colisoes, int x) {  /// Funcao chamada caso a bolinha encoste no fundo da tela
    char hazy = 178; // lava

    gotoxy(CENTRO_MAP + 2*x, 27);
    textcolor(LIGHTRED, 0);
    cout << hazy << hazy; //reimprime a lava em que a bolinha caiu
    vidas--; //diminui a vida
    colisoes = 0;  //reinicia as colisoes

    Sleep(750);

    gotoxy(105 + 3*(vidas), 11); //diminui o contador de vida
    cout << "  ";

    Sleep(750);
}

void derrota(int &vidas, int &score) {  /// Define a matriz da arte do game over, a imprime e restaura as estatisticas do jogo
    system("cls");  // Limpa a tela
    int game_over[6 * 48] = {0, 1, 1, 1, 0, 0,	    0, 0, 0, 1, 0,		0, 0, 0, 0, 0, 0,	0, 1, 1, 1, 0, 0,	0, 0, 0,	0, 0, 0, 0, 0,		1, 0, 0, 0, 1, 0,	0, 1, 1, 1, 0, 0,	1, 1, 1, 0, 0,
                             1, 0, 0, 0, 1, 0,	    0, 0, 1, 1, 0,		0, 1, 0, 1, 0, 0,	1, 0, 0, 0, 1, 0,	0, 0, 0,	0, 1, 1, 0, 0,		1, 0, 0, 0, 1, 0,	1, 0, 0, 0, 1, 0,	1, 0, 0, 1, 0,
                             1, 0, 0, 0, 0, 0,  	0, 1, 0, 1, 0,		0, 1, 0, 1, 0, 0,	1, 0, 1, 1, 0, 0,	0, 0, 0,	1, 0, 0, 1, 0,		0, 1, 0, 1, 0, 0,	1, 0, 1, 1, 0, 0,	1, 0, 1, 0, 0,
    /*define a arte */       1, 0, 0, 1, 0, 0,	    0, 1, 0, 1, 0,		1, 0, 1, 0, 1, 0,	1, 0, 0, 0, 0, 0,	0, 0, 0,	1, 0, 0, 1, 0,		0, 1, 0, 1, 0, 0,	1, 0, 0, 0, 0, 0,	1, 1, 1, 0, 0,
                             1, 0, 0, 0, 1, 0,	    1, 0, 0, 1, 0,		1, 0, 1, 0, 1, 0,	1, 0, 0, 0, 1, 0,	0, 0, 0,	1, 0, 0, 1, 0,		0, 1, 0, 1, 0, 0,	1, 0, 0, 0, 1, 0,	1, 0, 1, 0, 0,
                             0, 1, 1, 1, 1, 0,	    0, 1, 0, 1, 0,		1, 0, 0, 0, 1, 0,	0, 1, 1, 1, 0, 0,	0, 0, 0,	0, 1, 1, 0, 0,		0, 0, 1, 0, 0, 0,	0, 1, 1, 1, 0, 0,	1, 0, 0, 1, 0 };

    imprime_titulo(48, game_over, 1); //Imprime a arte de game over
    Sleep(3000);

    vidas = 3; // Restaura as vidas
    score = 0; // Restaura a pontuacao
}

int jogo(int &sel_mapa, int mapa[][TAM_X]) {    /// Script do jogo
    int x, y, dir_x, dir_y, score = 0, vidas = 3, colisoes = 0; //variaveis gerais da bolinha e outras
    float delay = 25; //delay de atualizacao da posicao do player, tambem usado pra bolinha
    bool vitoria = false; //condicao de vitoria
    pos_bolinha(x, y, dir_x, dir_y, sel_mapa); //chama a funcao que spawna a bolinha aleatoriamente

    while(!vitoria) { //enquanto nao terminar os mapas fica nesse laco
        if(vidas == 0) { //se o jogador perder todas as vidas ele reinicia o jogo do mesmo mapa
            derrota(vidas, score);
            print_mapa(mapa, sel_mapa);
            pos_bolinha(x, y, dir_x, dir_y, sel_mapa);
            controle(5, delay, mapa, true);
        }

        if(colisoes == 10) { //aumenta a velocidade da bolinha caso ela bata 10 vezes
            delay = delay/1.4;
            colisoes++; //aumento fantasma pra evitar loops da condicao
        }

        if(y - dir_y > 27) {    //caso a bolinha caia na lava, a velocidade volta ao normal e reinicia a posicao da bolinha
            if(colisoes > 10)
                delay = delay*1.4;
            morte(vidas, colisoes, x);
            pos_bolinha(x, y, dir_x, dir_y, sel_mapa);
        } else{                 // caso contrario continua o jogo ate acabar os blocos no mapa
            controle(5, delay, mapa, false); //controle do player
            vitoria = colisao_bolinha(x,y,dir_x,dir_y,mapa, colisoes, score, sel_mapa); //checa condicao de vitoria quando acontece colisao
            move_bolinha(dir_x,dir_y,x,y,mapa); //atualiza a posicao da bolinha

            gotoxy(105,12);
            cout << score;  //imprime a pontuacao
        }

    }

    gotoxy(51,12);
    textcolor(LIGHTRED, 0);
    cout << "NIVEL 0" << sel_mapa + 1 << " CONCLUIDO"; //imprime mensagem quando acaba um nivel
    Sleep(3000);

    controle(5, delay, mapa, true); //reinicia a posicao do player antes de mudar o mapa

    return sel_mapa + 1; //avanca para o proximo mapa e aumenta a condicao de fim de jogo
}

void vitoria() {    /// Define a matriz da arte de vitoria e a imprime
    int vitoria[6 * 32] = {0, 1, 0, 0, 1, 0, 	1, 0,		1, 1, 1, 1, 0, 0,	0, 0, 0, 0, 0,		    1, 1, 1, 0, 0,		    1, 0,	    	0, 0, 0, 1, 0,  1,
                           1, 0, 0, 0, 1, 0,	1, 0,		0, 0, 1, 0, 1, 0,	0, 1, 1, 0, 0,		    1, 0, 0, 1, 0,		    1, 0,		    0, 0, 1, 1, 0,  1,
                           1, 0, 0, 0, 1, 0,	1, 0,		0, 0, 1, 0, 0, 0,   1, 0, 0, 1, 0,		    1, 0, 1, 0, 0,		    1, 0,	    	0, 1, 0, 1, 0,  1,
    /*define a arte */     0, 1, 0, 1, 0, 0,	1, 0,		0, 0, 1, 0, 0, 0,   1, 0, 0, 1, 0,		    1, 1, 1, 0, 0,		    1, 0,		    1, 0, 0, 1, 0,  1,
                           0, 1, 0, 1, 0, 0,	1, 0,		0, 0, 1, 0, 0, 0,   1, 0, 0, 1, 0,		    1, 0, 1, 0, 0,		    1, 0,	        1, 0, 0, 1, 0,  0,
                           0, 0, 1, 0, 0, 0,	1, 0,		0, 0, 1, 0, 0, 0,	0, 1, 1, 0, 0,		    1, 0, 0, 1, 0,		    1, 0,		    0, 1, 0, 1, 0,  1 };

    system("cls");  // Limpa a tela

    imprime_titulo(32, vitoria, 2); //Imprime a arte

    cout << "\n\n\n\n\n\n\n\n";
    getch();    // Aguarda comando do teclado para finalizar a funcao
}

int main() { /// Programa principal
    invis_cursor(); //desabilita o cursor
    srand(time(NULL)); //seed dos numeros aleatorios
    int mapa[TAM_Y][TAM_X], sel_mapa = 0; //matriz do mapa e seletor da fase
    bool cond = false; //condicao de parada do jogo

    menu();
    while(!cond) { //programa fica preso no laco ate o jogo acabar
        print_mapa(mapa, sel_mapa); //configura e printa o mapa na tela
        sel_mapa = jogo(sel_mapa, mapa); //verifica se ta no mapa 1 ou 2
        if(sel_mapa == 2)       //caso acabe o mapa 2, acaba o jogo
            cond = !cond;
    }
    vitoria(); //arte de vitoria, fim de jogo

    return 0;
}
