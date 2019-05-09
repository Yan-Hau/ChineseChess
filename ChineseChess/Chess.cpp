#include "pch.h"
#include "Chess.h"

/* Static Variable */
int Chess::ChessTable[10][9] = 
{
	4,5,3,2,1,2,3,5,4,
	0,0,0,0,0,0,0,0,0,
	0,6,0,0,0,0,0,6,0,
	7,0,7,0,7,0,7,0,7,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	14,0,14,0,14,0,14,0,14,
	0,13,0,0,0,0,0,13,0,
	0,0,0,0,0,0,0,0,0,
	11,12,10,9,8,9,10,12,11
};

unsigned int Chess::Turn = 1;

bool Chess::isEnd = false;

void Chess::PrintTable()
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 9; x++) {
			//cout << cout.width(2) << ChessTable[y][x] << " ";
			printf("%-2d ", ChessTable[y][x]);
		}
		cout << endl;
	}
}

//建構式
Chess::Chess(short X, short Y, short ID , string Name, bool State , short Camp)
{
	this->x = X;
	this->y = Y;
	this->name = Name;
	this->ID = ID;
	this->state = State;
	this->camp = Camp;
	this->beChoice = false;
	Chess::ChessTable[y][x] = this->ID;
}
Chess::Chess()
{
	this->x = -1;
	this->y = -1;
	this->ID = 0;
	this->name = "？";
	this->state = false;
	this->beChoice = false;
	this->camp = 2;
}

//判斷移動是否符合棋盤規定
bool Chess::JudgeMove(short targetX, short targetY)
{
	//目標位置和起始位置相同
	if (this->x == targetX && this->y == targetY)
	{
		cout << "a目標位置和起始位置相同";// << endl;
		return false;
	}

	//起始位置沒有棋子
	if (ChessTable[y][x] == 0)
	{
		cout << "b起始位置沒有棋子";// << endl;
		return false;
	}
		
	//陣營與當前玩家不同
	if (this->camp != Chess::Turn)
	{
		cout << "c陣營與當前玩家不同";// << endl;
		return false;
	}

	//目標位置超出棋盤範圍
	if (targetX < 0 || targetX > 8 ||targetY < 0 || targetY > 9)
	{
		cout << "d目標位置超出棋盤範圍";// << endl;
		return false;
	}


	//目標位置與當前玩家同陣營（無法吃棋）
	if (ChessTable[targetY][targetX] != 0 && (ChessTable[targetY][targetX]-1)/7 == Chess::Turn)
	{
		cout << "e同陣營（無法吃棋）";// << endl;
		return false;
	}

	return true;
}

