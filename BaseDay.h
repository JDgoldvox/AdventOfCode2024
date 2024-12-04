#pragma once
#include "Util.h";
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <limits>
#include <map>
#include <array>

using namespace std;

class BaseDay
{
public:
	virtual string Run() = 0;

	virtual string Part1(ifstream& inStream) = 0;
	virtual string Part2(ifstream& inStream) = 0;
};

