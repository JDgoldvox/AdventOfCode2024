#include "Day1.h"

string Day1::Run() {
	ifstream inStream;
	inStream.open("input/inputDay1.txt");

	if (!inStream.is_open()) {
		cout << "Error - File did not open\n";
		return string();
	}
	
	string answer = Part2(inStream);
	inStream.close();
	return answer;
}

string Day1::Part1(ifstream& inStream) {
	vector<int> leftList, rightList;
	string line;
	std::stringstream ss;
	int lineLength = 0;

	//go through every line in file && Gather left list and right list of ints
	while (getline(inStream, line)) {
		lineLength = line.length();
		int index = 0;

		//loop characters in line
		while (index <= line.length() - 1) {

			//is a digit
			if (line[index] > 47 && line[index] < 58) {
				ss << line[index];
			}

			//is a space
			if (isspace(line[index]))
			{
				int leftInt = stoi(ss.str());
				leftList.emplace_back(leftInt);

				//reset string stream
				ss.clear();
				ss.str("");

				//3 spaces in between left and right list, skip to start of right list
				index += 3;
				continue;
			}

			index++;
		}

		//insert right most list
		int rightInt = stoi(ss.str());
		rightList.emplace_back(rightInt);

		//reset string stream
		ss.clear();
		ss.str("");
	}

	//sort left and right lists
	sort(leftList.begin(), leftList.end());
	sort(rightList.begin(), rightList.end());

	//compare difference between lists and sum
	int differenceSum = 0;

	//go through every entry in lists
	int listSize = leftList.size();

	for (int i = 0; i < listSize; i++) {
		differenceSum += abs(leftList[i] - rightList[i]);
	}

	return to_string(differenceSum);
}

string Day1::Part2(ifstream& inStream) {

	vector<int> leftList, rightList;
	string line;
	std::stringstream ss;
	int lineLength = 0;

	//go through every line in file && Gather left list and right list of ints
	while (getline(inStream, line)) {
		lineLength = line.length();
		int index = 0;

		//loop characters in line
		while (index <= line.length() - 1) {

			//is a digit
			if (line[index] > 47 && line[index] < 58) {
				ss << line[index];
			}

			//is a space
			if (isspace(line[index]))
			{
				int leftInt = stoi(ss.str());
				leftList.emplace_back(leftInt);

				//reset string stream
				ss.clear();
				ss.str("");

				//3 spaces in between left and right list, skip to start of right list
				index += 3;
				continue;
			}

			index++;
		}

		//insert right most list
		int rightInt = stoi(ss.str());
		rightList.emplace_back(rightInt);

		//reset string stream
		ss.clear();
		ss.str("");
	}

	//create a frequency table for each number
	unordered_map<int,int> frequencyTable;

	//calculate number frequency of each number in right hand list
	for (int num : rightList) {

		//find if it already exists in table
		if (frequencyTable.find(num) == frequencyTable.end()) {
			//add to frequency table
			frequencyTable.emplace(num, 1);
		}
		else { //if number already exists in map
			frequencyTable[num] = frequencyTable.at(num) + 1;
		}
	}

	int similarityScore = 0;
	//go through all left list
	int listSize = leftList.size();
	int similarityMultiplier = 0;
	int currentLeftListNum = 0;
	for (int i = 0; i < listSize; i++) {

		//current number
		currentLeftListNum = leftList[i];

		if (frequencyTable.find(currentLeftListNum) != frequencyTable.end()) {
			similarityMultiplier = frequencyTable.at(currentLeftListNum);
		}
		else {
			similarityMultiplier = 0;
		}
		
		//calculation leftListNum * simularityMultiplier
		similarityScore += leftList[i] * similarityMultiplier;
	}

	return to_string(similarityScore);
}