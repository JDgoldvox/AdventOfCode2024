#include "Day4.h"

string Day4::Run() {
	ifstream inStream;
	inStream.open(inputPath);

	if (!inStream.is_open()) {
		cout << "Error - File did not open\n";
		return string();
	}

	string answer = Part2(inStream);
	inStream.close();
	return answer;
}

string Day4::Part1(ifstream& inStream) {
	string line;
	vector<char> row;
	int xmasNum = 0;

	//fill grid
	{
		int y = 0;
		while (getline(inStream, line))
		{
			int lineLength = line.length();
			for (int x = 0; x < lineLength; x++)
			{
				grid[x][y] = line[x];
			}
			y++;
		}
	}

	//check for XMAS
	for (int y = 0; y <= height - 1; y++)
	{
		for (int x = 0; x <= width - 1; x++)
		{
			//look for X's
			if (grid[x][y] == 'X')
			{
				xmasNum += NumberOfXMAS(x, y);
			}
			
		}
	}

	return to_string(xmasNum);
}

string Day4::Part2(ifstream& inStream) {
	string line;
	vector<char> row;
	int xmasNum = 0;

	//fill grid
	{
		int y = 0;
		while (getline(inStream, line))
		{
			int lineLength = line.length();
			for (int x = 0; x < lineLength; x++)
			{
				grid[x][y] = line[x];
			}
			y++;
		}
	}

	//check for XMAS
	for (int y = 0; y <= height - 1; y++)
	{
		for (int x = 0; x <= width - 1; x++)
		{
			//look for X's
			if (grid[x][y] == 'A')
			{
				xmasNum += NumberOfX(x, y);
			}

		}
	}

	return to_string(xmasNum);
}

int Day4::NumberOfXMAS(const int& x, const int& y)
{
	int num = 0;

	//CARDINAL DIRECTIONS **********************************************************************
	
	//check UP
	if (HasMAS(x, y + 1, x, y + 2, x, y + 3))
	{
		num++;
	}

	//check DOWN
	if (HasMAS(x, y - 1, x, y - 2, x, y - 3))
	{
		num++;
	}

	//check LEFT
	if (HasMAS(x - 1, y, x - 2, y, x - 3, y))
	{
		num++;
	}

	//check RIGHT
	if (HasMAS(x + 1, y, x + 2, y, x + 3, y))
	{
		num++;
	}

	//ORDINAL ********************************************************************

	//TOP RIGHT
	if (HasMAS(x + 1, y + 1, x + 2, y + 2, x + 3, y + 3))
	{
		num++;
	}

	//TOP LEFT
	if (HasMAS(x - 1, y + 1, x - 2, y + 2, x - 3, y + 3))
	{
		num++;
	}

	//BOTTOM LEFT
	if (HasMAS(x - 1, y - 1, x - 2, y - 2, x - 3, y - 3))
	{
		num++;
	}

	//BOTTOM RIGHT
	if (HasMAS(x + 1, y - 1, x + 2, y - 2, x + 3, y - 3))
	{
		num++;
	}

	return num;
}

bool Day4::IsOutOfBounds(const int& x, const int& y)
{
	if (x < 0 || x >= width)
	{
		return true;
	}

	if (y < 0 || y >= height)
	{
		return true;
	}

	return false;
}

/// <summary>
/// returns true if MAS is found wtihin 3 coords in order
/// </summary>
/// <returns></returns>
bool Day4::HasMAS(const int& x1, const int& y1, const int& x2, const int& y2, const int& x3, const int& y3)
{
	//check if coords in bounds
	if (IsOutOfBounds(x1, y1) || IsOutOfBounds(x2, y2) || IsOutOfBounds(x3, y3))
	{
		return false;
	}

	//check whether we have "MAS"
	if (grid[x1][y1] == 'M' && grid[x2][y2] == 'A' && grid[x3][y3] == 'S')
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/// <summary>
/// returns number of X's made with MAS
/// X1,X2 are coupled with X2,Y2 and X3,Y3 are coupled with X4,Y4
/// </summary>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
/// <returns></returns>
bool Day4::HasX(const int& x1, const int& y1, const int& x2, const int& y2, const int& x3, const int& y3, const int& x4, const int& y4)
{
	//check if coords in bounds
	if (IsOutOfBounds(x1, y1) || IsOutOfBounds(x2, y2) || IsOutOfBounds(x3, y3) || IsOutOfBounds(x4, y4))
	{
		return false;
	}

	//check whether we have "MAS"
	if (grid[x1][y1] == 'M' && grid[x2][y2] == 'S' || grid[x1][y1] == 'S' && grid[x2][y2] == 'M')
	{
		if (grid[x3][y3] == 'M' && grid[x4][y4] == 'S' || grid[x3][y3] == 'S' && grid[x4][y4] == 'M')
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// Find X's created with MAS
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int Day4::NumberOfX(const int& x, const int& y)
{
	int num = 0;

	//TOP RIGHT && TOP LEFT
	if (HasX(x + 1, y + 1, x - 1, y - 1, x - 1, y + 1, x + 1, y - 1))
	{
		num++;
	}

	return num;
}