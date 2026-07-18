#include "Available.hpp"

std::vector<Choice> toVector(const Available& choices)
{
	std::vector<Choice> v;
	v.reserve(choices.count());
	if (choices.test(D4))   v.push_back(D4);
	if (choices.test(D6))   v.push_back(D6);
	if (choices.test(D8))   v.push_back(D8);
	if (choices.test(D10))  v.push_back(D10);
	if (choices.test(D12))  v.push_back(D12);
	if (choices.test(D20))  v.push_back(D20);
	if (choices.test(Bank)) v.push_back(Bank);
	return v;
}
