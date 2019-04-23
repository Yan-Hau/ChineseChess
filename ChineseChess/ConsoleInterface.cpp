#include "pch.h"
#include "ConsoleInterface.h"


ConsoleInterface::ConsoleInterface()
{
	this->handle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->color = ConsoleInterface::getColor();
	this->flag = { this->color };
}

ConsoleInterface::ConsoleInterface(HANDLE h)
{
	this->handle = h;
	this->color = ConsoleInterface::getColor();
	this->flag = { this->color };
}

ConsoleInterface::~ConsoleInterface()
{
}

WORD ConsoleInterface::originColor()
{
	return this->color;
}

/// Static function
/* Get Stand Output stream */
const HANDLE ConsoleInterface::Instance = GetStdHandle(STD_OUTPUT_HANDLE);

/* Get Now using Bacground color, font color */
WORD ConsoleInterface::getColor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(ConsoleInterface::Instance, &csbiInfo);
	return csbiInfo.wAttributes;
}

/* Set Bacground color, font color By color code */
bool ConsoleInterface::setColor(WORD color)
{
	return SetConsoleTextAttribute(ConsoleInterface::Instance, color);
}

/* Set Background color , fonr color By Flag*/
bool ConsoleInterface::setColor(Flag flag)
{
	return SetConsoleTextAttribute(ConsoleInterface::Instance, flag.color);
}

/* Get Now Cursor position */
COORD ConsoleInterface::getCursor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(ConsoleInterface::Instance, &csbiInfo);
	return csbiInfo.dwCursorPosition;
}

/* Set Now Cursor position */
COORD ConsoleInterface::setCursor(short x, short y)
{
	static COORD c; c.X = x; c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return COORD{ x, y };
}

void ConsoleInterface::initialize(int height, int weight) /* Set Command Box height & weight */
{
	char buffer[256];
	sprintf_s(buffer, "mode con cols=%d lines=%d", weight, height);
	system(buffer);
}

Flag ConsoleInterface::FONT_LIGHT = { 8 };
Flag ConsoleInterface::FONT_BLACK = { 0 };
Flag ConsoleInterface::FONT_BLUE = { 1 };
Flag ConsoleInterface::FONT_GREEN = { 2 };
Flag ConsoleInterface::FONT_CYAN = { 3 };
Flag ConsoleInterface::FONT_RED = { 4 };
Flag ConsoleInterface::FONT_PURPLE = { 5 };
Flag ConsoleInterface::FONT_YELLOW = { 6 };
Flag ConsoleInterface::FONT_WHITE = { 7 };
Flag ConsoleInterface::BACK_LIGHT = { 128 };
Flag ConsoleInterface::BACK_BLACK = { 0 };
Flag ConsoleInterface::BACK_BLUE = { 16 };
Flag ConsoleInterface::BACK_GREEN = { 32 };
Flag ConsoleInterface::BACK_CYAN = { 48 };
Flag ConsoleInterface::BACK_RED = { 64 };
Flag ConsoleInterface::BACK_PURPLE = { 80 };
Flag ConsoleInterface::BACK_YELLOW = { 96 };
Flag ConsoleInterface::BACK_WHITE = { 112 };