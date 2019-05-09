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
	bool state;										 //true為活，false為死棋
	bool beChoice;
	bool JudgeMove   (short targetX, short targetY); //判斷移動是否符合棋盤規定
	bool JudgeChess  (short targetX, short targetY); //判斷走棋吃棋是否符合棋種
	int  JudgeBetween(short targetX, short targetY); //兩點間棋子數目

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
	bool ChangeChess(short targetX, short targetY);   //吃棋走棋
	void operator=(Chess&);

public:
	static void PrintTable(); //印棋盤
	static unsigned int Turn; //回合
	static int ChessTable[10][9];    //文字狀態
	static bool isEnd; //遊戲狀態
};