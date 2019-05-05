#pragma once
#include <functional>
#include <iostream>
#include "ConsoleInterface.h"
#include "Board.h"
namespace System 
{
	bool menu();
	bool game();
	bool menuBrand();
	bool gameBrand();
	bool option();
	string nextOne(int v);

	/* Stage 1 : Menu */
	inline bool menu()
	{
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
		function<bool()> menuOption[] = {
			[]() -> bool { //開始遊戲
				Cmder::setCursor(COORD{0,0});
				return game();
			},

			[]() -> bool {       //讀取紀錄
				Cmder::setCursor(COORD{0,0});
				cout << "00002";
				return 1;
			},

			[]() -> bool {       //結束遊戲
				Cmder::setCursor(COORD{0,0});
				cout << "00003";
				return 1;
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
		menuBrand();
		
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
						if (!menuOption[menuOffset]())
							return false;
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
		Board board;
		
		gameBrand();

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

				case 27:    //Key press ESC
					Cmder::setCursor(0, 26);
					cout << "E";
					break;

				case 91:    //Key press -
					Cmder::setCursor(0, 26);
					cout << "[";
					break;

				case 93:    //Key press +
					Cmder::setCursor(0, 26);
					cout << "]";
					break;

				case 13:	//Key press Enter
					break;
				
				case 83:    //Key press Delete
					return false;
					break;

				case 33: //Shift + 1
				case 64: //Shift + 2
				case 35: //Shift + 3
				case 36: //Shift + 4
				case 37: //Shift + 5
				case 94: //Shift + 6
				case 38: //Shift + 7
				case 42: //Shift + 8
				case 40: //Shift + 9
					Cmder::setCursor(0, 26);
					cout << (char)keypress;
					break;

				case 49:  //Number 1
				case 50:  //Number 2
				case 51:  //Number 3
				case 52:  //Number 4
				case 53:  //Number 5
				case 54:  //Number 6
				case 55:  //Number 7
				case 56:  //Number 8
				case 57:  //Number 9
					Cmder::setCursor(0, 26);
					cout << (char)keypress;
					break;

				default:
					if (keypress != 224)
					{
						Cmder::setCursor(0, 26);
						cout << "                           ";
						Cmder::setCursor(0, 26);
						cout << keypress;
						option();
					}
					break;
				}

				/* Reset other unselected option color */
				Cmder::setCursor( board.getPointer() );


			}
			
			return true;
		}();
	}

	/* 進入畫面基底 */
	inline bool menuBrand()
	{
		system("COLOR 07");
		system("cls");
		cout << "====================================================================================================" << '\n';
		cout << "|  [1;36m    起         [30m|＼_[37m／▏ [;33m╱[30;43m◤                ◢[37;40m                [30;43m◤            [37;40m                     |" << '\n';
		cout << "|  [1;36m觀  手        [30m／   [37m  \ [;33m／                 [30;43m◤                ◢[37;40m                                   |" << '\n';
		cout << "|  [1;36m棋  無      [30m／  ■ [37m■ ▏               [;30;43m◤                ◢[37;40m                                     |" << '\n';
		cout << "|  [1;36m不  回     [30m／     [37m   │               [;30;43m◤                ◢[37;40m                [33m◢[37m                     |" << '\n';
		cout << "|  [1;36m語  大    [30m／  [m＼  ×  /             [30;43m◤                ◢[37;40m                [30;43m◤  [37;40m                     |" << '\n';
		cout << "|  [1;36m真  丈   [30mㄟ     \ __[;30;43m◤            [33;40m◤                [30;43m◤                ◢[37;40m                         |" << '\n';
		cout << "|  [1;36m君  夫   [30m◥◣   ▕[37;43m▏           [;33m◤                [30;43m◤                ◢[37;40m                           |" << '\n';
		cout << "|  [1;36m子        [30m\\◥[m◣ [1;30m▕[37;43m▎         [;33m◤                [30;43m◤                ◢[37;40m                             |" << '\n';
		cout << "|           [33m╱[30;43m◤[1;40m\\[m◥[1;47m▇▇[;43m        [33;40m◤                [30;43m◤                ◢[37;40m                               |" << '\n';
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
		return true;
	}

	/* 遊戲畫面基底 */
	inline bool gameBrand()
	{
		system("COLOR 07");
		system("cls");
		cout << "====================================================================================================" << '\n';
		cout << "|                                       |  戰      況      顯      示                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  步      數  |    " << Cmder::FONT_RED << "紅         方    " << Cmder::FONT_WHITE << "|" << Cmder::FONT_GREEN << "    黑         方    " << Cmder::FONT_WHITE << "|\n";
		cout << "|                                       |==============|=====================|=====================|" << '\n';
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
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " ESC" << Cmder::FONT_WHITE << " : Menu (主選單)                  Delete : Exit(離開)|" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " [  " << Cmder::FONT_WHITE << " : Previous Stepundo (上一步)     S : Save(保存)     |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " ]  " << Cmder::FONT_WHITE << " : Undo (復原)                                       |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " ←↑↓→ " << Cmder::FONT_WHITE << " : Move Cursor (移動游標)                      |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " Enter " << Cmder::FONT_WHITE << " : Select (選擇)                                  |" << '\n';
		cout << "|                                       |                                                          |" << '\n';
		//      cout << "|                                       |                                                          |" << '\n';
		cout << "|==================================================================================================|" << endl;
		return true;
	}

	inline bool option()
	{
		Board b;
		COORD _current = Cmder::getCursor();

		Cmder::setColor( CLI_FONT_LIGHT | CLI_FONT_WHITE );
		Cmder::setCursor(29, 8);
		cout << "================================================ "; Cmder::setCursor(29, 9);
		cout << "|                                              | "; Cmder::setCursor(29, 10);
		cout << "|                                              | "; Cmder::setCursor(29, 11);
		cout << "|                                              | "; Cmder::setCursor(29, 12);
		cout << "|                                              | "; Cmder::setCursor(29, 13);
		cout << "|                                              | "; Cmder::setCursor(29, 14);
		cout << "|         YES                     NO           | "; Cmder::setCursor(29, 15);
		cout << "|                                              | "; Cmder::setCursor(29, 16);
		cout << "================================================ ";
		Cmder::setCursor(39, 14);

		char ch = _getch();

		gameBrand();
		b.print();
		Cmder::setCursor(_current);
		return ch == 'a' ? true : false;
	}

	inline string nextOne(int v)
	{
		string str = "\v";
		for (int i = 0; i < v; ++i)
			str.push_back('\b');
		return str;
	}
}

