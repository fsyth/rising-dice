#include "miscStrategies.hpp"

#include <random>

Choice chooseLowestStrategy(const GameState& state)
{
	if (state.choices.test(D4))   return D4;
	if (state.choices.test(D6))   return D6;
	if (state.choices.test(D8))   return D8;
	if (state.choices.test(D10))  return D10;
	if (state.choices.test(D12))  return D12;
	return Bank;
}

Choice chooseD12Strategy(const GameState& state)
{
	if (state.choices.test(D12))  return D12;
	return Bank;
}

Choice chooseRandomlyStrategy(const GameState& state)
{
	std::vector<Choice> choices = toVector(state.choices);

	int r = std::rand() % choices.size();
	return choices[r];
}

Choice chooseMoreThanHalfOddsStrategy(const GameState& state)
{
	std::vector<Choice> choices = toVector(state.choices);

	for (Choice c : choices)
	{
		if (c > 2 * state.turnScore)
			return c;
	}

	return Bank;
}

Choice chooseAtLeastHalfOddsStrategy(const GameState& state)
{
	std::vector<Choice> choices = toVector(state.choices);

	for (Choice c : choices)
	{
		if (c >= 2 * state.turnScore)
			return c;
	}

	return Bank;
}

Choice chooseD10AndIfLowD12Strategy(const GameState& state)
{
	if (state.rollNo == 0)
		return D10;

	if (state.rollNo == 1 && state.prevRoll <= 7)
		return D12;

	return Bank;
}

Choice chooseD4D12AndIfLowD10Strategy(const GameState& state)
{
	if (state.rollNo == 0)
		return D4;

	if (state.rollNo == 1)
		return D12;

	if (state.rollNo == 2 && state.prevRoll <= 5)
		return D10;

	return Bank;
}

Choice chooseD4D12AndIfLowD10D8Strategy(const GameState& state)
{
	// Always start with D4
	if (state.rollNo == 0)
		return D4;

	// Always follow up with d12
	if (state.rollNo == 1)
		return D12;

	// Then d10 if low scoring so far
	if (state.rollNo == 2 && state.prevRoll <= 5)
		return D10;

	// Only d8 if minimal score so far (d4:1, d12:2, d10:3)
	if (state.rollNo == 3 && state.prevRoll <= 3)
		return D8;

	return Bank;
}

Choice solverEquivalentStrategy(const GameState& state)
{
	// Always start with d4
	if (state.rollNo == 0)
		return D4;

	// Always follow up with d12
	if (state.rollNo == 1)
		return D12;

	// Then d10 if low scoring so far
	if (state.rollNo == 2 && state.prevRoll <= 5 && state.turnScore <= 7)
		return D10;

	// Only d8 if minimal score so far (d4:1, d12:2, d10:3)
	if (state.rollNo == 3 && state.prevRoll <= 3)
		return D8;

	return Bank;
}

Choice cheatStrategy(const GameState& state)
{
	if (state.rollNo == 0)
		return D12;

	if (state.rollNo == 1 && state.prevRoll <= 7)
		return D12; // Should fail assert for D12 being unavailable

	return Bank;
}
