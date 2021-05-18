#pragma once

#include "Choice.hpp"
#include "GameState.hpp"

Choice chooseLowestStrategy(const GameState& state);

Choice chooseD12Strategy(const GameState& state);

Choice chooseRandomlyStrategy(const GameState& state);

Choice chooseMoreThanHalfOddsStrategy(const GameState& state);

Choice chooseAtLeastHalfOddsStrategy(const GameState& state);

Choice chooseD10AndIfLowD12Strategy(const GameState& state);

Choice chooseD4D12AndIfLowD10Strategy(const GameState& state);

Choice chooseD4D12AndIfLowD10D8Strategy(const GameState& state);

Choice solverEquivalentStrategy(const GameState& state);

Choice cheatStrategy(const GameState& state);

template <int Threshold>
Choice chooseLowestProfitableStrategy(const GameState& state)
{
	std::vector<Choice> choices = toVector(state.choices);

	for (const auto die : choices)
	{
		if (die <= state.prevRoll) continue;

		const double prob = (static_cast<double>(die) - state.prevRoll) / die;
		const double minRoll = state.prevRoll + 1.0;
		const double maxRoll = die;
		const double avg = (minRoll + maxRoll) / 2;
		const double expected = (state.turnScore + avg) * prob;

		if (expected > state.turnScore + static_cast<double>(Threshold))
			return die;
	}

	return Bank;
}

template <Choice C1, Choice C2 = Bank, Choice C3 = Bank, Choice C4 = Bank, Choice C5 = Bank>
Choice sequenceStrategy(const GameState& state)
{
	static_assert(C1 != Bank, "Cannot bank before the first roll.");
	if (state.choices.test(C1)) return C1;
	if (state.choices.test(C2)) return C2;
	if (state.choices.test(C3)) return C3;
	if (state.choices.test(C4)) return C4;
	if (state.choices.test(C5)) return C5;
	return Bank;
}
