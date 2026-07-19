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

void d20Rule(GameState& state)
{
	// Optional rule: allow d20 if all five other dice have been rolled
	if (state.rollNo == 5)
		state.choices.set(D20);
}

void removeDumbChoices(GameState& state)
{
	// Optional, but can unset choices that are guaranteed to bust
	state.choices >>= state.prevRoll;
	state.choices <<= state.prevRoll;
}

void playTurnRoll(GameState& state, Choice choice, RollResult rolled)
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

void playTurnBank(GameState& state)
{
	// Indicates a logic error in the strategy passed in.
	assert(state.turnScore > 0 && "Invalid strategy. Cannot bank 0 score for turn.");

	state.prevChoice = Bank;
	state.gameScore += state.turnScore;
	state.choices.reset();
}

void endTurn(GameState& state)
{
	state.choices = initialChoices;
	state.turnScore = 0;
	state.prevRoll = 0;
	state.rollNo = 0;
	++state.turnNo;
}

void playTurn(GameState& state, Strategy choose, GameStateDisplay display)
{
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
	
	display(state);
	endTurn(state);
}

int play(Strategy choose, GameStateDisplay display, int winningScore)
{
	// Setup
	GameState state;

	// Begin game
	while (state.gameScore < winningScore)
	{
		playTurn(state, choose, display);
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
