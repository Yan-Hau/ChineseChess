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
	string dir1 = "./ChessLog", fileName1 = "ChessLog\\log.txt", dir2 = "./NotationLog", fileName2 = "NotationLog\\log.txt";;
	if (_access(dir1.c_str(), 6) == -1)/* Create new folder */
	{
#ifdef WIN32
		_mkdir(dir1.c_str());
#endif
#ifdef linux 
		mkdir(dir1.c_str(), 0777);
#endif
	}
	boardFile.open(fileName1.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);  /* Create new file */

	if (_access(dir2.c_str(), 6) == -1)/* Create new folder */
	{
#ifdef WIN32
		_mkdir(dir2.c_str());
#endif
#ifdef linux 
		mkdir(dir2.c_str(), 0777);
#endif
	}
	notationFile.open(fileName2.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);  /* Create new file */
}
//Load all chess score from the txt 
void ChessLog::downloadLog()
{
	boardRecord.clear();
	boardTurn.clear();
	while (!boardFile.eof())
	{
		int tempTurn;
		vector<int> tempRecord;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int chess;
				boardFile >> chess;
				tempRecord.push_back(chess);
			}
		}
		boardFile >> tempTurn;

		boardRecord.push_back(tempRecord);
		boardTurn.push_back(tempTurn);
	}
	counter = boardRecord.size();

	redNotation.clear();
	blackNotation.clear();
	int n = 0;
	while (!notationFile.eof())
	{
		string notation;
		notationFile >> notation;
		if (n % 2 == 0)
			redNotation.push_back(notation);
		else
			blackNotation.push_back(notation);
		n++;
	}
}
//Record current chess board
void ChessLog::record(int ChessTable[], int Turn, COORD notation, COORD currentXY)
{
	tempRecord.clear();
	tempTurn.clear();
	tempRed.clear();
	tempBlack.clear();
	int tempTurn = Turn;
	vector<int> tempRecord;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tempRecord.push_back(ChessTable[9 * i + j]);
		}
	}
	boardRecord.push_back(tempRecord);
	boardTurn.push_back(tempTurn);

	COORD laststep = { currentXY.X + notation.X,currentXY.Y + notation.Y };
	string name[] = { "0" ,"將","士","象","車","馬","包","卒","帥","仕","相","車","傌","炮","兵" };
	string step = name[ChessTable[currentXY.Y * 9 + currentXY.X]];
	if (counter % 2 == 0)
	{
		string number[] = { "九","八","七","六","五","四","三","二","一" };
		step += number[laststep.X];
		if (notation.Y > 0 && notation.X != 0)//進
			step += ("進" + number[currentXY.X]);
		else if (notation.Y < 0 && notation.X != 0)//退
			step += ("退" + number[currentXY.X]);
		else if (notation.Y == 0 && notation.X != 0)//平
			step += ("平" + number[currentXY.X]);
		else if (notation.Y > 0 && notation.X == 0)//前
			step += ("進" + number[8 - abs(notation.Y)]);
		else if (notation.Y < 0 && notation.X == 0)//後
			step += ("退" + number[8 - abs(notation.Y)]);
		redNotation.push_back(step);
	}
	else
	{
		string number[] = { "1","2","3","4","5","6","7","8","9" };
		step += number[laststep.X];
		if (notation.Y < 0 && notation.X != 0)//進
			step += ("進" + number[currentXY.X]);
		else if (notation.Y > 0 && notation.X != 0)//退
			step += ("退" + number[currentXY.X]);
		else if (notation.Y == 0 && notation.X != 0)//平
			step += ("平" + number[currentXY.X]);
		else if (notation.Y < 0 && notation.X == 0)//前
			step += ("進" + number[abs(notation.Y) - 1]);
		else if (notation.Y > 0 && notation.X == 0)//後
			step += ("退" + number[abs(notation.Y) - 1]);
		blackNotation.push_back(step);
	}
	counter++;

}
//Repent current chess board
bool ChessLog::repent()
{
	if (boardRecord.size() >= 1)
	{
		if (counter % 2 == 1)
		{
			tempRed.push_back(redNotation[redNotation.size() - 1]);
			redNotation.pop_back();
		}
		else
		{
			tempBlack.push_back(blackNotation[blackNotation.size() - 1]);
			blackNotation.pop_back();
		}

		tempRecord.push_back(boardRecord[boardRecord.size() - 1]);
		tempTurn.push_back(boardTurn[boardTurn.size() - 1]);
		boardRecord.pop_back();
		boardTurn.pop_back();
		counter--;
		return 1;
	}
	return 0;
}
//Recover the repent
bool ChessLog::recover()
{
	if (tempRecord.size() >= 1)
	{
		if (counter % 2 == 0)
		{
			redNotation.push_back(tempRed[tempRed.size() - 1]);
			tempRed.pop_back();
		}
		else
		{
			blackNotation.push_back(tempBlack[tempBlack.size() - 1]);
			tempBlack.pop_back();
		}

		boardRecord.push_back(tempRecord[tempRecord.size() - 1]);
		boardTurn.push_back(tempTurn[tempTurn.size() - 1]);
		tempRecord.pop_back();
		tempTurn.pop_back();
		counter++;
		return 1;
	}
	return 0;
}
//Clear the file and save chess score
void ChessLog::saveLog()
{
	fstream file1(BOARD_FILE_NAME, ios::out | ios::trunc);
	for (int n = 0; n < boardRecord.size(); n++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				file1 << boardRecord[n][9 * i + j] << ((j != 8) ? (" ") : "");
			}
			file1 << endl;
		}
		if (n < boardRecord.size() - 1)
			file1 << boardTurn[n] << endl;
		else
			file1 << boardTurn[n];
	}

	fstream file2(NOTATION_FILE_NAME, ios::out | ios::trunc);
	for (int n = 0, a = 0, b = 0; n < redNotation.size() + blackNotation.size(); n++)
	{
		if (n % 2 == 0)
		{
			if (n == redNotation.size() + blackNotation.size() - 1)
				file2 << redNotation[a++];
			else
				file2 << redNotation[a++] << endl;
		}
		else
		{
			if (n == redNotation.size() + blackNotation.size() - 1)
				file2 << blackNotation[b++];
			else
				file2 << blackNotation[b++] << endl;
		}
	}

	printf("%100c", ' ');
	Cmder::setCursor(0, 27);
	
	

	
	cout << "存檔進度[";

	COORD _current = Cmder::getCursor();
	Cmder::setCursor(_current.X + 50, _current.Y);
	cout << "]";
	Cmder::setCursor(_current);

	for (int i = 0; i < 50; ++i)
	{
		cout << "=";
		Sleep(rand()%100);
	}
	cout << "] 存檔成功！";
	Sleep(500);
	
}
//Get last chess log
int* ChessLog::getCurrentChessTable()
{
	int lastRecord[90];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			lastRecord[9 * i + j] = boardRecord[boardRecord.size() - 1][9 * i + j];
		}
	}
	return lastRecord;
}
//Get last turn
int ChessLog::getCurrentTurn()
{
	return boardTurn[boardTurn.size() - 1];
}
