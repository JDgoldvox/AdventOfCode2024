#include "Day3.h"

string Day3::Run() {
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

string Day3::Part1(ifstream& inStream) {
	string line;
	int sum = 0;

	while (getline(inStream, line)) {
		vector<int> possibleMuls = FindPossibleMuls(line);
		CheckValidMulsAndSum(possibleMuls, sum, line);
	}

	return to_string(sum);
}

string Day3::Part2(ifstream& inStream) {
	string line;
	int sum = 0;

	bool instructionEnabled = true;
	while (getline(inStream, line)) {
		vector<int> possibleMuls = FindPossibleMulsWithInstructions(line, instructionEnabled);
		CheckValidMulsAndSum(possibleMuls, sum, line);
	}

	return to_string(sum);
}

/// <summary>
/// Returns list of locations where it has "mul(" 
/// </summary>
/// <returns></returns>
vector<int> Day3::FindPossibleMuls(const string& line)
{
	vector<int> possibleMuls;
	int lastIndexInLine = line.size() - 1;
	int lastIndexFound = 0;

	//search for muls

	while (line.find("mul(", lastIndexFound) != line.npos) {
		lastIndexFound = line.find("mul(", lastIndexFound);
		possibleMuls.push_back(lastIndexFound);

		//add atleast 4 chars
		lastIndexFound += 4;
	}

	return possibleMuls;
}

/// <summary>
/// Similar to FindPossibleMuls(), just with don't() removed
/// </summary>
/// <param name="line"></param>
/// <returns></returns>
vector<int> Day3::FindPossibleMulsWithInstructions(const string& line, bool& instructionEnabledInitialState)
{
	int lastIndexInLine = line.size() - 1;
	int lastIndexFound = 0;
	int instructionEnabled = instructionEnabledInitialState;

	map<int, bool> significantInstructionPositions;

	//check when there are significant function *****************

	//find do instruction positions
	while (line.find("do()", lastIndexFound) != line.npos) {
		//update last index found
		lastIndexFound = line.find("do()", lastIndexFound);
		significantInstructionPositions.emplace(lastIndexFound, true);
		lastIndexFound += 4;
	}
	lastIndexFound = 0;

	//find don't instruction positions
	while (line.find("don't()", lastIndexFound) != line.npos) {
		//update last index found
		lastIndexFound = line.find("don't()", lastIndexFound);
		significantInstructionPositions.emplace(lastIndexFound, false);
		lastIndexFound += 7;
	}

	instructionEnabled = instructionEnabledInitialState;
	lastIndexFound = 0;
	//sort out significant changes
	for (auto it = significantInstructionPositions.begin(); it != significantInstructionPositions.end(); ) {
		
		//get info
		const auto& [position, isEnabled] = *it;

		// remove if not significant data
		if ((isEnabled && instructionEnabled) || (!isEnabled && !instructionEnabled)) {
			// Erase the element and don't increment the iterator, because erase returns the next valid iterator
			it = significantInstructionPositions.erase(it);
		}
		else 
		{
			//Change current instruction
			instructionEnabled = (isEnabled) ? true : false;

			//increment itt only if we are keeping value, else stay
			it++;
		}
	}

	//search for muls *******************************
	instructionEnabled = instructionEnabledInitialState;
	vector<int> possibleMuls;
	while (line.find("mul(", lastIndexFound) != line.npos) {
		lastIndexFound = line.find("mul(", lastIndexFound);
		
		//check if we need to use this mul potential depending on current instruction
		//find instruction relevent to this

		int lastInstructionPosition = -1;

		for (const auto& [position, isEnabled] : significantInstructionPositions)
		{
			//find instruction at a position larger than this
			if (position > lastInstructionPosition && position < lastIndexFound)
			{
				lastInstructionPosition = position;
			}

			if(position > lastIndexFound) //exit if we found positions larger than current mul pos
			{
				break;
			}
		}

		//if no instruction, follow previous initial instruction
		if (lastInstructionPosition == -1)
		{
			if (instructionEnabledInitialState)
			{
				possibleMuls.push_back(lastIndexFound);
			}
		}
		else 
		{
			if (significantInstructionPositions.at(lastInstructionPosition))
			{
				//cout << "ENABLE INSTRUCTION\n";
				possibleMuls.push_back(lastIndexFound);
			}
			else {
				//cout << "DISABLE INSTRUCTION\n";
			}
		}

		//add atleast 4 chars to skip past the "mul("
		lastIndexFound += 4;
	}

	//ensure the last instruction is kept
	instructionEnabledInitialState = significantInstructionPositions.rbegin()->second;

	return possibleMuls;
}

/// <summary>
/// Checks all possible muls for "x,x)" with x = valid number 
/// </summary>
/// <param name="possibleMuls"></param>
/// <param name="sum"></param>
/// <param name="line"></param>
void Day3::CheckValidMulsAndSum(const vector<int>& possibleMuls, int& sum, const string& line) 
{
	size_t lineSize = line.size();

	//check every possible mul
	for (int possibleMul : possibleMuls) {

		string multiplierA = "";
		string multiplierB =  "";
		CurrentMultiplierBeingSet currentMultiplierBeingSet = CurrentMultiplierBeingSet::A;

		//go through chars beginning at this possibleMulIndex
		// we already have mul(so + 5 to start at the next char
		for (int i = possibleMul + 4; i < lineSize; i++)
		{
			char c = line[i];

			//Check if valid character, otherwise fail completely for this mul possibility
			if (!IsNumber(c) && !isspace(c) && c != ',' && c != ')')
			{
				break;
			}

			//switch to 2nd multiplier
			if (c == ',' && currentMultiplierBeingSet == CurrentMultiplierBeingSet::A)
			{
				currentMultiplierBeingSet = CurrentMultiplierBeingSet::B;
				continue;
			}
			else if (c == ',' && currentMultiplierBeingSet == CurrentMultiplierBeingSet::B)
			{
				break;
			}

			//end of mul
			if (c == ')') 
			{
				//check if multiplier B has anything
				if (multiplierB.size() == 0) {
					break;
				}

				//sum
				sum += stoi(multiplierA) * stoi(multiplierB);
				//cout << stoi(multiplierA) << " x " << stoi(multiplierB) << endl;

				break;
			}

			//add current char to multiplier
			if (currentMultiplierBeingSet == CurrentMultiplierBeingSet::A)
			{
				multiplierA += c;
			}
			else {
				multiplierB += c;
			}
		}
	}
}

bool Day3::IsNumber(const char& character) {
	return (character > 47 && character < 58) ? true : false;
}