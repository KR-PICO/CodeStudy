#include <malloc.h> //���� ũ�⸦ ���������� �ٲ��ֱ� ���� �����Ҵ��� ����Ѵ�
#include <time.h> //������ ����Ϸ��� ���� �ð��� �õ��� �Ѱ��ֱ� ���Ͽ�
#include "main.h"
#include "map.h"

#define START 3
#define PLAYER 20 //�÷��̾�
#define FINISH 4 //���� ����
#define WALL 1 //�� - �÷��̾ ������ ���� �� �ϴ� ��
#define SPACE 0 //�� ���� - �� �� �÷��̾ �̵��� �� �ִ� ��
#define RMS 25 //��ǰ �迭�� ũ��

const char* pMap[] = { "  ", "��" };//const�� �������ν� ���� ������ �迭 �������� ������***
int** map, mapSize, ** backupMap; // �����Ҵ��� �ʰ� �Ҵ�� �ʰ� �Ҵ�� ���� ũ��
int level = 1, timer = 0;// ���� ����, Ÿ�Ӿƿ����� ���� �ð�ǥ��

void SetMap(void);//�Լ� ���� ����
int** RollingArray(int MapArr[25][25], int num, int block);
void PrintMap(int PosX, int PosY);
void PlayerMove(int* PosX, int* PosY, int Key);

int Record[10] = { 0 }, timer = 0, timerCpy = 0; //�̰� ��� ������ ���� �ʿ��ϴ�

int LevelSuccess(void);
void SaveRec(void);
int GameOver(void);
unsigned WINAPI CounterTimer(void* arg);
char** addFile(char** string, int size, int length, char* msg);


void GamePlay(void) {//game.cpp���� main������ ������

Restart:

	int PosX = 1, PosY = 1, NowLevel = level;
	char title[40] = { 0 };

	sprintf(title, "title MAZE - LV.%d", level);
	system(title);
	system("mode con: cols=100 lines=50");
	SetMap();
	while (NowLevel == level)
	{
		if (GetAsyncKeyState(VK_UP))
			PlayerMove(&PosX, &PosY, VK_UP);
		else if (GetAsyncKeyState(VK_DOWN))
			PlayerMove(&PosX, &PosY, VK_DOWN);
		else if (GetAsyncKeyState(VK_LEFT))
			PlayerMove(&PosX, &PosY, VK_LEFT);
		else if (GetAsyncKeyState(VK_RIGHT))
			PlayerMove(&PosX, &PosY, VK_RIGHT);
		else if (GetAsyncKeyState('R')) {

			for (int i = 0; i < mapSize; i++) {
				free(map[i]);
				free(backupMap[i]);
			}
			free(map);
			free(backupMap);
			//GetExitCodeThread(CountTimer, NULL); ���� �������� �ʾҴ�.
			goto Restart;
			return;
		}

		PrintMap(PosX, PosY);
		Sleep(1);
	}
	while (true) {
		switch (LevelSuccess()) {
		case 0:
			for (int i = 0; i < mapSize; i++) {
				free(map[i]);
				free(backupMap[i]);
			}
			free(map);
			free(backupMap);
			return;
			break;

		}




	}


	free(map);

	return;
};

void SetMap(void) {
	mapSize = level * 100;//���� ������� ������ 100��� ������

	//���� 2���� �迭�� �����Ҵ��Ŵ ���� ����
	map = (int**)malloc(sizeof(int*) * mapSize);
	for (int i = 0; i < mapSize; i++)
		map[i] = (int*)malloc(sizeof(int) * mapSize);

	//�����Ҵ� �� ���� ���� �� �������� �ʱ�ȭ ������
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			map[i][j] = SPACE;

	//Ÿ�Ӿƿ� �ð��� ����*2������ �ӽ� ���� ���߿� ������Ʈ
	timer = level * 120;

	int num = mapSize / RMS;//�ʿ��� ���� ������ ��

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			srand((unsigned)time(NULL) * (i + j));/*(i+j)�� ���ֵ� ���� �õ尡 ���� �ʳ�?*/
			int** arr = RollingArray(RandomMap[rand() % 2], rand() % 3, ((i == 0 && j == 0) || (i == num - 1 && j == num - 1)) ? 0 : (rand() % 5));
			for (int AH = RMS * i, height = 0; height < RMS; height++, AH++) {
				for (int AW = RMS * j, width = 0; width < RMS; width++, AW++) {
					map[AH][AW] = arr[height][width];

				}
			}
		}
	}

	for (int i = 0; i < mapSize; i++) {
		map[i][0] = WALL;
		map[0][i] = WALL;
		map[i][mapSize - 1] = WALL;
		map[mapSize - 1][i] = WALL;
	}

	map[mapSize - 2][mapSize - 2] = FINISH;
	map[1][1] = PLAYER;

	//���� ������ ���� �̺�Ʈ�� ó���� �� ���
	/*backupMap = (int**)malloc(sizeof(int*) * mapSize);
	for (int i = 0; i < mapSize; i++)
		backupMap[i] = (int*)malloc(sizeof(int) * mapSize);
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			backupMap[i][j] = map[i][j];*/

}

