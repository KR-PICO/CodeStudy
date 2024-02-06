#pragma once

#include<stdio.h>
#include<windows.h>
#include<stralign.h>
#include<stdlib.h>
#include<process.h>//타이머를 돌리기 위해 쓰레드를 사용한다
#include<conio.h>//입력 버퍼를 지워주는 과정에서 _kbhit()함수를 사용해야 한다.
#include<io.h>//파일 존재 유무를 확인할 때
#include<direct.h>//폴더를 만들 때
#include<setjmp.h>//TRY CATCH ETRY THROW를 사용할 때

//메크로는 해당 변수를 대체하지 함수처럼 변수를 바꿀 수 있지 않다
#define pause system("pause > nul")//nul 들어가면 계속하려면 아무 키 입력 . . .안뜸 
#define cls system("cls")//clear screen의 약자 콘솔창에 모든 텍스트 삭제
//배치파일 명렁어 system()
// 현재 약간 자동완성 같은 느낌의 메크로임
//소스 파일 작성시 ; 붙여주면 자동 완성 됨

#define TRY do{ jmp_buf ex_buf__; if (!setjmp(ex_buf__){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__,1)
#define flush for (int i=0;i<100;i++) if(_kbhit()) scanf("%*c",stdin) //입력버퍼를 지워주는 
/*위에꺼 하나도 이해 안됨 띄어쓰기 하나로 오류가 나고 안남*/

bool LoadGame(void);

void SetColor(int color);
void CursorView(char show);
void GoToxy(int x, int y);
void GamePlay();



