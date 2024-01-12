#include "main.h"

void SetColor(int color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show)
{

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;//Ŀ���� ǥ�� �����Դϴ�. Ŀ���� ǥ�õǸ� �� ����� TRUE�Դϴ�.
	ConsoleCursor.dwSize = 1;//Ŀ�� ������� 1~100;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

}


void GoToxy(int x, int y) {

	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
