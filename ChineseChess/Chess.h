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
	bool JudgeMove(short targetX, short targetY); //判斷移動是否符合棋盤規定
	bool JudgeChess(short targetX, short targetY); //判斷走棋吃棋是否符合棋種
	int  JudgeBetween(short targetX, short targetY); //兩點間棋子數目
	bool CanMove[10][9] = { {false},{false},{false},{false},{false},{false},{false},{false},{false},{false} };  //用來存取可以走的點
public:
	Chess(short X, short Y, short ID, string Name, bool State, short Camp);
	Chess();
	~Chess() {}
	bool isLife();
	bool isCurrent();
	void setCurrent(bool);
	string getName();
	short getID();
	short getCamp();
	COORD getPosition();
	COORD ChangeChess(short targetX, short targetY);   //吃棋走棋
	void operator=(Chess&);
	void doCheckMate(); //檢查會不會被將軍
	int CheckMate();  //檢查被將軍的情形
	void MovingTip();  //下棋提示
public:
	static void PrintTable(); //印棋盤
	static unsigned int Turn; //回合
	static int ChessTable[10][9];    //文字狀態
	static bool isEnd; //遊戲狀態
};