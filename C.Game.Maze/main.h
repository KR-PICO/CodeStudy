#pragma once

#include<stdio.h>
#include<windows.h>
#include<stralign.h>
#include<stdlib.h>

//��ũ�δ� �ش� ������ ��ü���� �Լ�ó�� ������ �ٲ� �� ���� �ʴ�
#define pause system("pause > nul")//nul ���� ����Ϸ��� �ƹ� Ű �Է� . . .�ȶ� 
#define cls system("cls")//clear screen�� ���� �ܼ�â�� ��� �ؽ�Ʈ ����
//��ġ���� ���� system()
// ���� �ణ �ڵ��ϼ� ���� ������ ��ũ����
//�ҽ� ���� �ۼ��� ; �ٿ��ָ� �ڵ� �ϼ� ��


void SetColor(int color);
void CursorView(char show);
void GoToxy(int x, int y);
void GamePlay();