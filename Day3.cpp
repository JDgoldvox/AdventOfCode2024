#include "Day3.h"

string Day3::Run() {
	ifstream inStream;
	inStream.open(inputPath);

	if (!inStream.is_open()) {
		cout << "Error - File did not open\n";
		return string();
	}

	string answer = Part1(inStream);
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
	return string();
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

	for(int x: possibleMuls) {
		cout << x << endl;
	}
	//std::cout << "---------\n";

	/*for (int x : possibleMuls) {
		
		for (int i = x; i < lastIndexInLine + 1; i++)
		{
			cout << line[i];
		}

		std::cout << endl;
	}*/

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