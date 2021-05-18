#pragma once

#include "Available.hpp"
#include "Choice.hpp"

constexpr unsigned long initialChoices = (1 << D4) | (1 << D6) | (1 << D8) | (1 << D10) | (1 << D12);

struct TurnState
{
	Available choices{ initialChoices };
	Choice prevChoice = Bank;
	int prevRoll = 0;
	int turnScore = 0;
	int rollNo = 0;
};

struct GameState : TurnState
{
	int gameScore = 0;
	int turnNo = 0;
};
