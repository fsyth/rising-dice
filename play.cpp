#include "play.hpp"

#include "Available.hpp"
#include "Choice.hpp"
#include "GameState.hpp"

#include <cassert>
#include <random>

int roll(int die)
{
	return 1 + (std::rand() % die);
}

void removeDumbChoices(GameState& state)
{
	// Optional, but can unset choices that are guaranteed to bust
	if (state.prevRoll > D4)  state.choices.set(D4,  false);
	if (state.prevRoll > D6)  state.choices.set(D6,  false);
	if (state.prevRoll > D8)  state.choices.set(D8,  false);
	if (state.prevRoll > D10) state.choices.set(D10, false);
	if (state.prevRoll > D12) state.choices.set(D12, false);
}

int play(Strategy choose, GameStateDisplay display, int winningScore)
{
	// Setup
	GameState state;

	// Begin game
	while (state.gameScore < winningScore)
	{
		// Begin turn
		state.choices = initialChoices;
		display(state);

		Choice choice = choose(state);

		// Indicates a logic error in the strategy passed in.
		assert(choice != Bank && "Invalid strategy. Cannot bank 0 score for turn.");

		state.prevChoice = choice;
		int r = roll(choice);

		state.turnScore = r;
		state.prevRoll = r;
		state.choices.set(choice, false);
		state.choices.set(Bank);
		removeDumbChoices(state);

		while (true)
		{
			++state.rollNo;
			display(state);

			choice = state.choices.count() > 1
				? choose(state)
				: Bank;

			// Indicates a logic error in the strategy passed in.
			assert(state.choices.test(choice) && "Invalid strategy. Choice unavailable.");

			state.prevChoice = choice;

			if (choice == Bank)
			{
				// Bank
				state.gameScore += state.turnScore;
				state.choices.reset();
				++state.rollNo;
				display(state);
				break;
			}

			r = roll(choice);

			if (r < state.prevRoll)
			{
				// Bust
				state.turnScore = 0;
				state.prevRoll = r;
				state.choices.reset();
				++state.rollNo;
				display(state);
				break;
			}

			// Safe
			state.turnScore += r;
			state.prevRoll = r;
			state.choices.set(choice, false);
			removeDumbChoices(state);
		}

		// End turn
		state.turnScore = 0;
		state.prevRoll = 0;
		state.rollNo = 0;
		++state.turnNo;
	}

	return state.turnNo;
}

void noDisplay(const GameState& state)
{
	// Do nothing
}

int playTest(Strategy choose, int winningScore)
{
	// If testing, seed rng at the start of the game for fair comparison between strategies
	std::srand(0);

	return play(choose, &noDisplay, winningScore);
}
