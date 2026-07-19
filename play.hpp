#pragma once

#include "Choice.hpp"
#include "GameState.hpp"

#include <functional>

// Function signature for a strategy,
// i.e. for a given GameState, return a Choice.
using Strategy = std::function<Choice (const GameState&)>;

// Function signature for displaying the current GameState.
using GameStateDisplay = std::function<void (const GameState&)>;

// Roll a die, generating a random number from 1 to die.
RollResult roll(Choice die);

// Play a game. The strategy provided will be asked for choices until the
// winning score is reached.
// Each time the GameState is updated, display will be called.
// Returns the final turn number reached.
int play(Strategy choose, GameStateDisplay display, int winningScore = 100);

// Play a single turn of a game. The strategy provided will be asked for
// choices until the turn ends in a bank or bust.
void playTurn(GameState& state, Strategy choose, GameStateDisplay display);

// Update the game state to begin a new turn.
void beginTurn(GameState& state);

// Update the turn state with a given choice of die and rolled result.
void playTurnRoll(TurnState& state, Choice choice, RollResult rolled);

// Update the turn state with a choice of Bank.
void playTurnBank(TurnState& state);

// Update the game state with the final turn state (bank or bust).
void endTurn(GameState& state);

// Test a strategy. This plays a game, but display is disabled and the rng is
// seeded at the start.
// Returns the final turn number reached.
int playTest(Strategy choose, int winningScore = 100);
