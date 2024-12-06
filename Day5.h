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

	void WriteRuleSet(const string& line);
	void DebugRules();
	vector<int> ReturnCorrectlyOrderedPages(const string& line);
	vector<int> ReturnIncorrectlyOrderedPages(const string& line);
	vector<int> ReturnNumbersFromString(const string& line);
	bool IsCharDigit(const char& character);
	

	bool isRules = true; //always read rules first
	map<int, set<int>> rules;
};

