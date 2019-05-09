#pragma once
#include <functional>
#include <iostream>
#include "ConsoleInterface.h"
#include "Board.h"
#include "Chess.h"
namespace System 
{
	bool menu();
	bool game();
	bool menuBrand();
	bool gameBrand();
	bool option();
	bool test(Chess x);
	void change(Chess* t1 , Chess* t2);

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
		string menu[] = { "�}�l�C��" , "Ū������" , "�����C��" };
		function<bool()> menuOption[] = {
			[]() -> bool { //�}�l�C��
				Cmder::setCursor(COORD{0,0});
				return game();
			},

			[]() -> bool {       //Ū������
				Cmder::setCursor(COORD{0,0});
				cout << "00002";
				return 1;
			},

			[]() -> bool {       //�����C��
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
		Chess ChessTableMap[10][9];

		/* Initial Virtual ChessTableMap */
		auto makeContainer = [&]() -> void {
			string name[] = { "0" ,"�N","�h","�H","��","��","�]","��","��","�K","��","��","�X","��","�L" };
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
		
		/* Listen Keyboard-event */
		int keypress;
		board.setPointer(0, 9);
		Cmder::setCursor(board.getPointer());
		bool isSelected = false;
		Chess* current = new Chess();
		return [&]() -> bool {
			while (true)
			{
				test(*current);
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
					COORD pos = board.getCursor(); //���п����H
					
					/* ���� (�H��ܡA�B���i���ʦܦP�}�窺�Ѥl�l�W ) */
					if( isSelected && ChessTableMap[pos.Y][pos.X].getCamp() != Chess::Turn )
					{
						/* ���m��ܪ��A */
						isSelected = false;
						current->setCurrent(false);
						
						/* ���ʫ�A�洫�^�X */
						if (current->ChangeChess(pos.X, pos.Y))
						{
							Chess::Turn ^= 1;
							change(current, &ChessTableMap[pos.Y][pos.X]);
						}
						
						/* ���ެO�_���ʡA��s�e�� */
						
						//makeContainer();
						refreshBoard();
						break;
					}

					/*����ܡA�άO��P�}�窺*/
					else if( (!isSelected || ChessTableMap[pos.Y][pos.X].getCamp() == Chess::Turn) )
					{
						/* �藍�P�}�� */
						if (ChessTableMap[pos.Y][pos.X].getCamp() != Chess::Turn)	break;

						/* ��D�Ŧa����m */
						if (ChessTableMap[pos.Y][pos.X].getID() != 0)
						{
							/* ���m�쥻���A */
							current->setCurrent(false);

							/* ����ثe�Ѥl */
							current = &ChessTableMap[pos.Y][pos.X];
							current->setCurrent( true );
							isSelected = true;
							refreshBoard();
						}
					}

					
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
					/*
					Cmder::setCursor(0, 26);
					printf("%100c", ' ');
					Cmder::setCursor(0, 26);
					cout << "Key: " << keypress;
					*/
					break;
				}

				if (Chess::isEnd == true)
				{
					return false;
				}
				/* Reset other unselected option color */
				
				
			}
			
			return true;
		}();
	}

	/* �i�J�e���� */
	inline bool menuBrand()
	{
		system("COLOR 07");
		system("cls");
		cout << "====================================================================================================" << '\n';
		cout << "|  [1;36m    �_         [30m|�@_[37m���j [;33m��[30;43m��                ��[37;40m                [30;43m��            [37;40m                     |" << '\n';
		cout << "|  [1;36m�[  ��        [30m��   [37m  \ [;33m��                 [30;43m��                ��[37;40m                                   |" << '\n';
		cout << "|  [1;36m��  �L      [30m��  �� [37m�� �j               [;30;43m��                ��[37;40m                                     |" << '\n';
		cout << "|  [1;36m��  �^     [30m��     [37m   �x               [;30;43m��                ��[37;40m                [33m��[37m                     |" << '\n';
		cout << "|  [1;36m�y  �j    [30m��  [m�@  ��  /             [30;43m��                ��[37;40m                [30;43m��  [37;40m                     |" << '\n';
		cout << "|  [1;36m�u  �V   [30m��     \ __[;30;43m��            [33;40m��                [30;43m��                ��[37;40m                         |" << '\n';
		cout << "|  [1;36m�g  ��   [30m����   �y[37;43m�j           [;33m��                [30;43m��                ��[37;40m                           |" << '\n';
		cout << "|  [1;36m�l        [30m\\��[m�� [1;30m�y[37;43m�k         [;33m��                [30;43m��                ��[37;40m                             |" << '\n';
		cout << "|           [33m��[30;43m��[1;40m\\[m��[1;47m�h�h[;43m        [33;40m��                [30;43m��                ��[37;40m                               |" << '\n';
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
		cout << "|     #           #     #       #           #            #             �}�l�C��                    |" << '\n';
		cout << "|     #           #     #       #           #            #                                         |" << '\n';
		cout << "|     #           #######       #####       ######       ######        Ū������                    |" << '\n';
		cout << "|     #           #     #       #                #            #                                    |" << '\n';
		cout << "|     #           #     #       #                #            #        �����C��                    |" << '\n';
		cout << "|     ######      #     #       ######      ######       ######                                    |" << '\n';
		cout << "|==================================================================================================|" << endl;
		return true;
	}

	/* �C���e���� */
	inline bool gameBrand()
	{
		system("COLOR 07");
		system("cls");
		cout << "====================================================================================================" << '\n';
		cout << "|                                       |  ��      �p      ��      ��                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  �B      ��  |    " << Cmder::FONT_RED << "��         ��    " << Cmder::FONT_WHITE << "|" << Cmder::FONT_GREEN << "    ��         ��    " << Cmder::FONT_WHITE << "|\n";
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
		cout << "|                                       | " << Cmder::FONT_GREEN << " ESC" << Cmder::FONT_WHITE << " : Menu (�D���)                  Delete : Exit(���})|" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " [  " << Cmder::FONT_WHITE << " : Previous Stepundo (�W�@�B)     S : Save(�O�s)     |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " ]  " << Cmder::FONT_WHITE << " : Undo (�_��)                                       |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " �������� " << Cmder::FONT_WHITE << " : Move Cursor (���ʴ��)                      |" << '\n';
		cout << "|                                       | " << Cmder::FONT_GREEN << " Enter " << Cmder::FONT_WHITE << " : Select (���)                                  |" << '\n';
		cout << "|                                       |                                                          |" << '\n';
		//      cout << "|                                       |                                                          |" << '\n';
		cout << "|==================================================================================================|" << endl;
		return true;
	}

