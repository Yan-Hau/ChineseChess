#pragma once
#include "Chess.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>
#include <cmath>
#define BOARD_FILE_NAME "ChessLog\\log.txt"
#define NOTATION_FILE_NAME "NotationLog\\log.txt"
using namespace std;

class ChessLog
{
private:
	fstream boardFile;//棋局檔案
	fstream notationFile;//記譜(每步表示)檔案
	vector<vector<int> > boardRecord;//存放全部棋譜
	vector<int> boardTurn;
	vector<vector<int> > tempRecord;//暫存悔棋的局面
	vector<int> tempTurn;
	vector<string> tempRed;//暫存悔棋記譜
	vector<string> tempBlack;
public:
	ChessLog();
	~ChessLog();
	void create();//創新檔案
	void downloadLog();//讀取前次紀錄
	void record(int[], int, COORD, COORD);//紀錄當前局面
	bool repent();//悔棋
	bool recover();//復原
	void saveLog();//儲存紀錄
	int* getCurrentChessTable();
	int getCurrentTurn();
public:
	vector<string> redNotation;//紅方記譜
	vector<string> blackNotation;//黑方記譜
	int counter = 0;
};

