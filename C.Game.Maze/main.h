#pragma once

#include<stdio.h>
#include<windows.h>
#include<stralign.h>
#include<stdlib.h>

//메크로는 해당 변수를 대체하지 함수처럼 변수를 바꿀 수 있지 않다
#define pause system("pause > nul")//nul 들어가면 계속하려면 아무 키 입력 . . .안뜸 
#define cls system("cls")//clear screen의 약자 콘솔창에 모든 텍스트 삭제
//배치파일 명렁어 system()
// 현재 약간 자동완성 같은 느낌의 메크로임
//소스 파일 작성시 ; 붙여주면 자동 완성 됨


void SetColor(int color);
void CursorView(char show);
void GoToxy(int x, int y);
void GamePlay();