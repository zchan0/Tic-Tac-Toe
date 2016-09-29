#include <cstdlib>
#include <limits>
#include "controller/TTTController.cpp"

// Credits to http://stackoverflow.com/a/10349885
void handleWrongInputType() 
{
	std::cin.clear();	// clear bad input flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// discard input
    std::cout << "Invalid input; please re-enter. " << std::endl;
}

bool promptInstruction()
{
	std::cout << "Enter number: " << std::endl;
	std::cout << "1. Start a new game." << std::endl;
	std::cout << "2. Exit." << std::endl;	
	return true;
}

int main()
{
	TTTController controller;

	int choice = 0;
	while (choice == 0) {
		while (promptInstruction() && !(std::cin >> choice)) handleWrongInputType();
		if (choice == 2) exit(1);
		if (choice == 1) {	
			controller.startNewGame();
			controller.createPlayer("A", "O");
			controller.createPlayer("B", "X", 2);

			int currentPlayerNum, row, col;
			while(controller.determinWinner() == 0) {
				// check input type, if it isn't int, should re-input
				while(std::cout << "Input player num: " && !(std::cin >> currentPlayerNum)) handleWrongInputType();
				while(std::cout << "Input row: " && !(std::cin >> row)) handleWrongInputType();
				while(std::cout << "Input col: " && !(std::cin >> col)) handleWrongInputType();
				
				if (controller.setSelection(--row, --col, currentPlayerNum)) {
					std::cout << controller.getGameDisplay() << std::endl;
					continue;
				}
			}

			// reset to restart game
			choice = 0;		
		}
	}

	return 0;
}
