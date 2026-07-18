#include "playerStrategy.hpp"

#include "Color.hpp"

#include <iostream>

Choice playerStrategy(const GameState& state)
{
	while (true)
	{
		std::cout << Color::Cyan << "Choice > ";
		unsigned int c;
		std::cin >> c;
		std::cout << Color::Reset;

		if (c < ChoiceMax && state.choices.test(c))
		{
			return static_cast<Choice>(c);
		}

		std::cout << Color::Yellow << "Unknown choice.\n" << Color::Yellow;
	}
}