//判斷走棋吃棋是否符合棋種
bool Chess::JudgeChess(short targetX, short targetY)
{
	//將帥
	if (ID % 7 == 1)
	{
		int tmpX = targetX - x;
		int tmpY = targetY - y;
		if ((tmpX * tmpX + tmpY * tmpY == 1) //一次走一步
			&& (targetX <= 5) && (targetX >= 3)
			&& (targetY >= 7 || targetY <= 2)) //不出九宮
			return true;
	}

	//士仕
	else if (ID % 7 == 2)
	{
		int tmpX = targetX - x;
		int tmpY = targetY - y;
		if ((tmpX * tmpX + tmpY * tmpY == 2) //走斜
			&& (targetX <= 5) && (targetX >= 3)
			&& (targetY >= 7 || targetY <= 2)) //不出九宮
			return true;
	}

	//象相
	else if (ID % 7 == 3)
	{
		int tmpX = targetX - x;
		int tmpY = targetY - y;

		if (tmpX * tmpX + tmpY * tmpY == 8 //走田
			&& ChessTable[y+tmpY/2][x+tmpX/2] == 0) //不踩象眼

			//不過河
			if ((ID > 7 && targetY > 4) || (ID <= 7 && targetY < 5))
				return true;
	}

	//車俥
	else if (ID % 7 == 4)
	{
		if (x == targetX || y == targetY) //同一線上
			if (!JudgeBetween(targetX, targetY)) //中間沒有棋子
				return true;
	}

	//馬傌
	else if (ID % 7 == 5)
	{
		int tmpX = targetX - x;
		int tmpY = targetY - y;

		if (tmpX * tmpX + tmpY * tmpY == 5 //走日
			&& ChessTable[(y+tmpY/2)][x+tmpX/2] == 0) //沒有憋馬腳

			return true;
	}

	//包炮
	else if (ID % 7 == 6)
	{
		if (ChessTable[targetY][targetX] == 0) //若不用吃子
		{
			if (x == targetX || y == targetY) //同一線上
				if (!JudgeBetween(targetX, targetY)) //中間沒有棋子
					return true;
		}
		else //若要吃子
		{
			if (x == targetX || y == targetY) //同一線上
				if (JudgeBetween(targetX, targetY) == 1) //跳吃
					return true;
		}
	}

	//卒兵
	else if (ID % 7 == 0)
	{
		int tmpX = targetX - x;
		int tmpY = targetY - y;

		if (tmpX * tmpX + tmpY * tmpY == 1) //一次走一步
		{
			if ((ID > 7 && targetY < 4) || (ID <= 7 && targetY > 5)) //過河
				return true;

			else //沒過河
			{
				//只能往前走
				if ((ID > 7 && tmpY == -1) || (ID <= 7 && tmpY == 1))
					return true;
			}
		}
	}

	cout << "e";// << endl;
	return false;
}

//兩點間棋子數目
int Chess::JudgeBetween(short targetX, short targetY)
{
	int num = 0;
	//若兩點x軸相等
	if (x == targetX)
	{
		if (y > targetY)
		{
			for (int i = targetY + 1; i < y; i++)
			{
				if (ChessTable[i][x] != 0) num++;
			}
		}
		else
		{
			for (int i = y + 1; i < targetY; i++)
			{
				if (ChessTable[i][x] != 0) num++;
			}
		}
	}
	//若兩點y軸相等
	else if (y == targetY)
	{
		if (x > targetX)
		{
			for (int i = targetX + 1; i < x; i++)
			{
				if (ChessTable[y][i] != 0) num++;
			}
		}
		else
		{
			for (int i = x + 1; i < targetX; i++)
			{
				if (ChessTable[y][i] != 0) num++;
			}
		}
	}
	return num;
}

//走路
bool Chess::ChangeChess(short targetX, short targetY)
{
	Cmder::setCursor(0, 27);
	if (JudgeMove(targetX, targetY) && JudgeChess(targetX, targetY))
	{
		//吃棋
		if (ChessTable[targetY][targetX] != 0)
		{
			//如果將或帥被吃掉，遊戲結束
			if (ChessTable[targetY][targetX] == 1 || ChessTable[targetY][targetX] == 8)
			{
				isEnd = true;
				cout << "遊戲結束";
			}

			ChessTable[targetY][targetX] = 0;
			state = false; //死棋
		}

		//移動
		ChessTable[targetY][targetX] = ChessTable[y][x];
		ChessTable[y][x] = 0;
		x = targetX;
		y = targetY;

		return true;
	}
	else
	{
		cout << "輸入錯誤" << endl;
		return false;
	}
}

// 取得Private
bool Chess::isLife()
{
	return this->state;
}

bool Chess::isCurrent()
{
	return this->beChoice;
}

void Chess::setCurrent(bool choice)
{
	this->beChoice = choice;
}

void Chess::operator=(Chess& ref)
{
	this->x = ref.x;
	this->y = ref.y;
	this->ID = ref.ID;
	this->name = ref.name;
	this->state = ref.state;
	this->camp = ref.camp;

}

string Chess::getName()
{
	return this->name;
}

short Chess::getID()
{
	return this->ID;
}

short Chess::getCamp()
{
	return this->camp;
}

COORD Chess::getPosition()
{
	return COORD{ this->x , this->y };
}