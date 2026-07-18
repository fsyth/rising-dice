#pragma once

#include <iosfwd>

using RollResult = int;

// It's actually desirable to use an enum over an enum class here since integer
// conversion is frequent
#pragma warning(disable:26812)
enum Choice : RollResult
{
	Bank = 0,
	D4 = 4,
	D6 = 6,
	D8 = 8,
	D10 = 10,
	D12 = 12,
	D20 = 20,
	ChoiceMax
};

std::ostream& operator<<(std::ostream& os, Choice choice);
