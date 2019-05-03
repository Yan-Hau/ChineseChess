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
		string menu[] = { "¶}©l¹CÀ¸" , "Åª¨ú¬ö¿ý" , "µ²§ô¹CÀ¸" };
		function<void()> menuOption[] = {
			[]() -> void { //¶}©l¹CÀ¸
				Cmder::setCursor(COORD{0,0});
				game();
			},

			[]() -> void {       //Åª¨ú¬ö¿ý
				Cmder::setCursor(COORD{0,0});
				cout << "00002";
			},

			[]() -> void {       //µ²§ô¹CÀ¸
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
		cout << "|  [1;36m    °_         [30m|¢@_[37m¡þ¢j [;33m¢¬[30;43m¢«                ¢¨[37;40m                [30;43m¢«            [37;40m                     |" << '\n';
		cout << "|  [1;36mÆ[  ¤â        [30m¡þ   [37m  \ [;33m¡þ                 [30;43m¢«                ¢¨[37;40m                                   |" << '\n';
		cout << "|  [1;36m´Ñ  µL      [30m¡þ     [37m   ¢j               [;30;43m¢«                ¢¨[37;40m                                     |" << '\n';
		cout << "|  [1;36m¤£  ¦^     [30m¡þ     [37m   ¢x               [;30;43m¢«                ¢¨[37;40m                [33m¢¨[37m                     |" << '\n';
		cout << "|  [1;36m»y  ¤j    [30m¡þ  [m¢@     /             [30;43m¢«                ¢¨[37;40m                [30;43m¢«  [37;40m                     |" << '\n';
		cout << "|  [1;36m¯u  ¤V   [30m£°     \ __[;30;43m¢«            [33;40m¢«                [30;43m¢«                ¢¨[37;40m                         |" << '\n';
		cout << "|  [1;36m§g  ¤Ò   [30m¢ª¢©   ¢y[37;43m¢j           [;33m¢«                [30;43m¢«                ¢¨[37;40m                           |" << '\n';
		cout << "|  [1;36m¤l        [30m\\¢ª[m¢© [1;30m¢y[37;43m¢k         [;33m¢«                [30;43m¢«                ¢¨[37;40m                             |" << '\n';
		cout << "|           [33m¢¬[30;43m¢«[1;40m\ [m¢ª[1;47m¢h¢h[;43m        [33;40m¢«                [30;43m¢«                ¢¨[37;40m                               |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|     ######      #     #       #####      ###     #      ######      ######      ######           |" << '\n';
		cout << "|     #           #     #         #        #  #    #      #           #           #                |" << '\n';
		cout << "|     #           #######         #        #   #   #      #####       ######      #####            |" << '\n';
		cout << "|     #           #     #         #        #    #  #      #                #      #                |" << '\n';
		cout << "|     #           #     #         #        #     # #      #                #      #                |" << '\n';
		cout << "|     ######      #     #       #####      #     ###      ######      ######      ######           |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|     ######      #     #       ######      ######       ######                                    |" << '\n';
		cout << "|     #           #     #       #           #            #             ¶}©l¹CÀ¸                    |" << '\n';
		cout << "|     #           #     #       #           #            #                                         |" << '\n';
		cout << "|     #           #######       #####       ######       ######        Åª¨ú¬ö¿ý                    |" << '\n';
		cout << "|     #           #     #       #                #            #                                    |" << '\n';
		cout << "|     #           #     #       #                #            #        µ²§ô¹CÀ¸                    |" << '\n';
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
		cout << "|                                       |  ¾Ô      ªp      Åã      ¥Ü                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  ¨B      ¼Æ  |    ¬õ         ¤è    |    ¶Â         ¤è    |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
		cout << "|                                       |       1      |       ¬¶¤G¥­¤­      |      °¨¢·¶i¢¶       |" << '\n';
		cout << "|                                       |       2      |       ØX¤G¶i¤T      |      ¯¥¢·¥­¢¸       |" << '\n';
		cout << "|                                       |       3      |       ØX¤K¶i¤C      |      ¨®¢¸¥­¢·       |" << '\n';
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
		cout << "|                                       | ESC: Menu (¥D¿ï³æ)                                       |" << '\n';
		cout << "|                                       | -  : Previous Stepundo (¤W¤@¨B)                          |" << '\n';
		cout << "|                                       | +  : Undo (´_­ì)                                         |" << '\n';
		cout << "|                                       | ¡ö¡ô¡õ¡÷ : Move Cursor (²¾°Ê´å¼Ð)                        |" << '\n';
		cout << "|                                       | Enter : Select (¿ï¾Ü)                                    |" << '\n';
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