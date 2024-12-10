#pragma once
#include "Util.h"
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
#include <set>
#include <unordered_set>
#include <deque>
#include <stdint.h>

using namespace std;

class BaseDay
{
public:
	virtual string Run() = 0;

	virtual string Part1(ifstream& inStream) = 0;
	virtual string Part2(ifstream& inStream) = 0;
};

