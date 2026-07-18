#pragma once

#include "Choice.hpp"
#include "GameState.hpp"

#include <map>

struct TurnNode
{
	Choice bestChoiceNext = Bank;
	double expectedScore = 0.0; // mean of outcomes
	TurnState state;
	std::map<Choice, std::map<RollResult, TurnNode>> next;
};

const TurnNode& solve();
