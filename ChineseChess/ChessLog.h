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
	vector<vector<int> > tempRecord;//�Ȧs���Ѫ�����
	vector<int> tempTurn;
public:
	ChessLog();
	~ChessLog();
	void create();//�зs�ɮ�
	void downloadLog();//Ū���e������
	void record(int [], int);//������e����
	void repent();//����
	void recover();//�_��
	void saveLog();//�x�s����
	int* getCurrentChessTable();
	int getCurrentTurn();
public:
	int counter = 0;
};

