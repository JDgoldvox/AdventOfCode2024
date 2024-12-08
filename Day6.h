#pragma once
#include "BaseDay.h"

class Day6 : public BaseDay
{
public:
	string Run();
	string Part1(ifstream& inStream);
	string Part2(ifstream& inStream);
private:

	enum class DIRECTION
	{
		NORTH,SOUTH,EAST,WEST
	};

	string inputPath = "input/inputDay6.txt";
	pair<int,int> guardPosition;
	DIRECTION guardDirection;
	map<int, set<int>> obstaclePositions;
	map<int, set<int>> guardVisitedPositions;
	int width = 0, height = 0;

	bool trackTurns = false;
	deque<pair<int, int>> guardlast3Positions; //when guard turns, set position
	deque<DIRECTION> guardlast3Directions; //when guard turns, set position
	set<pair<int,int>> loopPositions;
	unordered_map<pair<int, int>, set<DIRECTION>, hash_pair> obstaclePositionsDirectionHit;

	void WriteObstacleAndGuardPositions(const string& line, const int& y);
	void WriteGuardDirection(const char& guard);

	void WriteGuardMovements();
	void MoveGuard();
	bool HasObstacle(const int& x,const int& y);

	//part 2 box
	bool CheckPathForBox();
	bool CheckInBounds(const int& x, const int& y);
	void AddToLast3GuardPositions(const int& x, const int& y);
	void AddToLast3GuardDirections();
	void AddObstacleDirectionHit(DIRECTION guardHitDirection, const int& xObstacle, const int& yObstacle);
};