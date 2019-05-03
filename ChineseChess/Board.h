#pragma once
#
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
	vector<vector<string>> state;
	vector<vector<string>> base;
	vector<vector<string>> hint;
public:
	Board();
	~Board();
	void print();
	void put(Position);
	void put(int , int);
};
