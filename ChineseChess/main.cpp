#include "pch.h"
#include "ConsoleInterface.h"
#include "Board.h"
#include "System.h"
#include <functional>
using namespace std;

int main()
{
	/* Game System Object */
	bool state = true;
	Cmder box;
	Board board;
	box.initialize(30, 100);
	
	do
	{
		state = System::menu();
	} while (state);

	return 0;
}