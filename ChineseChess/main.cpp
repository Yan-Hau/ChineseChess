#include "pch.h"
#include "ConsoleInterface.h"
#include "Board.h"
#include <functional>
using namespace std;

int main()
{
	/* Game System Object */
	Cmder box;
	Board board;
	box.initialize(35, 100);
	system("COLOR 07");
	
	/* Variable initialize */
	COORD menuPosition[] = { {56,11} , {56,13} , {56,15} };
	int keypress, menuOffset = 0, functionOffset = 0;
	string menu[] = { "開始遊戲" , "讀取紀錄" , "結束遊戲" };
	function<void()> menuFunction[] = {
		[&board]() -> void {
			Cmder::setCursor(COORD{0,0});
			board.print();
		},

		[]() -> void {
			Cmder::setCursor(COORD{0,20});
			cout << "00002";
		},

		[]() -> void {
			Cmder::setCursor(COORD{0,20});
			cout << "00003";
		},
	};

	/* High-light Current selected option */
	auto select = [&menuPosition , &menu](int offset) -> void {
		Cmder::setCursor(menuPosition[offset]);
		Cmder::setColor(CLI_FONT_CYAN);
		cout << menu[offset];
		Cmder::setCursor(menuPosition[offset]);
	};

	cout << "\n\n";
	cout << "    ######   #     #    #####   ###     #   ######   ######   ######    "	<< '\n';
	cout << "    #        #     #      #     #  #    #   #        #        #         "	<< '\n';
	cout << "    #        #     #      #     #  #    #   #        #        #         "	<< '\n';
	cout << "    #        #######      #     #   #   #   #####    ######   #####     "	<< '\n';
	cout << "    #        #     #      #     #    #  #   #             #   #         "	<< '\n';
	cout << "    #        #     #      #     #     # #   #             #   #         "	<< '\n';
	cout << "    ######   #     #    #####   #     ###   ######   ######   ######    "	<< '\n';
	cout << "                                                                        "	<< '\n';
	cout << "    ######   #     #    ######   ######   ######                        "	<< '\n';
	cout << "    #        #     #    #        #        #             開始遊戲        "	<< '\n';
	cout << "    #        #     #    #        #        #                             "	<< '\n';
	cout << "    #        #######    #####    ######   ######        讀取紀錄        "	<< '\n';
	cout << "    #        #     #    #             #        #                        "	<< '\n';
	cout << "    #        #     #    #             #        #        結束遊戲        "	<< '\n';
	cout << "    ######   #     #    ######   ######   ######                        ";

	select(0);

	/* Stage 1 : Menu */
	[&]() -> void {
		while (true)
		{
			keypress = _getch();

			switch (keypress)
			{
				case 72:	//Up
					menuOffset = (menuOffset + 2) % 3;
					functionOffset = (functionOffset + 3) % 3;
					break;

				case 80:	//Down
					menuOffset = (++menuOffset % 3);
					functionOffset = (functionOffset + 1) % 3;
					break;

				case 13:	//Enter
					menuFunction[functionOffset]();
					if (functionOffset == 2)
					{
						return;
					}
					break;

				default:
					break;
			}

			/* Reset other unselected option */
			for (int i = 0; i < 3; ++i)
			{
				Cmder::setColor();
				Cmder::setCursor(menuPosition[i]);
				cout << menu[i];
			}

			select(menuOffset);
		}
	}();
	

	/* Stage 2 : Game processing */
	[&]() -> void {

	}();

	return 0;
}
/*
	vector<string> help;
	19
	strint temp;

	while( !file.eof() )
	{
		for(int i = 0 ; i < 20 && file >> temp; ++i)
		{
			help.push_back( temp+'\n' );
		}
	}

	for(int i = 0 ; i < help.size() ; ++i)
	{
		if( i%20 == 0 )
		{
			system("pause");
			system("cls");
		}
		cout << help[i];

		
	}
*/