#pragma once

#include "Choice.hpp"

#include <bitset>
#include <iterator>
#include <vector>

// Track available choices on a turn using a small bitset.
using Available = std::bitset<ChoiceMax>;

// Convert a bitset of available choices to a vector of available choices.
std::vector<Choice> toVector(const Available& choices);

//// todo: provide iterator rather than toVector and vector::iterator
//struct AvailableIterator
//{
//	using iterator_category = std::input_iterator_tag;
//	//using difference_type = size_t;
//	using value_type = Choice;
//	using reference = Choice;
//};
