#include "main.h"

void SetColor(int color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show)
{

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;//커서의 표시 유형입니다. 커서가 표시되면 이 멤버는 TRUE입니다.
	ConsoleCursor.dwSize = 1;//커서 사이즈는 1~100;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

}


void GoToxy(int x, int y) {

	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
