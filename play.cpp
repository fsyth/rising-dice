#include "play.hpp"

#include "Available.hpp"
#include "Choice.hpp"
#include "GameState.hpp"

#include <cassert>
#include <random>

RollResult roll(Choice die)
{
	return 1 + (std::rand() % die);
}

void d20Rule(TurnState& state)
{
	// Optional rule: allow d20 if all five other dice have been rolled
	if (state.rollNo == 5)
		state.choices.set(D20);
}

void removeDumbChoices(TurnState& state)
{
	// Optional, but can unset choices that are guaranteed to bust
	state.choices >>= state.prevRoll;
	state.choices <<= state.prevRoll;
}

int play(Strategy choose, GameStateDisplay display, int winningScore)
{
	GameState state;

	while (state.gameScore < winningScore)
		playTurn(state, choose, display);

	return state.turnNo;
}

void playTurn(GameState& state, Strategy choose, GameStateDisplay display)
{
	beginTurn(state);

	while (state.choices.any())
	{
		display(state);
		Choice choice = choose(state);

		if (choice == Bank)
		{
			playTurnBank(state);
			break;
		}

		RollResult rolled = roll(choice);
		playTurnRoll(state, choice, rolled);
	}

	endTurn(state);
	display(state);
}

void beginTurn(GameState& state)
{
	// Reset turn state for next turn
	state.choices = initialChoices;
	state.turnScore = 0;
	state.prevRoll = 0;
	state.rollNo = 0;
	++state.turnNo;
}

void playTurnRoll(TurnState& state, Choice choice, RollResult rolled)
{
	// Indicates a logic error in the strategy passed in.
	assert(state.choices.test(choice) && "Invalid strategy. Choice unavailable.");

	++state.rollNo;
	state.prevChoice = choice;

	if (rolled < state.prevRoll)
	{
		// Bust
		state.prevRoll = rolled;
		state.turnScore = 0;
		state.choices.reset();
		return;
	}

	// Safe
	state.prevRoll = rolled;
	state.turnScore += rolled;
	d20Rule(state);
	removeDumbChoices(state);
	state.choices.set(choice, false);
	state.choices.set(Bank);
}

void playTurnBank(TurnState& state)
{
	// Indicates a logic error in the strategy passed in.
	assert(state.turnScore > 0 && "Invalid strategy. Cannot bank 0 score for turn.");

	state.prevChoice = Bank;
	state.choices.reset();
}

void endTurn(GameState& state)
{
	// Either we banked with non-zero turn score, or we bust with zero turn score.
	assert(((state.prevChoice == Bank) != (state.turnScore == 0)) && "Invalid state. Must bank or bust before ending turn.");

	state.gameScore += state.turnScore;
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
