#pragma once

#include "Choice.hpp"
#include "GameState.hpp"

// Strategy that allows the player to interactively select choices at each
// stage via the console.
Choice solverStrategy(const GameState& state);
