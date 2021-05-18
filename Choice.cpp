#include "Choice.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& os, Choice choice)
{
	if (choice == Bank)
		return os << "Bank";

	return os << "d" << static_cast<int>(choice);
}
