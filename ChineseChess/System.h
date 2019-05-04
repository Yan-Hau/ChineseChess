#pragma once
#include <functional>
#include <iostream>
#include "ConsoleInterface.h"
#include "Board.h"
namespace System 
{
	bool menu();
	bool game();
	bool option();


	/* Stage 1 : Menu */
	inline bool menu()
	{
		/* Command Box initialize */
		system("COLOR 07");
		system("cls");

		/* Variable initialize */
		COORD menuPosition[] = { 
			{71,19} , 
			{71,21} , 
			{71,23} 
		};
		const int EXIT_GAME = 2;
		int keypress = 0, menuOffset = 0;
		
		
		/* Menu Option */
		string menu[] = { "開始遊戲" , "讀取紀錄" , "結束遊戲" };
		function<void()> menuOption[] = {
			[]() -> void { //開始遊戲
				Cmder::setCursor(COORD{0,0});
				game();
			},

			[]() -> void {       //讀取紀錄
				Cmder::setCursor(COORD{0,0});
				cout << "00002";
			},

			[]() -> void {       //結束遊戲
				Cmder::setCursor(COORD{0,0});
				cout << "00003";
			},
		};

		/* High-light Current selected option */
		auto select = [&menuPosition, &menu](int offset) -> void {
			Cmder::setCursor(menuPosition[offset]);
			Cmder::setColor(CLI_FONT_CYAN);
			cout << menu[offset];
			Cmder::setCursor(menuPosition[offset]);
		};

		/* Entrance Brand  */
		cout << "====================================================================================================" << '\n';
		cout << "|  [1;36m    起         [30m|＼_[37m／▏ [;33m╱[30;43m◤                ◢[37;40m                [30;43m◤            [37;40m                     |" << '\n';
		cout << "|  [1;36m觀  手        [30m／   [37m  \ [;33m／                 [30;43m◤                ◢[37;40m                                   |" << '\n';
		cout << "|  [1;36m棋  無      [30m／     [37m   ▏               [;30;43m◤                ◢[37;40m                                     |" << '\n';
		cout << "|  [1;36m不  回     [30m／     [37m   │               [;30;43m◤                ◢[37;40m                [33m◢[37m                     |" << '\n';
		cout << "|  [1;36m語  大    [30m／  [m＼     /             [30;43m◤                ◢[37;40m                [30;43m◤  [37;40m                     |" << '\n';
		cout << "|  [1;36m真  丈   [30mㄟ     \ __[;30;43m◤            [33;40m◤                [30;43m◤                ◢[37;40m                         |" << '\n';
		cout << "|  [1;36m君  夫   [30m◥◣   ▕[37;43m▏           [;33m◤                [30;43m◤                ◢[37;40m                           |" << '\n';
		cout << "|  [1;36m子        [30m\\◥[m◣ [1;30m▕[37;43m▎         [;33m◤                [30;43m◤                ◢[37;40m                             |" << '\n';
		cout << "|           [33m╱[30;43m◤[1;40m\ [m◥[1;47m▇▇[;43m        [33;40m◤                [30;43m◤                ◢[37;40m                               |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|     ######      #     #       #####      ###     #      ######      ######      ######           |" << '\n';
		cout << "|     #           #     #         #        #  #    #      #           #           #                |" << '\n';
		cout << "|     #           #######         #        #   #   #      ####        ######      ####             |" << '\n';
	//	cout << "|     #           #     #         #        #    #  #      #                #      #                |" << '\n';
		cout << "|     #           #     #         #        #     # #      #                #      #                |" << '\n';
		cout << "|     ######      #     #       #####      #     ###      ######      ######      ######           |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|     ######      #     #       ######      ######       ######                                    |" << '\n';
		cout << "|     #           #     #       #           #            #             開始遊戲                    |" << '\n';
		cout << "|     #           #     #       #           #            #                                         |" << '\n';
		cout << "|     #           #######       #####       ######       ######        讀取紀錄                    |" << '\n';
		cout << "|     #           #     #       #                #            #                                    |" << '\n';
		cout << "|     #           #     #       #                #            #        結束遊戲                    |" << '\n';
		cout << "|     ######      #     #       ######      ######       ######                                    |" << '\n';
		cout << "|==================================================================================================|" << endl;
		
		/* Listen Keyboard-event */
		select(0);
		return [&]() -> bool {
			while (true)
			{
				keypress = _getch();

				switch (keypress)
				{
					case 72:	//Key press Up
						menuOffset = (menuOffset + 2) % 3;
						break;

					case 80:	//Key press Down
						menuOffset = (++menuOffset % 3);
						break;

					case 13:	//Key press Enter
						if (menuOffset == EXIT_GAME)
							return false;
						menuOption[menuOffset]();
						break;
						

					default:
						break;
				}

				/* Reset other unselected option color */
				for (int i = 0; i < 3; ++i)
				{
					Cmder::setColor();
					Cmder::setCursor(menuPosition[i]);
					cout << menu[i];
				}
				select(menuOffset);
			}
			return true;
		}();
	}

	/* Stage 2 : Board */
	inline bool game()
	{
		/* Command Box initialize */
		system("COLOR 07");
		system("cls");
		
		Board board;
		
		cout << "====================================================================================================" << '\n';
		cout << "|                                       |  戰      況      顯      示                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  步      數  |    紅         方    |    黑         方    |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
		cout << "|                                       |       1      |       炮二平五      |      馬８進７       |" << '\n';
		cout << "|                                       |       2      |       傌二進三      |      砲８平９       |" << '\n';
		cout << "|                                       |       3      |       傌八進七      |      車９平８       |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
		cout << "|                                       | "<< Cmder::FONT_GREEN <<" ESC" << Cmder::FONT_WHITE <<      " : Menu (主選單)                                     |" << '\n';
		cout << "|                                       | "<< Cmder::FONT_GREEN <<" -  " << Cmder::FONT_WHITE <<      " : Previous Stepundo (上一步)                        |" << '\n';
		cout << "|                                       | "<< Cmder::FONT_GREEN <<" +  " << Cmder::FONT_WHITE <<      " : Undo (復原)                                       |" << '\n';
		cout << "|                                       | "<< Cmder::FONT_GREEN <<" ←↑↓→ " << Cmder::FONT_WHITE <<" : Move Cursor (移動游標)                      |" << '\n';
		cout << "|                                       | "<< Cmder::FONT_GREEN <<" Enter " << Cmder::FONT_WHITE <<   " : Select (選擇)                                  |" << '\n';
		cout << "|                                       |                                                          |" << '\n';
//      cout << "|                                       |                                                          |" << '\n';
		cout << "|==================================================================================================|" << endl;
		board.print();

		/* Listen Keyboard-event */
		int keypress;
		COORD currentPosition = Cmder::getCursor();
		board.setPointer(0, 9);
		return [&]() -> bool {
			while (true)
			{
				keypress = _getch();

				switch (keypress)
				{
				case 72:	//Key press Up
					board.setPointer(0, 9);
					break;

				case 75:	//Key press Left
					board.setPointer(8, 0);
					break;

				case 77:	//Key press Right
					board.setPointer(1, 0);
					break;

				case 80:	//Key press Down
					board.setPointer(0, 1);
					break;

				case 13:	//Key press Enter
					break;

				default:
					break;
				}

				/* Reset other unselected option color */
				Cmder::setCursor( board.getPointer() );
				
			}
			return true;
		}();
	}

	inline bool option()
	{

	}
}