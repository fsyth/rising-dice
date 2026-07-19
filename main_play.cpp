#include "Color.hpp"
#include "displayGameState.hpp"
#include "play.hpp"
#include "playerStrategy.hpp"

#include <iostream>

void playAsHuman()
{
	std::cout << "Game Start!\n";

	char playAgain;
	do
	{
		play(playerStrategy, displayGameState);

		std::cout
			<< Color::Green << "\nWinning score reached!\n" << Color::Reset
			<< "Play Again?    "
			<< Color::Cyan << "(y)" << Color::Reset << " Yes   "
			<< Color::Cyan << "(n)" << Color::Reset << " No\n"
			<< Color::Cyan << "Choice > ";

		std::cin >> playAgain;
		std::cout << Color::Reset;
	} while (playAgain == 'y');
}

int main()
{
	playAsHuman();

	return 0;
}
