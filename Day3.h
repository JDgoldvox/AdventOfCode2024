#pragma once
#include "BaseDay.h"

class Day3 : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "input/inputDay3.txt";
};
