#include "pch.h"
#include "ConsoleInterface.h"


Cmder::Cmder()
{
	this->handle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->color = Cmder::getColor();
	this->flag = { this->color };
}

Cmder::Cmder(HANDLE h)
{
	this->handle = h;
	this->color = Cmder::getColor();
	this->flag = { this->color };
}

Cmder::~Cmder()
{
}

WORD Cmder::originColor()
{
	return this->color;
}

/// Static function
/* Get Stand Output stream */
const HANDLE Cmder::Instance = GetStdHandle(STD_OUTPUT_HANDLE);

/* Get Now using Bacground color, font color */
WORD Cmder::getColor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(Cmder::Instance, &csbiInfo);
	return csbiInfo.wAttributes;
}


/* Set Bacground color, font color By color code */
bool Cmder::setColor(WORD color)
{
	return SetConsoleTextAttribute(Cmder::Instance, color);
}

/* Set Background color , fonr color By Flag*/
bool Cmder::setColor(Flag flag)
{
	return SetConsoleTextAttribute(Cmder::Instance, flag.color);
}

/* Get Now Cursor position */
COORD Cmder::getCursor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(Cmder::Instance, &csbiInfo);
	return csbiInfo.dwCursorPosition;
}

/* Set Now Cursor position */
COORD Cmder::setCursor(short x, short y)
{
	static COORD c; c.X = x; c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return COORD{ x, y };
}

COORD Cmder::setCursor(COORD pos)
{
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return COORD{ pos.X, pos.Y };
}

void Cmder::initialize(int height, int weight) /* Set Command Box height & weight */
{
	char buffer[256];
	sprintf_s(buffer, "mode con cols=%d lines=%d", weight, height);
	system(buffer);
}

Flag Cmder::FONT_LIGHT = { 8 };
Flag Cmder::FONT_BLACK = { 0 };
Flag Cmder::FONT_BLUE = { 1 };
Flag Cmder::FONT_GREEN = { 2 };
Flag Cmder::FONT_CYAN = { 3 };
Flag Cmder::FONT_RED = { 4 };
Flag Cmder::FONT_PURPLE = { 5 };
Flag Cmder::FONT_YELLOW = { 6 };
Flag Cmder::FONT_WHITE = { 7 };
Flag Cmder::BACK_LIGHT = { 128 };
Flag Cmder::BACK_BLACK = { 0 };
Flag Cmder::BACK_BLUE = { 16 };
Flag Cmder::BACK_GREEN = { 32 };
Flag Cmder::BACK_CYAN = { 48 };
Flag Cmder::BACK_RED = { 64 };
Flag Cmder::BACK_PURPLE = { 80 };
Flag Cmder::BACK_YELLOW = { 96 };
Flag Cmder::BACK_WHITE = { 112 };