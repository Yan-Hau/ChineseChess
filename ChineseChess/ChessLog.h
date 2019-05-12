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
public:
	ChessLog();
	~ChessLog();
	void create();
	void downloadLog();
	void record(int [], int);
	void repent();
	void saveLog();
	int* getCurrentChessTable();
	int getCurrentTurn();
public:
	int counter = 0;
};

