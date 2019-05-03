#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <wchar.h>

#define CLI_FONT_LIGHT    0b00001000 //8
#define CLI_FONT_BLACK    0b00000000 //0
#define CLI_FONT_BLUE     0b00000001 //1
#define CLI_FONT_GREEN    0b00000010 //2
#define CLI_FONT_CYAN     0b00000011 //3
#define CLI_FONT_RED      0b00000100 //4
#define CLI_FONT_PURPLE   0b00000101 //5
#define CLI_FONT_YELLOW   0b00000110 //6
#define CLI_FONT_WHITE    0b00000111 //7
#define CLI_BACK_LIGHT    0b10000000 //128
#define CLI_BACK_BLACK    0b00000000 //0
#define CLI_BACK_BLUE     0b00010000 //16
#define CLI_BACK_GREEN    0b00100000 //32
#define CLI_BACK_CYAN     0b00110000 //48
#define CLI_BACK_RED      0b01000000 //64
#define CLI_BACK_PURPLE   0b01010000 //80
#define CLI_BACK_YELLOW   0b01100000 //96
#define CLI_BACK_WHITE    0b01110000 //112

typedef struct {
	WORD color;
} Flag;

class Cmder
{
private:
	HANDLE handle;
	WORD color;

	// Set Console Attribute
public:
	Cmder(HANDLE);
	Cmder();
	~Cmder();
	Flag flag;
	unsigned short originColor();

	static const HANDLE Instance;			  /* Stand Output stream*/
	static COORD setCursor(short x, short y); /* Set cursor position */
	static COORD setCursor(COORD);        /* Set cursor position */
	static COORD getCursor();			  /* Get Now cursor position */
	static unsigned short getColor();     /* Get Now using Color*/
	static bool setColor(WORD color = 7);			  /* Set Background color , fonr color Use value  */
	static bool setColor(Flag flag);	  /* Set Background color , fonr color Use struct */
	static void initialize(int height = 40, int weight = 180); /* Set Command Box height & weight */


// Color Format Struct
public:
	static Flag FONT_LIGHT;
	static Flag	FONT_BLACK;
	static Flag	FONT_BLUE;
	static Flag	FONT_GREEN;
	static Flag	FONT_CYAN;
	static Flag	FONT_RED;
	static Flag	FONT_PURPLE;
	static Flag	FONT_YELLOW;
	static Flag	FONT_WHITE;
	static Flag	BACK_LIGHT;
	static Flag	BACK_BLACK;
	static Flag	BACK_BLUE;
	static Flag	BACK_GREEN;
	static Flag	BACK_CYAN;
	static Flag	BACK_RED;
	static Flag	BACK_PURPLE;
	static Flag	BACK_YELLOW;
	static Flag	BACK_WHITE;
};

/* Define command operator overload */
inline std::ostream& operator << (std::ostream& os, Flag& setting)
{
	Cmder::setColor(setting.color);
	return os;
}

inline std::ostream& operator << (std::ostream& os, Flag&& setting)
{
	Cmder::setColor(setting.color);
	return os;
}

inline Flag operator | (Flag base, Flag adder)
{
	return Flag{ static_cast<WORD> (base.color | adder.color) };
}







