#pragma once
#include "BaseDay.h"

class Day7 : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "input/inputDay7.txt";

	bool IsValidTestValue(const uint64_t& testValue, const vector<uint64_t>& inputNumbers);
	bool Calculate(const uint64_t& testValue, const vector<uint64_t>& inputNumbers, const int& index, const uint64_t& sum);
	
};
