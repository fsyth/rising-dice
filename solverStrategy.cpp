#include "solverStrategy.hpp"

#include "solve.hpp"

Choice solverStrategy(const GameState& state)
{
	static const TurnNode* solverCurrentNode = nullptr;

	const TurnNode& root = solve();

	// Reset if beginning a new turn, otherwise traverse deeper into the network
	solverCurrentNode = state.rollNo == 0
		? &root
		: &solverCurrentNode->next.at(state.prevChoice).at(state.prevRoll);

	return solverCurrentNode->bestChoiceNext;
}
