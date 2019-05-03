#include "pch.h"
#include "ConsoleInterface.h"
using namespace std;

int main(void)
{
	//Test
	ConsoleInterface cli;
	cli.initialize(); //初始化大小

	//設定顏色 背景
	ConsoleInterface::setColor(ConsoleInterface::FONT_BLACK | ConsoleInterface::BACK_WHITE);
	cout << "Test~~~" << '\n';
	printf("Test~~~\n");

	//多載ostream 設定顏色 背景
	cout << (ConsoleInterface::FONT_BLUE | ConsoleInterface::BACK_RED) << "Test~~~" << '\n';
	cout << ConsoleInterface::FONT_RED << "Test~~~" << '\n';
	cout << ConsoleInterface::FONT_GREEN << "Test~~~" << '\n';

	//初始值，等效 ConsoleInterface::setColor()
	cout << cli.flag << "test\n";

	//設定顏色+背景，無參數預設為黑底白字
	ConsoleInterface::setColor();
	cout << "Test~~~" << '\n';
	return 0;
}
