#include "playerStrategy.hpp"

#include "Color.hpp"

#include <iostream>

Choice playerStrategy(const GameState& state)
{
	while (true)
	{
		std::cout << Color::Cyan << "Choice > ";
		int c;
		std::cin >> c;
		std::cout << Color::Reset;

		if ((c == Bank || c == D4 || c == D6 || c == D8 || c == D10 || c == D12) &&
			state.choices.test(c))
		{
			return static_cast<Choice>(c);
		}

		std::cout << Color::Yellow << "Unknown choice.\n" << Color::Yellow;
	}
}
