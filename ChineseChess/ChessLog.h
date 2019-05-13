#pragma once
#include "Chess.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>
#define FILE_NAME "ChessLog\\log.txt"
using namespace std;

class ChessLog
{
private:
	fstream recordFile;
	vector<vector<int> > allRecord;
	vector<int> turn;
	vector<vector<int> > tempRecord;//暫存悔棋的局面
	vector<int> tempTurn;
public:
	ChessLog();
	~ChessLog();
	void create();//創新檔案
	void downloadLog();//讀取前次紀錄
	void record(int [], int);//紀錄當前局面
	void repent();//悔棋
	void recover();//復原
	void saveLog();//儲存紀錄
	int* getCurrentChessTable();
	int getCurrentTurn();
public:
	int counter = 0;
};

