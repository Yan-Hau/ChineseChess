
Chinese Chess 中國象棋 簡易說明
===


Class : ConsoleInterface (基於Windows.h)
---

```cpp
Feature: Guess the word

  # Define Static Function:
    /* Stand Output stream*/
    static const HANDLE Instance;
    
    /* Set cursor position */
    static COORD setCursor(short x, short y);
    
    /* Get Now cursor position */
    static COORD getCursor();
    
    /* Get Now using Color*/
    static unsigned short getColor();
    
    /* Set Background color , fonr color use color code*/
    static bool setColor(unsigned short color = 7); 
    
    /* Set Background color , fonr color use Flag*/
    static bool setColor(Flag flag);
    
    /* Set Command Box height & weight */
    static void initialize(int height = 40, int weight = 180); 

    /*Set StandOutput stream font-color */
    inline std::ostream& operator << (std::ostream& os, Flag& setting)
    inline std::ostream& operator << (std::ostream& os, Flag&& setting)
    inline Flag operator | (Flag base, Flag adder)
    
    /* 色碼表 */
    #define CLI_FONT_LIGHT    0b00001000
    #define CLI_FONT_BLACK    0b00000000
    #define CLI_FONT_BLUE     0b00000001
    #define CLI_FONT_GREEN    0b00000010
    #define CLI_FONT_CYAN     0b00000011
    #define CLI_FONT_RED      0b00000100
    #define CLI_FONT_PURPLE   0b00000101
    #define CLI_FONT_YELLOW   0b00000110
    #define CLI_FONT_WHITE    0b00000111
    #define CLI_BACK_LIGHT    0b10000000
    #define CLI_BACK_BLACK    0b00000000
    #define CLI_BACK_BLUE     0b00010000
    #define CLI_BACK_GREEN    0b00100000
    #define CLI_BACK_CYAN     0b00110000
    #define CLI_BACK_RED      0b01000000
    #define CLI_BACK_PURPLE   0b01010000
    #define CLI_BACK_YELLOW   0b01100000
    #define CLI_BACK_WHITE    0b01110000
```

Sample Code
---
```cpp
#include "pch.h"
#include "ConsoleInterface.h"
using namespace std;

int main(void)
{
	ConsoleInterface cli;
	cli.initialize(); //初始化大小
	cli.initialize(200, 100); //設定高200、寬100 之文字介面

	/* 使用靜態方法設定 背景顏色 文字顏色  */


	ConsoleInterface::setColor(CLI_BACK_WHITE | CLI_FONT_BLACK); //白底黑字
	cout << "Red Font" << '\n';
	printf("Red Font\n");


	ConsoleInterface::setColor(CLI_BACK_WHITE | CLI_FONT_RED); //白底紅字
	cout << "Red Font , White background" << '\n';
	printf("Red Font , White background\n");

	/* 使用ostream旗標設定 背景顏色 文字顏色  */
	cout << ConsoleInterface::FONT_BLUE << "Test" << '\n'; //藍字
	cout << (ConsoleInterface::FONT_BLUE | ConsoleInterface::BACK_WHITE) << "Test" << '\n'; //白底藍字

    cout << "Test" << '\n' //未更改設定，仍為白底藍字

	/* 無參數，設為黑底白字(預設值) */
	ConsoleInterface::setColor();
	cout << "Test" << '\n';

	/* 初始值，等效 ConsoleInterface::setColor() */
	cout << cli.flag << "test\n";
    
    /* 設定游標位置 */
    ConsoleInterface::setCursor(30, 0);
	cout << "From 30 word";
	ConsoleInterface::setCursor(30, 1);
	cout << "From 30 word & next line.";
    
    
	return 0;
}

    
```
