#include "play.hpp"
#include "solverStrategy.hpp"
#include "miscStrategies.hpp"
#include "displaySolverResults.hpp"

#include <iostream>

void testStrategies()
{
	constexpr int wins = 1000000;
	constexpr double dwins = static_cast<double>(wins);
	std::cout << "Solver:                        " << dwins / playTest(solverStrategy, wins) << "\n";
	std::cout << "Solver equivalent:             " << dwins / playTest(solverEquivalentStrategy, wins) << "\n";
	std::cout << "D4, D12, and if low D10, D8:   " << dwins / playTest(chooseD4D12AndIfLowD10D8Strategy, wins) << "\n";
	std::cout << "D4, D12, and if low D10:       " << dwins / playTest(chooseD4D12AndIfLowD10Strategy, wins) << "\n";
	std::cout << "D10, and if low D12:           " << dwins / playTest(chooseD10AndIfLowD12Strategy, wins) << "\n";
	std::cout << "D12:                           " << dwins / playTest(chooseD12Strategy, wins) << "\n";
	std::cout << "At least half chance success:  " << dwins / playTest(chooseAtLeastHalfOddsStrategy, wins) << "\n";
	std::cout << "More than half chance success: " << dwins / playTest(chooseMoreThanHalfOddsStrategy, wins) << "\n";
	std::cout << "Randomly:                      " << dwins / playTest(chooseRandomlyStrategy, wins) << "\n";
	std::cout << "Lowest:                        " << dwins / playTest(chooseLowestStrategy, wins) << "\n";
	std::cout << "\n";
	std::cout << "Lowest profitable > 0:         " << dwins / playTest(chooseLowestProfitableStrategy<0>, wins) << "\n";
	std::cout << "Lowest profitable > 1:         " << dwins / playTest(chooseLowestProfitableStrategy<1>, wins) << "\n";
	std::cout << "Lowest profitable > 2:         " << dwins / playTest(chooseLowestProfitableStrategy<2>, wins) << "\n";
	std::cout << "Lowest profitable > 3:         " << dwins / playTest(chooseLowestProfitableStrategy<3>, wins) << "\n";
	std::cout << "Lowest profitable > 4:         " << dwins / playTest(chooseLowestProfitableStrategy<4>, wins) << "\n";
	std::cout << "Lowest profitable > 5:         " << dwins / playTest(chooseLowestProfitableStrategy<5>, wins) << "\n";
	std::cout << "Lowest profitable > 6:         " << dwins / playTest(chooseLowestProfitableStrategy<6>, wins) << "\n"; // D12 equivalent
	std::cout << "\n";
	std::cout << "Sequence D4,  D12:             " << dwins / playTest(sequenceStrategy<D4, D12>, wins) << "\n";
	std::cout << "Sequence D6,  D12:             " << dwins / playTest(sequenceStrategy<D6, D12>, wins) << "\n";
	std::cout << "Sequence D8,  D12:             " << dwins / playTest(sequenceStrategy<D8, D12>, wins) << "\n";
	std::cout << "Sequence D10, D12:             " << dwins / playTest(sequenceStrategy<D10, D12>, wins) << "\n";
	std::cout << "Sequence D12, D10:             " << dwins / playTest(sequenceStrategy<D12, D10>, wins) << "\n";
	std::cout << "Sequence D4,  D8,  D12:        " << dwins / playTest(sequenceStrategy<D4, D8, D12>, wins) << "\n";
	std::cout << "Sequence D6,  D8,  D12:        " << dwins / playTest(sequenceStrategy<D6, D8, D12>, wins) << "\n";
	std::cout << "Sequence D6,  D10, D12:        " << dwins / playTest(sequenceStrategy<D6, D10, D12>, wins) << "\n";
	std::cout << "\n";
	// Should fail assert in debug:
	//std::cout << "Cheat with multiple D12s:      " << dwins / playTest(&cheatStrategy, wins) << "\n";
}

int main()
{
	displaySolverResults();
	//displaySolverResultsHtml();
	//displaySolverResultsJson();

	testStrategies();

	return 0;
}
