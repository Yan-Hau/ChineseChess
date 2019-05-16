#pragma once
#include <functional>
#include <iostream>
#include "ConsoleInterface.h"
#include "Board.h"
#include "Chess.h"
#include "ChessLog.h"
namespace System 
{
	bool menu();
	bool game();
	bool menuBrand();
	bool gameBrand();
	bool optionBrand();
	bool option();
	bool info(Chess x);
	void swap(Chess* t1 , Chess* t2);
	bool stepBrand();
	ChessLog boardRecoed;

	/* Stage 1 : Menu */
	inline bool menu()
	{
		system("cls");
		/* Variable initialize */
		COORD menuPosition[] = { 
			{71,19} , 
			{71,21} , 
			{71,23} 
		};
		const int EXIT_GAME = 2;
		int keypress = 0, menuOffset = 0;
		boardRecoed.create();
		
		/* Menu Option */
		string menu[] = { "開始遊戲" , "讀取紀錄" , "結束遊戲" };
		function<bool()> menuOption[] = {
			[&]() -> bool {		//開始遊戲
				Cmder::setCursor(COORD{0,0});
				int initialChessTable[90] =
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
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < 9; ++j)
					{
						Chess::ChessTable[i][j] = initialChessTable[9 * i + j];
					}
				}
				return game();
			},

