#pragma once

#include<stdio.h>
#include<windows.h>
#include<stralign.h>
#include<stdlib.h>
#include<process.h>//Ÿ�̸Ӹ� ������ ���� �����带 ����Ѵ�
#include<conio.h>//�Է� ���۸� �����ִ� �������� _kbhit()�Լ��� ����ؾ� �Ѵ�.
#include<io.h>//���� ���� ������ Ȯ���� ��
#include<direct.h>//������ ���� ��
#include<setjmp.h>//TRY CATCH ETRY THROW�� ����� ��

//��ũ�δ� �ش� ������ ��ü���� �Լ�ó�� ������ �ٲ� �� ���� �ʴ�
#define pause system("pause > nul")//nul ���� ����Ϸ��� �ƹ� Ű �Է� . . .�ȶ� 
#define cls system("cls")//clear screen�� ���� �ܼ�â�� ��� �ؽ�Ʈ ����
//��ġ���� ���� system()
// ���� �ణ �ڵ��ϼ� ���� ������ ��ũ����
//�ҽ� ���� �ۼ��� ; �ٿ��ָ� �ڵ� �ϼ� ��

#define TRY do{ jmp_buf ex_buf__; if (!setjmp(ex_buf__){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__,1)
#define flush for (int i=0;i<100;i++) if(_kbhit()) scanf("%*c",stdin) //�Է¹��۸� �����ִ� 
/*������ �ϳ��� ���� �ȵ� ���� �ϳ��� ������ ���� �ȳ�*/

bool LoadGame(void);

void SetColor(int color);
void CursorView(char show);
void GoToxy(int x, int y);
void GamePlay();