	/* �I�s�D���(�ȩw) */
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

	/* ���աA��X�ثe��m */
	inline bool test(Chess x)
	{
		Cmder::setCursor(0, 26);
		printf("%100c", ' ');
		Cmder::setCursor(0, 26);

		Cmder::setColor(CLI_FONT_PURPLE | CLI_FONT_LIGHT);

		cout << (x.getCamp() == 1 ? "����" : x.getCamp() == 0 ? "�¤�" : "    " ) << "   " << x.getName()
			 << "   Position:{" << x.getPosition().X << "," << x.getPosition().Y << "}   "
			 << (x.getCamp() == 1 ? "����" : x.getCamp() == 0 ? "�¤�" : "��") << "   Turn: "
			 << (Chess::Turn == 1 ? "����" : "�¤�") << "   "
			 << (Chess::isEnd ? "�w����" : "������") << "\n\n";
		
		Cmder::setColor(CLI_FONT_CYAN);
		//Chess::PrintTable();
		return true;
	}

	void change(Chess* t1, Chess* t2)
	{
		Chess t3 = *t1;
		*t1 = *t2;
		*t2 = t3;
	}
}

/*
		cout << "====================================================================================================" << '\n';
		cout << "|      �_         |�@_���j ����               ��                ��                                 |" << '\n';
		cout << "|  �[  ��        ��     \ ��                ��                ��                                   |" << '\n';
		cout << "|  ��  �L      ��        �j               ��                ��                                     |" << '\n';
		cout << "|  ��  �^     ��        �x              ��                ��                ��                     |" << '\n';
		cout << "|  �y  �j    ��  �@     /             ��                ��                ��                       |" << '\n';
		cout << "|  �u  �V   ��     \ __��           ��                ��                ��                         |" << '\n';
		cout << "|  �g  ��   ����   �y�j           ��                ��                ��                           |" << '\n';
		cout << "|  �l        \���� �y�k         ��                ��                ��                             |" << '\n';
		cout << "|           ����\ ���h�h      ��                ��                ��                               |" << '\n';
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
		cout << "|     #           #     #       #           #            #             �}�l�C��                    |" << '\n';
		cout << "|     #           #     #       #           #            #                                         |" << '\n';
		cout << "|     #           #######       #####       ######       ######        Ū������                    |" << '\n';
		cout << "|     #           #     #       #                #            #                                    |" << '\n';
		cout << "|     #           #     #       #                #            #        �����C��                    |" << '\n';
		cout << "|     ######      #     #       ######      ######       ######                                    |" << '\n';
		cout << "|==================================================================================================|" << endl;
���i��
		cout << "====================================================================================================" << '\n';
		cout << "|                                       |  ��      �p      ��      ��                              |" << '\n';
		cout << "|                                       |==========================================================|" << '\n';
		cout << "|                                       |  �B      ��  |    ��         ��    |    ��         ��    |" << '\n';
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
		cout << "|                                       |  ESC : Menu (�D���)                                     |" << '\n';
		cout << "|                                       |  -   : Previous Stepundo (�W�@�B)                        |" << '\n';
		cout << "|                                       |  +   : Undo (�_��)                                       |" << '\n';
		cout << "|                                       |  ��������  : Move Cursor (���ʴ��)                      |" << '\n';
		cout << "|                                       |  Enter  : Select (���)                                  |" << '\n';
		cout << "|                                       |                                                          |" << '\n';
//      cout << "|                                       |                                                          |" << '\n';
		cout << "|==================================================================================================|" << endl;
*/