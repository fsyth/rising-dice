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

// Test a strategy. This plays a game, but display is disabled and the rng is
// seeded at the start.
// Returns the final turn number reached.
int playTest(Strategy choose, int winningScore = 100);
