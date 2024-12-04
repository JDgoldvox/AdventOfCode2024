#pragma once
#include "BaseDay.h"

class Day4 : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:
	string inputPath = "input/inputDay4.txt";

	int NumberOfXMAS(const int& x, const int& y);
	int NumberOfX(const int& x, const int& y);
	bool IsOutOfBounds(const int& x, const int& y);
	bool HasMAS(const int& x1, const int& y1, const int& x2, const int& y2, const int& x3, const int& y3);
	bool HasX(const int& x1, const int& y1, const int& x2, const int& y2, const int& x3, const int& y3, const int& x4, const int& y4);
	array<array<char, 140>, 140> grid;
	int height = 140;
	int width = 140;
};