/*
		cout << "====================================================================================================" << '\n';
		cout << "|      起         |＼_／▏ ╱◤               ◢                ◤                                 |" << '\n';
		cout << "|  觀  手        ／     \ ／                ◤                ◢                                   |" << '\n';
		cout << "|  棋  無      ／        ▏               ◤                ◢                                     |" << '\n';
		cout << "|  不  回     ／        │              ◤                ◢                ◢                     |" << '\n';
		cout << "|  語  大    ／  ＼     /             ◤                ◢                ◤                       |" << '\n';
		cout << "|  真  丈   ㄟ     \ __◤           ◤                ◤                ◢                         |" << '\n';
		cout << "|  君  夫   ◥◣   ▕▏           ◤                ◤                ◢                           |" << '\n';
		cout << "|  子        \◥◣ ▕▎         ◤                ◤                ◢                             |" << '\n';
		cout << "|           ╱◤\ ◥▇▇      ◤                ◤                ◢                               |" << '\n';
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
基本檯面
		cout << "====================================================================================================" << '\n';
		cout << "|                                       |  戰      況      顯      示                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  步      數  |    紅         方    |    黑         方    |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
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
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |              |                     |                     |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
		cout << "|                                       |  ESC : Menu (主選單)                                     |" << '\n';
		cout << "|                                       |  -   : Previous Stepundo (上一步)                        |" << '\n';
		cout << "|                                       |  +   : Undo (復原)                                       |" << '\n';
		cout << "|                                       |  ←↑↓→  : Move Cursor (移動游標)                      |" << '\n';
		cout << "|                                       |  Enter  : Select (選擇)                                  |" << '\n';
		cout << "|                                       |                                                          |" << '\n';
//      cout << "|                                       |                                                          |" << '\n';
		cout << "|==================================================================================================|" << endl;
*/