#pragma once
#include "BaseDay.h"

class ExampleDay : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "";
};

