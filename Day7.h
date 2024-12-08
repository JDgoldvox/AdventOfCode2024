#pragma once
#include "BaseDay.h"

class Day7 : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "";
};

