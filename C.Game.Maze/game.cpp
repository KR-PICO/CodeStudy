#include <malloc.h> //맵의 크기를 동기적으로 바꿔주기 위해 동적할당을 사용한다
#include <time.h> //랜덤을 사용하려면 현재 시간을 시도로 넘겨주기 위하여
#include "main.h"
#include "map.h"

#define START 3
#define PLAYER 20 //플레이어
#define FINISH 4 //도착 지점
#define WALL 1 //벽 - 플레이어가 막혀서 가지 못 하는 곳
#define SPACE 0 //빈 공간 - 즉 즉 플레이어가 이동할 수 있는 곳
#define RMS 25 //부품 배열의 크기

const char* pMap[] = { "  ", "■" };//const를 붙임으로써 이중 포인터 배열 느낌으로 맞춰줌***
int** map, mapSize, ** backupMap; // 동적할당할 맵과 할당된 맵과 할당된 맵의 크기
int level = 1, timer = 0;// 현재 레벨, 타임아웃까지 남은 시간표시

void SetMap(void);//함수 원형 선언
int** RollingArray(int MapArr[25][25], int num, int block);
void PrintMap(int PosX, int PosY);
void PlayerMove(int* PosX, int* PosY, int Key);

int Record[10] = { 0 }, timer = 0, timerCpy = 0; //이건 기록 저장을 위해 필요하다

int LevelSuccess(void);
void SaveRec(void);
int GameOver(void);
unsigned WINAPI CounterTimer(void* arg);
char** addFile(char** string, int size, int length, char* msg);


void GamePlay(void) {//game.cpp에서 main정도의 역할임

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
			//GetExitCodeThread(CountTimer, NULL); 아직 구현하지 않았다.
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
	mapSize = level * 100;//맵의 사이즈는 레벨의 100배로 정해줌

	//맵을 2차원 배열로 동적할당시킴 잊지 말자
	map = (int**)malloc(sizeof(int*) * mapSize);
	for (int i = 0; i < mapSize; i++)
		map[i] = (int*)malloc(sizeof(int) * mapSize);

	//동적할당 된 맵을 전부 빈 공간으로 초기화 시켜줌
	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			map[i][j] = SPACE;

	//타임아웃 시간은 레벨*2분으로 임시 설저 나중에 업데이트
	timer = level * 120;

	int num = mapSize / RMS;//필요한 맵의 개수를 셈

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			srand((unsigned)time(NULL) * (i + j));/*(i+j)를 없애도 랜덤 시드가 들어가지 않나?*/
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

	//추후 아이템 같은 이벤트를 처리할 때 사용
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
		int tempArr[RMS][RMS] = { 0 };/*이거 결국 한번도 안쓰는데 왜 선언함... ?*/

		//이게 배열을 오른쪽으로 90도 돌리는 알고리즘
		for (int ii = 0; ii < RMS; ii++) {
			for (int j1 = RMS - 1, j2 = 0; j2 < RMS; j1--, j2++) {
				arr[ii][j2] = MapArr[j1][ii];
			}
		}
	}

	//원본은 그대로
	if (num == 0) {
		for (int i = 0; i < RMS; i++) {
			for (int j = 0; j < RMS; j++) {
				arr[i][j] = MapArr[j][i];
			}
		}
	}

	//랜덤으로 8개의 입구를 막기 위한 코드
	bool check[8] = { 0 };//모두 flase 상태로 초기화
	for (int i = 0; i < block; i++) {/*막기를 6곳만 해주면 될거 같은데 출구 입구 제외 왜 0~4 즉 5개이지... ?*/
		//정사각형 4개를 붙이면 3개의 접착면이 필요하다!!!

		srand((unsigned)time(NULL) * (i + i));/*(i+i)를 없애도 랜덤 시드가 들어가지 않나?*/
		int random = rand() % 8;

		//check[]이 true 이면 flase를 찾게 하는 반복문
		for (int i = 0; check[random]; i++) {
			if (i > 1000) {/*이거 굳이 필요했을까...? 시행횟수를 늘리는 것은 이해하는데 그냥 무한 반복 시키고나 더 작은 수로 굳이 1000?*/
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
	int CameraPosX = 0, CameraPosY = 0;    //카메라 좌표

	//포인터가 아니기 때문에 Pos값을 바꿔도 괜찮다.
	if (PosX < 25) PosX = 0;   //카메라가 왼쪽 세로벽에 부딪혔을 때
	else if (PosX > mapSize - 26) PosX = mapSize - 50;    //카메라가 오른쪽 세로벽에 부딪혔을 때
	else PosX = PosX - 25;

	if (PosY < 25) PosY = 0;    //카메라가 위쪽 가로벽에 부딪혔을 때
	else if (PosY > mapSize - 26) PosY = mapSize - 50;    //카메라가 아래쪽 가로벽에 부딪혔을 때
	else PosY = PosY - 25;

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			CameraPosX = PosX + j; CameraPosY = PosY + i;  //카메라는 현재 좌표 + 출력되는 인덱스다.
			GoToxy(j * 2, i);  //gotoxy는 콘솔에서 입력할 것이니 그대로 해주면 됨.
			if (map[CameraPosY][CameraPosX] == PLAYER) {  //플레이어를 출력
				SetColor(10);
				printf("□");
				SetColor(15);
			}
			else if (map[CameraPosY][CameraPosX] == FINISH) {  //피니시 장소를 출력
				SetColor(204);
				printf("  ");
				SetColor(15);
			}
			else printf("%s", pMap[map[CameraPosY][CameraPosX]]);  //그 외 벽이나 공간을 출력
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