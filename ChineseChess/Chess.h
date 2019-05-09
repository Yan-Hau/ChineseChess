#pragma once
#include "ConsoleInterface.h"
#include <iostream>
#include <string>
using namespace std;

class Chess
{

private:
	short camp;
	short x, y;
	short ID;
	string name;
	bool state;										 //true�����Afalse������
	bool beChoice;
	bool JudgeMove   (short targetX, short targetY); //�P�_���ʬO�_�ŦX�ѽL�W�w
	bool JudgeChess  (short targetX, short targetY); //�P�_���ѦY�ѬO�_�ŦX�Ѻ�
	int  JudgeBetween(short targetX, short targetY); //���I���Ѥl�ƥ�

public:
	Chess(short X, short Y, short ID, string Name, bool State , short Camp);
	Chess();
	~Chess() {}
	bool isLife();
	bool isCurrent();
	void setCurrent(bool);
	string getName();
	short getID();
	short getCamp();
	COORD getPosition();
	bool ChangeChess(short targetX, short targetY);   //�Y�Ѩ���
	void operator=(Chess&);

public:
	static void PrintTable(); //�L�ѽL
	static unsigned int Turn; //�^�X
	static int ChessTable[10][9];    //��r���A
	static bool isEnd; //�C�����A
};