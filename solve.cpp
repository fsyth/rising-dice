#include "solve.hpp"

#include <cassert>
#include <vector>

void exploreTurnNode(TurnNode& turn)
{
	assert(turn.next.empty() && "TurnNode already explored.");

	// Populate next turns
	std::vector<Choice> choices = toVector(turn.state.choices);
	for (Choice choice : choices)
	{
		// Handle bank
		if (choice == Bank)
		{
			TurnNode& nextTurn = turn.next[choice][0];
			nextTurn.state.prevChoice = choice;
			nextTurn.state.prevRoll = 0;
			nextTurn.state.rollNo = turn.state.rollNo + 1;
			nextTurn.state.turnScore = turn.state.turnScore;
			nextTurn.state.choices.reset();

			// No rolls possible, expected score known
			nextTurn.expectedScore = turn.state.turnScore;
			continue;
		}

		// Skip choice if it would always bust
		if (choice < turn.state.prevRoll) continue;

		// Create turn nodes for all roll results
		for (int roll = 1; roll <= choice; ++roll)
		{
			TurnNode& nextTurn = turn.next[choice][roll];
			nextTurn.state.prevChoice = choice;
			nextTurn.state.prevRoll = roll;
			nextTurn.state.rollNo = turn.state.rollNo + 1;

			if (roll < turn.state.prevRoll)
			{
				// Bust
				nextTurn.state.turnScore = 0;
				nextTurn.state.choices.reset();

				// No further choices, expected score known 0
				nextTurn.expectedScore = 0.0;
				continue;
			}

			// Safe
			nextTurn.state.turnScore = turn.state.turnScore + roll;
			nextTurn.state.choices = turn.state.choices;
			nextTurn.state.choices.set(choice, false).set(Bank, true);

			// Optional rule: allow d20 if all five other dice have been rolled
			if (turn.state.rollNo == 4)
				nextTurn.state.choices.set(D20);

			// Can make further choices, so explore recursively
			exploreTurnNode(nextTurn);
		}

	}

	// Average possible rolls for each choice (excluding bank)
	double bestScore = 0;
	Choice bestChoice = Bank;

	for (Choice choice : choices)
	{
		if (choice == Bank)
			continue;

		double sum = 0.0;
		for (const auto& rollResult : turn.next[choice])
			sum += rollResult.second.expectedScore;

		double meanForChoice = sum / choice;

		if (meanForChoice > bestScore)
		{
			bestScore = meanForChoice;
			bestChoice = choice;
		}
	}

	// Bank if that's as good as rolling
	if (turn.state.choices.test(Bank) &&
		turn.next[Bank][0].expectedScore >= bestScore)
	{
		bestScore = turn.next[Bank][0].expectedScore;
		bestChoice = Bank;
	}

	turn.expectedScore = bestScore;
	turn.bestChoiceNext = bestChoice;
}

const TurnNode& solve()
{
	// Static to avoid regenerating each time
	static TurnNode root;

	// Initialize root by exploring exhaustively
	if (root.next.empty()) exploreTurnNode(root);

	return root;
}
