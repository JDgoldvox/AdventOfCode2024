#pragma once
#include "BaseDay.h"

class Day2 : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	bool IsSafePart1(vector<int>& nums, bool isIncreasing);
	bool HasTrend(vector<int>& nums, bool& isIncreasing);
	bool PassRange(const vector<int>& nums, const bool& isIncreasing);
	bool IsPairInRange(const int& a, const int& b);
	bool IsPairFollowingPattern(const int& prev, const int& next, const bool& isIncreasing);

	string inputPath = "input/inputDay2.txt";
};