int** RollingArray(int MapArr[25][25], int num, int block) {
	int** arr;

	arr = (int**)malloc(sizeof(int*) * RMS);
	for (int i = 0; i < RMS; i++)
		arr[i] = (int*)malloc(sizeof(int) * RMS);

	for (int i = 0; i < num; i++) {
		int tempArr[RMS][RMS] = { 0 };/*�̰� �ᱹ �ѹ��� �Ⱦ��µ� �� ������... ?*/

		//�̰� �迭�� ���������� 90�� ������ �˰���
		for (int ii = 0; ii < RMS; ii++) {
			for (int j1 = RMS - 1, j2 = 0; j2 < RMS; j1--, j2++) {
				arr[ii][j2] = MapArr[j1][ii];
			}
		}
	}

	//������ �״��
	if (num == 0) {
		for (int i = 0; i < RMS; i++) {
			for (int j = 0; j < RMS; j++) {
				arr[i][j] = MapArr[j][i];
			}
		}
	}

	//�������� 8���� �Ա��� ���� ���� �ڵ�
	bool check[8] = { 0 };//��� flase ���·� �ʱ�ȭ
	for (int i = 0; i < block; i++) {/*���⸦ 6���� ���ָ� �ɰ� ������ �ⱸ �Ա� ���� �� 0~4 �� 5������... ?*/
		//���簢�� 4���� ���̸� 3���� �������� �ʿ��ϴ�!!!

		srand((unsigned)time(NULL) * (i + i));/*(i+i)�� ���ֵ� ���� �õ尡 ���� �ʳ�?*/
		int random = rand() % 8;

		//check[]�� true �̸� flase�� ã�� �ϴ� �ݺ���
		for (int i = 0; check[random]; i++) {
			if (i > 1000) {/*�̰� ���� �ʿ�������...? ����Ƚ���� �ø��� ���� �����ϴµ� �׳� ���� �ݺ� ��Ű�� �� ���� ���� ���� 1000?*/
				for (int j = 0; j < 8; j++) {
					if (check[j] == false) {
						random = j;
						break;
					}
				}
			}
			else random = rand() % 8;
		}

		check[random] = true;
		switch (random) {
		case 0:
			arr[1][0] = WALL;
			break;
		case 1:
			arr[0][1] = WALL;
			break;
		case 2:
			arr[0][RMS - 2] = WALL;
			break;
		case 3:
			arr[1][RMS - 1] = WALL;
			break;
		case 4:
			arr[RMS - 2][0] = WALL;
			break;
		case 5:
			arr[RMS - 1][1] = WALL;
			break;
		case 6:
			arr[RMS - 2][RMS - 1] = WALL;
			break;
		case 7:
			arr[RMS - 1][RMS - 2] = WALL;
			break;
		}
	}

	return arr;
}

void PrintMap(int PosX, int PosY) {
	int CameraPosX = 0, CameraPosY = 0;    //ī�޶� ��ǥ

	//�����Ͱ� �ƴϱ� ������ Pos���� �ٲ㵵 ������.
	if (PosX < 25) PosX = 0;   //ī�޶� ���� ���κ��� �ε����� ��
	else if (PosX > mapSize - 26) PosX = mapSize - 50;    //ī�޶� ������ ���κ��� �ε����� ��
	else PosX = PosX - 25;

	if (PosY < 25) PosY = 0;    //ī�޶� ���� ���κ��� �ε����� ��
	else if (PosY > mapSize - 26) PosY = mapSize - 50;    //ī�޶� �Ʒ��� ���κ��� �ε����� ��
	else PosY = PosY - 25;

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			CameraPosX = PosX + j; CameraPosY = PosY + i;  //ī�޶�� ���� ��ǥ + ��µǴ� �ε�����.
			GoToxy(j * 2, i);  //gotoxy�� �ֿܼ��� �Է��� ���̴� �״�� ���ָ� ��.
			if (map[CameraPosY][CameraPosX] == PLAYER) {  //�÷��̾ ���
				SetColor(10);
				printf("��");
				SetColor(15);
			}
			else if (map[CameraPosY][CameraPosX] == FINISH) {  //�ǴϽ� ��Ҹ� ���
				SetColor(204);
				printf("  ");
				SetColor(15);
			}
			else printf("%s", pMap[map[CameraPosY][CameraPosX]]);  //�� �� ���̳� ������ ���
		}
	}
	return;
}

void PlayerMove(int* PosX, int* PosY, int Key) {
	switch (Key) {
	case VK_UP: if (map[*PosY - 1][*PosX] != WALL) { map[*PosY][*PosX] = SPACE; *PosY -= 1; } break;
	case VK_DOWN: if (map[*PosY + 1][*PosX] != WALL) { map[*PosY][*PosX] = SPACE; *PosY += 1; } break;
	case VK_LEFT: if (map[*PosY][*PosX - 1] != WALL) { map[*PosY][*PosX] = SPACE; *PosX -= 1; } break;
	case VK_RIGHT: if (map[*PosY][*PosX + 1] != WALL) { map[*PosY][*PosX] = SPACE; *PosX += 1; } break;
	}
	map[*PosY][*PosX] = PLAYER;

	if (backupMap[*PosY][*PosX] == FINISH) level += 1;
	return;
}