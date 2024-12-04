#pragma once
#include "BaseDay.h"

class Day5 : BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "input/inputDay5.txt";
};

