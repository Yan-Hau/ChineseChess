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
	fstream boardFile;//�ѧ��ɮ�
	fstream notationFile;//�O��(�C�B���)�ɮ�
	vector<vector<int> > boardRecord;//�s���������
	vector<int> boardTurn;
	vector<vector<int> > tempRecord;//�Ȧs���Ѫ�����
	vector<int> tempTurn;
	vector<string> tempRed;//�Ȧs���ѰO��
	vector<string> tempBlack;
public:
	ChessLog();
	~ChessLog();
	void create();//�зs�ɮ�
	void downloadLog();//Ū���e������
	void record(int[], int, COORD, COORD);//������e����
	bool repent();//����
	bool recover();//�_��
	void saveLog();//�x�s����
	int* getCurrentChessTable();
	int getCurrentTurn();
public:
	vector<string> redNotation;//����O��
	vector<string> blackNotation;//�¤�O��
	int counter = 0;
};

