#include "displayGameState.hpp"

#include "Choice.hpp"
#include "Color.hpp"

#include <iostream>

void displayGameState(const GameState& state)
{
	std::cout << Color::Blue << "\n== Turn " << state.turnNo + 1;
	if (state.rollNo > 0)
	{
		if (state.prevChoice == Bank)
			std::cout << " End";
		else
			std::cout << " Roll " << state.rollNo;
	}
	std::cout << " ==" << Color::Reset << '\n';

	if (state.prevRoll != 0)
	{
		std::cout << "Choice:      " << Color::Magenta << state.prevChoice << Color::Reset << '\n';
		if (state.prevChoice != Bank)
			std::cout << "Roll:        " << Color::Magenta << state.prevRoll << Color::Reset << '\n';
	}

	const char* const turnColor = state.rollNo == 0 || state.prevChoice == Bank
		? Color::Reset
		: (state.turnScore > 0 
			? Color::Green 
			: Color::Red);

	const char* const bankColor = state.rollNo != 0 && state.prevChoice == Bank
		? Color::Green
		: Color::Reset;

	std::cout <<
		"Turn score:  " << turnColor << state.turnScore << Color::Reset << '\n' <<
		"Game score:  " << bankColor << state.gameScore << Color::Reset << '\n';

	if (state.choices.any())
	{
		std::cout << "\nChoices:    ";
		if (state.choices.test(D4))   std::cout << Color::Cyan << "(4)"  << Color::Reset << " d4   ";
		if (state.choices.test(D6))   std::cout << Color::Cyan << "(6)"  << Color::Reset << " d6   ";
		if (state.choices.test(D8))   std::cout << Color::Cyan << "(8)"  << Color::Reset << " d8   ";
		if (state.choices.test(D10))  std::cout << Color::Cyan << "(10)" << Color::Reset << " d10   ";
		if (state.choices.test(D12))  std::cout << Color::Cyan << "(12)" << Color::Reset << " d12   ";
		if (state.choices.test(Bank)) std::cout << Color::Cyan << "(0)"  << Color::Reset << " Bank";
		std::cout << Color::Reset << "\n";
	}
	else if (state.prevChoice == Bank)
	{
		std::cout << Color::Green << "Banked." << Color::Reset << '\n';
	}
	else
	{
		std::cout << Color::Red << "Bust!" << Color::Reset << '\n';
	}
}
