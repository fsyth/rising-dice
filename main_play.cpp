#include "play.hpp"
#include "playerStrategy.hpp"
#include "displayGameState.hpp"

#include <iostream>

void playAsHuman()
{
	std::cout << "Game Start!\n";

	char playAgain;
	do
	{
		play(playerStrategy, displayGameState);

		std::cout
			<< "\nWinning score reached!\n"
			<< "Play Again?    (y) Yes   (n) No\n"
			<< "Choice > ";

		std::cin >> playAgain;
	} while (playAgain == 'y');
}

int main()
{
	playAsHuman();

	return 0;
}
