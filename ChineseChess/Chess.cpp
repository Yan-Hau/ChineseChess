#include "pch.h"
#include "Chess.h"

/* Static Variable */
int Chess::ChessTable[10][9] =
{
	
};

unsigned int Chess::Turn = 1;//起始方為紅方(代號紅:1 黑:0)

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

		if (ChessTable[targetY][targetX] % 7 == 1) //王見王
			if (x == targetX || y == targetY) //同一線上
				if (!JudgeBetween(targetX, targetY)) //中間沒有棋子
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
			if ((ID > 7 && targetY <= 4) || (ID <= 7 && targetY >= 5)) //過河
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
 int Chess::CheckMate()   //判斷是否將死 與情形
{
	int King_posX[2] = { 0 };
	int King_posY[2] = { 0 };
	int count = 0;
	for (int i = 0; i <= 10; i++) {    //找出雙方主將的座標
		for (int j = 0; j <= 9; j++) {
			if (ChessTable[i][j] % 7 == 1)
			{
				King_posY[count] = i; //King_posY[0] 為將的Y座標  King_posX[1] 為帥的Y座標
 				King_posX[count] = j; //King_posX[0] 為將的X座標  King_posX[1] 為帥的X座標
				count++;
			}
		}
	}
	if (King_posX[0] == King_posX[1])  //如果在同條線上 檢查是否會王見王
	{
		for (int y = King_posY[0] + 1; y < King_posY[1]; y++) {
			if (ChessTable[y][King_posX[0]] != 0) //代表這步棋下完 不會被將軍
				return 0;
		}
		return 1;  //會王見王
	}
	else
	{
		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j <= 9; j++) {
				if (ChessTable[i][j] % 7 >= 4 || (ChessTable[i][j] % 7 == 0 && ChessTable[i][j] != 0)) //檢查 車 馬 包 卒
				{
					x = j;
					y = i;
					MovingTip();
					if (CanMove[King_posY[0]][King_posX[0]])  //下完這步棋 將可以被對方吃掉 代表被紅方將軍
						return 2;
					else if (CanMove[King_posY[1]][King_posX[1]])  //下完這步棋 帥可以被對方吃掉 代表被黑方將軍
						return 3;
				}
			}
		}
	}
}
void Chess::MovingTip()  //提示所選擇的旗子可走的路線
{
	for (int i = 0; i <= 10; i++){
		for (int j = 0; j <= 9; j++){
			if (JudgeMove(j, i) && JudgeChess(j, i) )  //尋找可以走的路線
				CanMove[j][i] = true;
			else
				CanMove[j][i] = false;
		}
	}
}
void Chess::doCheckMate() //檢查會不會被將軍
{
	if (CheckMate() == 0)
		cout << "";
	else if (CheckMate() == 1)
		cout << "王見王";
	else if (CheckMate() == 2)
		cout << "紅方將軍";
	else if (CheckMate() == 3)
		cout << "黑方將軍";
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