			[&]() -> bool {       //讀取紀錄
				Cmder::setCursor(COORD{0,0});
				boardRecoed.downloadLog();
				int *temp = boardRecoed.getCurrentChessTable();
				for (int i = 0; i < 10; ++i)
				{
					for (int j = 0; j < 9; ++j)
					{
						Chess::ChessTable[i][j] = temp[9 * i + j];
					}
				}
				return game();
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

						else
						{ 
							menuBrand();
							Chess::Turn = 1;
							Chess::isEnd = false;
						}

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
		Chess ChessTableMap[10][9];

		/* Initial Virtual ChessTableMap */
		auto makeContainer = [&]() -> void {
			string name[] = { "0" ,"將","士","象","車","馬","包","卒","帥","仕","相","車","傌","炮","兵" };
			for (int i = 0; i < 10; ++i)
			{
				for (int j = 0; j < 9; ++j)
				{
					int ID = Chess::ChessTable[i][j];
					short camp = (ID == 0) ? 2 : (ID / 8);
					Chess temp(j , i , ID , name[ID] , ID!=0 , camp);
					ChessTableMap[i][j] = temp;
				}
			}
		};

		auto refreshBoard = [&]() -> void {
			board.print();
			for (int i = 0; i < 10; ++i)
			{
				for (int j = 0; j < 9; ++j)
				{
					board.put( &ChessTableMap[i][j] );
				}
			}
		};
		/* Re-print board */
		board.print();
		makeContainer();
		refreshBoard();
		stepBrand();
		/* Listen Keyboard-event */
		int keypress;
		board.setPointer(0, 9);
		Cmder::setCursor(board.getPointer());
		bool isSelected = false;
		Chess* current = new Chess();
		int *tempboard;
		return [&]() -> bool {
			while (true)
			{
				info(*current);
				Cmder::setCursor(board.getPointer());
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
					if (!option())
					{
						return false;
					}
					break;

				case 91:    //Key press [
					Cmder::setCursor(0, 26);
					if (boardRecoed.counter > 1)
					{
						if (boardRecoed.repent())
							Chess::Turn ^= 1;
						tempboard = boardRecoed.getCurrentChessTable();
						for (int i = 0; i < 10; ++i)
						{
							for (int j = 0; j < 9; ++j)
							{
								Chess::ChessTable[i][j] = tempboard[9 * i + j];
							}
						}
					}
					else if (boardRecoed.counter == 1)
					{
						if (boardRecoed.repent())
							Chess::Turn ^= 1;
						int initialChessTable[90] =
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
						for (int i = 0; i < 10; ++i)
						{
							for (int j = 0; j < 9; ++j)
							{
								Chess::ChessTable[i][j] = initialChessTable[9 * i + j];
							}
						}
					}
					makeContainer();
					refreshBoard();
					stepBrand();
					break;

				case 93:    //Key press ]
					Cmder::setCursor(0, 26);
					if (boardRecoed.recover())
						Chess::Turn ^= 1;
					tempboard = boardRecoed.getCurrentChessTable();
					for (int i = 0; i < 10; ++i)
					{
						for (int j = 0; j < 9; ++j)
						{
							Chess::ChessTable[i][j] = tempboard[9 * i + j];
						}
					}
					makeContainer();
					refreshBoard();
					stepBrand();
					break;

				case 13:	//Key press Enter
					COORD pos = board.getCursor(); //光標選取對象
					COORD _current = Cmder::getCursor();
					Cmder::setCursor(0, 27);
					printf("%50c", ' ');
					Cmder::setCursor(_current);
					/* 移動 (以選擇，且不可移動至同陣營的棋子子上 ) */
					if (isSelected && ChessTableMap[pos.Y][pos.X].getCamp() != Chess::Turn)
					{
						/* 重置選擇狀態 */
						isSelected = false;
						current->setCurrent(false);

						/* 移動後，交換回合 */
						COORD notation = current->ChangeChess(pos.X, pos.Y);
						if (notation.X != 0 || notation.Y != 0)
						{
							boardRecoed.record(*current->ChessTable, current->Turn, notation, pos);
							Chess::Turn ^= 1;
							//swap(current, &ChessTableMap[pos.Y][pos.X]);
						}

						/* 不管是否移動，刷新畫面 */

						makeContainer();
						refreshBoard();
						stepBrand();
						break;
					}

					/*未選擇，或是選同陣營的*/
					else if ((!isSelected || ChessTableMap[pos.Y][pos.X].getCamp() == Chess::Turn))
					{
						/* 選不同陣營 */
						if (ChessTableMap[pos.Y][pos.X].getCamp() != Chess::Turn)	break;

						/* 選非空地的位置 */
						if (ChessTableMap[pos.Y][pos.X].getID() != 0)
						{
							/* 重置原本狀態 */
							current->setCurrent(false);

							/* 選取目前棋子 */
							current = &ChessTableMap[pos.Y][pos.X];
							current->setCurrent(true);
							isSelected = true;
							refreshBoard();
						}
					}
					break;

				default:
					break;
				}

				if (Chess::isEnd == true)
				{
					Cmder::setCursor(0, 27);
					cout << (Cmder::FONT_BLACK | Cmder::FONT_LIGHT) << "試用版本已經結束，若想進行接關功能請下載DLC (Please Any Key to Exit)";
					cin.get();
					return false;
				}
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
		cout << "|     #           #     #         #        #    #  #      #                #      #                |" << '\n';
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
		cout << "|                                       |  步      數  |    " << Cmder::FONT_RED << "紅         方    " << Cmder::FONT_WHITE << "|" << (Cmder::FONT_BLACK | Cmder::FONT_LIGHT) << "    黑         方    " << Cmder::FONT_WHITE << "|\n";
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
		cout << "|                                       | " << Cmder::FONT_GREEN << " ESC" << Cmder::FONT_WHITE << " : Menu (主選單)                  " << Cmder::FONT_GREEN << "       " << Cmder::FONT_WHITE << "            |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " [  " << Cmder::FONT_WHITE << " : Previous Stepundo (上一步)     "<< Cmder::FONT_GREEN << "  " << Cmder::FONT_WHITE <<"                 |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " ]  " << Cmder::FONT_WHITE << " : Undo (復原)                                       |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " ←↑↓→ " << Cmder::FONT_WHITE << " : Move Cursor (移動游標)                      |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " Enter " << Cmder::FONT_WHITE << " : Select (選擇)                                  |" << '\n';
		cout << "|                                       |                                                          |" << '\n';
		//      cout << "|                                       |                                                          |" << '\n';
		cout << "|==================================================================================================|" << endl;
		return true;
	}
	
	/* 中式記譜法 */
	bool stepBrand()
	{
		COORD _current = Cmder::getCursor();
		for (int i = 5; i < 18; i++)
		{
			Cmder::setCursor(40, i);
			cout << "|              |                     |                     |";
		}

		/* counter = 14 */
		for (int n = (boardRecoed.counter > 26) ? ((boardRecoed.counter+1) / 2 - 12) : 1 , i = 1 ; n <= (boardRecoed.counter + 1) / 2; n++ , i++)
		{
			Cmder::setCursor(47, 4 + i);
			Cmder::setColor(CLI_FONT_WHITE);
			cout << n;
			Cmder::setCursor(63, 4 + i);

			Cmder::setColor(CLI_FONT_RED | CLI_FONT_LIGHT);
			cout << boardRecoed.redNotation[n - 1];
			if (n * 2 <= boardRecoed.counter)
			{
				Cmder::setCursor(86, 4 + i);
				Cmder::setColor(CLI_FONT_BLACK | CLI_FONT_LIGHT);
				cout << boardRecoed.blackNotation[n - 1];
			}
		}
		Cmder::setCursor(_current);
		Cmder::setColor();
		return true;
	}

	/* ESC主選單基底 */
	inline bool optionBrand()
	{
		Cmder::setColor(CLI_FONT_LIGHT | CLI_FONT_WHITE);
		Cmder::setCursor(29, 8);
		cout << "================================================ "; Cmder::setCursor(29, 9);
		cout << "|                                              | "; Cmder::setCursor(29, 10);
		cout << "|            Exit Menu(離開主選單)             | "; Cmder::setCursor(29, 11);
		cout << "|                                              | "; Cmder::setCursor(29, 12);
		cout << "|            Save(保存)                        | "; Cmder::setCursor(29, 13);
		cout << "|                                              | "; Cmder::setCursor(29, 14);
		cout << "|            Exit GAME(離開遊戲)               | "; Cmder::setCursor(29, 15);
		cout << "|                                              | "; Cmder::setCursor(29, 16);
		cout << "================================================ ";
		Cmder::setCursor(39, 14);
		return true;
	}

	/* 呼叫主選單(暫定) */
	inline bool option()
	{
		Board b;
		COORD _current = Cmder::getCursor();

		/* Variable initialize */
		COORD menuPosition[] = {
			{42,10} ,
			{42,12} ,
			{42,14}
		};
		const int EXIT_GAME = 2;
		int keypress = 0, menuOffset = 0;


		/* Menu Option */
		string menu[] = { "Exit Menu(離開主選單)" , "Save(保存)" , "Exit GAME(離開遊戲)"};
		function<bool()> menuOption[] = {
			[&]() -> bool {		//離開主選單
				Cmder::setCursor(COORD{0,0});
				gameBrand();
				b.print();
				Cmder::setCursor(_current);
				return game();
			},
			[&]() -> bool {       //保存
				Cmder::setCursor(COORD{0,0});
				boardRecoed.saveLog();
				gameBrand();
				b.print();
				Cmder::setCursor(_current);
				return game();
			},
			[]() -> bool {       //離開遊戲
				Cmder::setCursor(COORD{0,0});
				return false;
			}
		};

		/* High-light Current selected option */
		auto select = [&menuPosition, &menu](int offset) -> void {
			Cmder::setCursor(menuPosition[offset]);
			Cmder::setColor(CLI_FONT_LIGHT | CLI_FONT_BLUE);
			cout << menu[offset];
			Cmder::setCursor(menuPosition[offset]);
		};

		/* Entrance Brand  */
		optionBrand();

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

	/* 輸出目前位置 */
	inline bool info(Chess x)
	{
		Cmder::setCursor(0, 26);
		printf("%60c", ' ');
		Cmder::setCursor(0, 26);

		//Cmder::setColor(CLI_FONT_PURPLE | CLI_FONT_LIGHT);
		
		if (Chess::Turn == 1)
		{
			Cmder::setColor(CLI_FONT_RED);
			cout << Cmder::FONT_RED << "紅方回合 ";
		}
		else
		{
			Cmder::setColor(CLI_FONT_BLACK | CLI_FONT_LIGHT);
			cout << Cmder::FONT_RED << "黑方回合 ";
		}
			
		Cmder::setColor(CLI_FONT_PURPLE | CLI_FONT_LIGHT);
		cout << (Chess::isEnd ? "已結束" : "未結束") << "   ";

		if (x.getCamp() != 1 && x.getCamp() != 0)
			return true;

		if (x.getCamp() == 1)
		{
			Cmder::setColor(CLI_FONT_RED);
			cout << "紅" << x.getName();
		}

		else
		{
			Cmder::setColor(CLI_FONT_BLACK | CLI_FONT_LIGHT);
			cout << "黑" << x.getName();
		}

		Cmder::setColor(CLI_FONT_WHITE | CLI_FONT_LIGHT);
		cout << " :Position:{" << x.getPosition().X + 1 << "," << x.getPosition().Y + 1 << "}   ";
			 
		return true;
	}

	void swap(Chess* t1, Chess* t2)
	{
		Chess t3 = *t1;
		*t1 = *t2;
		*t2 = t3;
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
		cout << "|     #           #     #         #        #    #  #      #                #      #                |" << '\n';
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
