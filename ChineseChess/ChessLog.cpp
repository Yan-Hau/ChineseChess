#include "pch.h"
#include "ChessLog.h"

ChessLog::ChessLog()
{

}
ChessLog::~ChessLog()
{

}
//Create new file to store
void ChessLog::create()
{
	string dir = "./ChessLog", fileName = "ChessLog\\log.txt";
	if (_access(dir.c_str(), 6) == -1)/* Create new folder */
	{
#ifdef WIN32
		_mkdir(dir.c_str());
#endif
#ifdef linux 
		mkdir(dir.c_str(), 0777);
#endif
	}

	recordFile.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);  /* Create new file */
}
//Load all chess score from the txt 
void ChessLog::downloadLog()
{
	allRecord.clear();
	turn.clear();
	while (!recordFile.eof())
	{
		int tempTurn;
		vector<int> tempRecord;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int chess;
				recordFile >> chess;
				tempRecord.push_back(chess);
			}
		}
		recordFile >> tempTurn;

		allRecord.push_back(tempRecord);
		turn.push_back(tempTurn);
	}
	counter = allRecord.size();
}
//Record current chess board
void ChessLog::record(int ChessTable[], int Turn)
{
	tempRecord.clear();
	tempTurn.clear();
	int tempTurn = Turn;
	vector<int> tempRecord;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tempRecord.push_back(ChessTable[9 * i + j]);
		}
	}
	allRecord.push_back(tempRecord);
	turn.push_back(tempTurn);
	counter++;
}
//Repent current chess board
void ChessLog::repent()
{
	if (allRecord.size() >= 1)
	{
		tempRecord.push_back(allRecord[allRecord.size() - 1]);
		tempTurn.push_back(turn[turn.size() - 1]);
		allRecord.pop_back();
		turn.pop_back();
		counter--;
	}
}
//Recover the repent
void ChessLog::recover()
{
	if (tempRecord.size() >= 1)
	{
		allRecord.push_back(tempRecord[tempRecord.size() - 1]);
		turn.push_back(tempTurn[tempTurn.size() - 1]);
		tempRecord.pop_back();
		tempTurn.pop_back();
		counter++;
	}
}
//Clear the file and save chess score
void ChessLog::saveLog()
{
	fstream file(FILE_NAME, ios::out | ios::trunc);
	for (int n = 0; n < allRecord.size(); n++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				file << allRecord[n][9 * i + j] << ((j != 8) ? (" ") : "");
			}
			file << endl;
		}
		if(n < allRecord.size() - 1)
			file << turn[n] << endl;
		else
			file << turn[n];
	}
}
//Get last chess log
int* ChessLog::getCurrentChessTable()
{
	int lastRecord[90];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			lastRecord[9 * i + j] = allRecord[allRecord.size() - 1][9 * i + j];
		}
	}
	return lastRecord;
}
//Get last turn
int ChessLog::getCurrentTurn()
{
	return turn[turn.size() - 1];
}
