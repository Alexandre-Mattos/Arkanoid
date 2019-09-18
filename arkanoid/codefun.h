#include <windows.h>
#include <time.h>
#include <string.h>

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15

void gotoxy(int x, int y)
{
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void clrscr(){
  system("cls");
}

void delay (unsigned long t) {
  Sleep(t);
}

int random (int max) {
   return (rand() % max) ;
}

void randomize() {
   srand((unsigned) time(NULL));
}

void textcolor (int forecolor, int backcolor) {
	SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (forecolor | backcolor<<4));
}

void textbackground (int newcolor) {
    newcolor = newcolor << 4;
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (WORD) (newcolor| newcolor));
}
