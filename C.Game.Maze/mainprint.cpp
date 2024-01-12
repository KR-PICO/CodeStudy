#include "main.h"

void mainPrint(void);

int main(void) {
	int POS = 0;
	CursorView(0);
	system("COLOR 0F");
	mainPrint();
	while (true)
	{
		if (GetAsyncKeyState(VK_LEFT))
			if (POS == 0) POS = 3;
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == 3) POS = 0;
			else POS += 1;
		else if (GetAsyncKeyState(VK_RETURN))
			break;
		

		//±ôºý±ôºý °Å¸®´Â °Å & ¼Ò¸® »ö»óµµ ÃßÈÄ º¯°æ
		switch (POS) {
		case 0:
			SetColor(11);
			GoToxy(10, 4); printf("New Game");
			SetColor(15);
			GoToxy(35, 4); printf("Continue");
			GoToxy(60, 4); printf("See Rank");
			GoToxy(85, 4); printf("End Game");
			break;
		case 1:
			GoToxy(10, 4); printf("New Game");
			SetColor(11);
			GoToxy(35, 4); printf("Continue");
			SetColor(15);
			GoToxy(60, 4); printf("See Rank");
			GoToxy(85, 4); printf("End Game");
			break;
		case 2:
			GoToxy(10, 4); printf("New Game");
			GoToxy(35, 4); printf("Continue");
			SetColor(11);
			GoToxy(60, 4); printf("See Rank");
			SetColor(15);
			GoToxy(85, 4); printf("End Game");
			break;
		case 3:
			GoToxy(10, 4); printf("New Game");
			GoToxy(35, 4); printf("Continue");
			GoToxy(60, 4); printf("See Rank");
			SetColor(11);
			GoToxy(85, 4); printf("End Game");
			SetColor(15);
			break;
		default: break;
		}
		Sleep(100);
	}
	cls;

	//Å©±â¶û Áß¾Ó¿¡ ¸ÂÃß±â
	if (POS == 0) {
		SetColor(11);
		GoToxy(40, 4);
		printf("Selected New Game.");
		GamePlay();
		pause;
	}
	else if (POS == 1) {
		SetColor(11);
		GoToxy(40, 4);
		printf("Selected Continue.");
		pause;
	}
	else if (POS == 2) {
		SetColor(11);
		GoToxy(40, 4);
		printf("Selected See Rank.");
		pause;
	}

	return 0;
}

void mainPrint(void) {
	system("mode con: cols=106 lines=9");
	system("title maze - main");

	puts("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");
	puts("¡á                                                                                                      ¡á");
	puts("¡á                                                                                                      ¡á");
	puts("¡á                                                                                                      ¡á");
	puts("¡á                                                                                                      ¡á");
	puts("¡á                                                                                                      ¡á");
	puts("¡á                                                                                                      ¡á");
	puts("¡á                                                                                                      ¡á");
	printf("¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á");

	GoToxy(10, 4); printf("New Game");
	GoToxy(35, 4); printf("Continue");
	GoToxy(60, 4); printf("See Rank");
	GoToxy(85, 4); printf("End Game");

	return;
}

