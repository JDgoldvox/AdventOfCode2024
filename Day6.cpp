#include "Day6.h"

string Day6::Run() {
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

string Day6::Part1(ifstream& inStream) {

	string line;
	int y = 0;

	//find width size
	if (getline(inStream, line))
	{
		width = line.size();
	}
	inStream.clear(); // clear bad state after eof
	inStream.seekg(0);

	//read entire text files
	while (getline(inStream, line))
	{
		//get position of all hashtags(obstacles)
		WriteObstacleAndGuardPositions(line, y);
		y++;
	}

	//set height
	height = y;

	//fill guard movements
	WriteGuardMovements();

	//count guard visited positions //search for all positions visited
	int visitPositions = 0;
	for (const auto& [y, xList] : guardVisitedPositions)
	{
		visitPositions += xList.size();
	}

	//remove start and end positions
	visitPositions -= 2;

	return to_string(visitPositions);
}

string Day6::Part2(ifstream& inStream) {

	//bool for part 2
	trackTurns = true;

	string line;
	int y = 0;

	//find width size
	if (getline(inStream, line))
	{
		int x = 0;
		cout << "    ";
		for (auto c : line)
		{
			cout << x;
			x++;
		}
		cout << endl;

		width = line.size();
	}
	inStream.clear(); // clear bad state after eof
	inStream.seekg(0);

	//read entire text files
	while (getline(inStream, line))
	{
		cout << y << " | " << line << endl;
		//get position of all hashtags(obstacles)
		WriteObstacleAndGuardPositions(line, y);
		y++;
	}

	//set height
	height = y;

	//fill guard movements
	WriteGuardMovements();

	//calculate number of potential obstacle positions
	return to_string(loopPositions.size());
}

/// <summary>
/// returns obstacles in this row
/// </summary>
/// <param name="line"></param>
/// <returns></returns>
void Day6::WriteObstacleAndGuardPositions(const string& line, const int& y)
{
	set<int> xPositions;
	//loop through line
	for (int x = 0; x < line.size(); x++)
	{
		//if we find obstacle
		if (line[x] == '#')
		{
			xPositions.insert(x); //store x
		}
		else if (line[x] == '>' || line[x] == '^' || line[x] == '<' || line[x] == 'v')
		{
			guardPosition = { x,y };
			WriteGuardDirection(line[x]);

			//add first visited position
			guardVisitedPositions.emplace(y, set<int>{x});
		}
	}

	//store in obstacle Positions
	obstaclePositions.emplace(y, xPositions);
}

/// <summary>
/// writes all guard movements into a <int,set<int>> where first = y, and second = x's
/// </summary>
void Day6::WriteGuardMovements() {

	//If there is something directly in front of you, turn right 90 degrees
	while (true)
	{
		//readable variables
		auto [x, y] = guardPosition;

		MoveGuard();

		CheckPathForBox();

		//check if guard is out of bounds
		if (x < 0 || x >= width || y < 0 || y >= height)
		{
			break;
		}
	}
}

/// <summary>
/// sets direction guard is facing
/// </summary>
/// <param name="guard"></param>
void Day6::WriteGuardDirection(const char& guard) {
	switch (guard)
	{
		case '>':
			guardDirection = DIRECTION::EAST;
			break;
		case '^':
			guardDirection = DIRECTION::NORTH;
			break;
		case '<':
			guardDirection = DIRECTION::WEST;
			break;
		case 'v':
			guardDirection = DIRECTION::NORTH;
			break;
	}
}

void Day6::MoveGuard() 
{
	//readable variables
	auto& [x, y] = guardPosition;

	switch (guardDirection)
	{
		case DIRECTION::SOUTH:
			if (HasObstacle(x,y + 1)) {

				//face right
				guardDirection = DIRECTION::WEST;
				AddToLast3GuardPositions(x, y);
				AddToLast3GuardDirections();
				AddObstacleDirectionHit(DIRECTION::SOUTH, x, y + 1);
			}
			else { //move north
				y = y + 1;
			}

			break;
		case DIRECTION::EAST:
			if (HasObstacle(x + 1, y)) {
				//face EAST
				guardDirection = DIRECTION::SOUTH;
				AddToLast3GuardPositions(x, y);
				AddToLast3GuardDirections();
				AddObstacleDirectionHit(DIRECTION::EAST, x + 1, y);
			}
			else { //move north
				x = x + 1;
			}

			break;
		case DIRECTION::NORTH:
			if (HasObstacle(x, y - 1)) {
				//face right
				guardDirection = DIRECTION::EAST;
				AddToLast3GuardPositions(x, y);
				AddToLast3GuardDirections();
				AddObstacleDirectionHit(DIRECTION::NORTH, x, y - 1);
			}
			else { //move SOUTH
				y = y - 1;
			}
			break;
		case DIRECTION::WEST:
			if (HasObstacle(x - 1, y)) {
				//face right
				guardDirection = DIRECTION::NORTH;
				AddToLast3GuardPositions(x, y);
				AddToLast3GuardDirections();
				AddObstacleDirectionHit(DIRECTION::WEST, x - 1, y);
			}
			else { //move SOUTH
				x = x - 1;
			}
			break;
	}

	//insert position change into map
	if (guardVisitedPositions.find(y) != guardVisitedPositions.end()) {
		set<int>& xList = guardVisitedPositions.at(y);
		xList.insert(x);
	}
	else //insert y
	{
		guardVisitedPositions.emplace(y, set<int>{x});
	}
}

bool Day6::HasObstacle(const int& x, const int& y) {

	//search for this coord in obstacle positions

	//first search y's
	if (obstaclePositions.find(y) == obstaclePositions.end()) { //if no existance
		return false;
	}

	//we know y has obstacles
	const set<int>& xPositions = obstaclePositions.at(y);

	//search x's
	if (xPositions.find(x) == xPositions.end()) { //if no existance
		return false;
	}

	return true;
}


///// <summary>
///// returns true if box has been created 
///// </summary>
///// <returns></returns>
//bool Day6::CheckPathForBox()
//{	
//	//if less than 3 positions in dequeue , skip
//	if (guardlast3Positions.size() < 3)
//	{
//		return false;
//	}
//
//	int desiredX = guardlast3Positions.back().first;
//	int desiredY = guardlast3Positions.back().second;
//	int currentX = guardPosition.first;
//	int currentY = guardPosition.second;
//	DIRECTION previousDirection = guardlast3Directions.back();
//
//	//check 3rd position direction
//	if (previousDirection == DIRECTION::EAST || previousDirection == DIRECTION::WEST)
//	{
//		//look for similar X position
//		if (currentX == desiredX) 
//		{
//			if (guardDirection == DIRECTION::EAST && CheckInBounds(desiredX + 1, currentY)) //if we are moving towards east
//			{
//				cout << "found position x: " << desiredX + 1 << " y: " << currentY << endl;
//				loopPositions.emplace(pair<int, int>{desiredX + 1, currentY});
//			}
//			else if(guardDirection == DIRECTION::WEST && CheckInBounds(desiredX - 1, currentY))// we are moving west
//			{
//				cout << "found position x: " << desiredX - 1 << " y: " << currentY << endl;
//				loopPositions.emplace(pair<int, int>{desiredX - 1, currentY});
//			}
//		}
//	}
//	else
//	{
//		//look for similar Y position
//		if (currentY == desiredY)
//		{
//			if (guardDirection == DIRECTION::NORTH && CheckInBounds(currentX, desiredY - 1)) //if we are moving north
//			{
//				cout << "found position x: " << currentX << " y: " << desiredY - 1 << endl;
//				loopPositions.emplace(pair<int, int>{currentX, desiredY - 1});
//			}
//			else if (guardDirection == DIRECTION::SOUTH && CheckInBounds(currentX, desiredY + 1))//if we are moving south
//			{
//				cout << "found position x: " << currentX << " y: " << desiredY + 1 << endl;
//				loopPositions.emplace(pair<int, int>{currentX, desiredY + 1});
//			}
//		}
//	}
//
//	return false;
//}

bool Day6::CheckInBounds(const int& x, const int& y) 
{
	if (x < 0 || x >= width && y < 0 || y >= height)
	{
		return false;
	}
	
	//not in obstacles table
	if (obstaclePositions.find(y) != obstaclePositions.end())
	{
		auto obstacleXPositions = obstaclePositions.at(y);
		if (obstacleXPositions.find(x) != obstacleXPositions.end()) {
			return false;
		}
	}

	return true;
}

bool Day6::CheckPathForBox()
{
	//if less than 3 positions in dequeue , skip
	if (guardlast3Positions.size() < 3)
	{
		return false;
	}

	int desiredX = guardlast3Positions.back().first;
	int desiredY = guardlast3Positions.back().second;
	int currentX = guardPosition.first;
	int currentY = guardPosition.second;
	DIRECTION previousDirection = guardlast3Directions.back();

	//check 3rd position direction
	if (previousDirection == DIRECTION::EAST || previousDirection == DIRECTION::WEST)
	{
		//look for similar X position
		if (currentX == desiredX)
		{
			if (guardDirection == DIRECTION::EAST && CheckInBounds(desiredX + 1, currentY)) //if we are moving towards east
			{
				cout << "found position x: " << desiredX + 1 << " y: " << currentY << endl;
				loopPositions.emplace(pair<int, int>{desiredX + 1, currentY});
			}
			else if (guardDirection == DIRECTION::WEST && CheckInBounds(desiredX - 1, currentY))// we are moving west
			{
				cout << "found position x: " << desiredX - 1 << " y: " << currentY << endl;
				loopPositions.emplace(pair<int, int>{desiredX - 1, currentY});
			}
		}
	}
	else
	{
		//look for similar Y position
		if (currentY == desiredY)
		{
			if (guardDirection == DIRECTION::NORTH && CheckInBounds(currentX, desiredY - 1)) //if we are moving north
			{
				cout << "found position x: " << currentX << " y: " << desiredY - 1 << endl;
				loopPositions.emplace(pair<int, int>{currentX, desiredY - 1});
			}
			else if (guardDirection == DIRECTION::SOUTH && CheckInBounds(currentX, desiredY + 1))//if we are moving south
			{
				cout << "found position x: " << currentX << " y: " << desiredY + 1 << endl;
				loopPositions.emplace(pair<int, int>{currentX, desiredY + 1});
			}
		}
	}

	return false;
}

void Day6::AddToLast3GuardPositions(const int& x, const int& y) {
	//if there is an obstacle, for part 2, track turn position
	if (!trackTurns)
	{
		return;
	}

	guardlast3Positions.push_front({ x,y });

	//never have more than 3
	if (guardlast3Positions.size() > 3)
	{
		/*cout << "FRONT: " << guardlast3Positions.front().first << "," << guardlast3Positions.front().second << endl;
		for (auto d : guardlast3Positions)
		{
			cout << "(" << d.first << "," << d.second << ") ,";
		}
		cout << endl;*/

		//cout << "POPPING " << guardlast3Positions.back().first << "," << guardlast3Positions.back().second << endl;

		guardlast3Positions.pop_back();
	}
}

void Day6::AddToLast3GuardDirections()
{
	if (!trackTurns)
	{
		return;
	}

	guardlast3Directions.push_front({ guardDirection });

	//never have more than 3
	if (guardlast3Directions.size() > 3)
	{
		guardlast3Directions.pop_back();
	}
}

void Day6::AddObstacleDirectionHit(DIRECTION guardHitDirection, const int& xObstacle, const int& yObstacle) {
	
	std::pair<int, int> key = { xObstacle, yObstacle };
	auto it = obstaclePositionsDirectionHit.find(key);

	// Determine the opposite direction for each case
	DIRECTION oppositeDirection;
	switch (guardHitDirection) {
	case DIRECTION::SOUTH:
		oppositeDirection = DIRECTION::NORTH;
		break;
	case DIRECTION::NORTH:
		oppositeDirection = DIRECTION::SOUTH;
		break;
	case DIRECTION::EAST:
		oppositeDirection = DIRECTION::WEST;
		break;
	case DIRECTION::WEST:
		oppositeDirection = DIRECTION::EAST;
		break;
	default:
		return; // Handle unexpected input gracefully
	}

	if (it != obstaclePositionsDirectionHit.end()) {
		// Key exists, add the opposite direction to the set
		it->second.insert(oppositeDirection);
	}
	else {
		// Key does not exist, create a new set and add the current direction
		obstaclePositionsDirectionHit[key] = set<DIRECTION>{ guardHitDirection };
	}
}