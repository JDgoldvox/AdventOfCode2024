#pragma once
#include "BaseDay.h"

class Day3 : public BaseDay
{
public:
	enum class CurrentMultiplierBeingSet {
		A, B
	};


	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "input/inputDay3.txt";

	vector<int> FindPossibleMuls(const string& line);
	vector<int> FindPossibleMulsWithInstructions(const string& line, bool& instructionEnabled);
	void CheckValidMulsAndSum(const vector<int>& possibleMuls, int& sum, const string& line);
	bool IsNumber(const char& character);
};
