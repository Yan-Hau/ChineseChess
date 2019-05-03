#pragma once
#include "ConsoleInterface.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef struct _pos {
	int x;
	int y;
} Position;

class Board
{
private:
	short pointerX , pointerY;
	vector<vector<COORD>>  cursor;
	vector<vector<string>> base;
public:
	Board();
	~Board();
	void print();
	void put(Position);
	void put(int , int);
	void setPointer(int , int);
	COORD getPointer();
};
