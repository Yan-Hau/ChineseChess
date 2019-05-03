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
		string menu[] = { "�}�l�C��" , "Ū������" , "�����C��" };
		function<void()> menuOption[] = {
			[]() -> void { //�}�l�C��
				Cmder::setCursor(COORD{0,0});
				game();
			},

			[]() -> void {       //Ū������
				Cmder::setCursor(COORD{0,0});
				cout << "00002";
			},

			[]() -> void {       //�����C��
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
		cout << "|  [1;36m    �_         [30m|�@_[37m���j [;33m��[30;43m��                ��[37;40m                [30;43m��            [37;40m                     |" << '\n';
		cout << "|  [1;36m�[  ��        [30m��   [37m  \ [;33m��                 [30;43m��                ��[37;40m                                   |" << '\n';
		cout << "|  [1;36m��  �L      [30m��     [37m   �j               [;30;43m��                ��[37;40m                                     |" << '\n';
		cout << "|  [1;36m��  �^     [30m��     [37m   �x               [;30;43m��                ��[37;40m                [33m��[37m                     |" << '\n';
		cout << "|  [1;36m�y  �j    [30m��  [m�@     /             [30;43m��                ��[37;40m                [30;43m��  [37;40m                     |" << '\n';
		cout << "|  [1;36m�u  �V   [30m��     \ __[;30;43m��            [33;40m��                [30;43m��                ��[37;40m                         |" << '\n';
		cout << "|  [1;36m�g  ��   [30m����   �y[37;43m�j           [;33m��                [30;43m��                ��[37;40m                           |" << '\n';
		cout << "|  [1;36m�l        [30m\\��[m�� [1;30m�y[37;43m�k         [;33m��                [30;43m��                ��[37;40m                             |" << '\n';
		cout << "|           [33m��[30;43m��[1;40m\ [m��[1;47m�h�h[;43m        [33;40m��                [30;43m��                ��[37;40m                               |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|     ######      #     #       #####      ###     #      ######      ######      ######           |" << '\n';
		cout << "|     #           #     #         #        #  #    #      #           #           #                |" << '\n';
		cout << "|     #           #######         #        #   #   #      #####       ######      #####            |" << '\n';
		cout << "|     #           #     #         #        #    #  #      #                #      #                |" << '\n';
		cout << "|     #           #     #         #        #     # #      #                #      #                |" << '\n';
		cout << "|     ######      #     #       #####      #     ###      ######      ######      ######           |" << '\n';
		cout << "|                                                                                                  |" << '\n';
		cout << "|     ######      #     #       ######      ######       ######                                    |" << '\n';
		cout << "|     #           #     #       #           #            #             �}�l�C��                    |" << '\n';
		cout << "|     #           #     #       #           #            #                                         |" << '\n';
		cout << "|     #           #######       #####       ######       ######        Ū������                    |" << '\n';
		cout << "|     #           #     #       #                #            #                                    |" << '\n';
		cout << "|     #           #     #       #                #            #        �����C��                    |" << '\n';
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
		cout << "|                                       |  ��      �p      ��      ��                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  �B      ��  |    ��         ��    |    ��         ��    |" << '\n';
		cout << "|                                       |==============|=====================|=====================|" << '\n';
		cout << "|                                       |       1      |       ���G����      |      �����i��       |" << '\n';
		cout << "|                                       |       2      |       �X�G�i�T      |      ��������       |" << '\n';
		cout << "|                                       |       3      |       �X�K�i�C      |      ��������       |" << '\n';
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
		cout << "|                                       | ESC: Menu (�D���)                                       |" << '\n';
		cout << "|                                       | -  : Previous Stepundo (�W�@�B)                          |" << '\n';
		cout << "|                                       | +  : Undo (�_��)                                         |" << '\n';
		cout << "|                                       | �������� : Move Cursor (���ʴ��)                        |" << '\n';
		cout << "|                                       | Enter : Select (���)                                    |" << '\n';
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