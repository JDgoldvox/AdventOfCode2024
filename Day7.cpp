#include "Day7.h"

string Day7::Run() {
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

string Day7::Part1(ifstream& inStream) {

	string line;
	uint64_t testValueSum = 0;

	while (getline(inStream, line)) 
	{
		istringstream ss(line);
		uint64_t testValue;
		vector<uint64_t> inputNumbers;

		//read test value
		{
			string tempTestValue;
			ss >> tempTestValue;
			tempTestValue.pop_back();
			testValue = stoull(tempTestValue); // Safely parse the value
		}

		//read numbers
		{
			uint64_t tmpNum;
			while (ss >> tmpNum)
				inputNumbers.push_back(tmpNum);
		}

		//calculate
		if (IsValidTestValue(testValue, inputNumbers))
		{
			testValueSum += testValue;
		}
	}

	cout << testValueSum << endl;
	return to_string(testValueSum);
}

string Day7::Part2(ifstream& inStream) {

	return string();
}

bool Day7::IsValidTestValue(const uint64_t& testValue, const vector<uint64_t>& inputNumbers) {
	return Calculate(testValue, inputNumbers, 1, inputNumbers[0]);
}

/// <summary>
/// GO through binary tree until sum matches test value
/// </summary>
/// <param name="testValue"></param>
/// <param name="inputNumbers"></param>
/// <param name="index"></param>
/// <param name="sum"></param>
/// <returns></returns>
bool Day7::Calculate(const uint64_t& testValue, const vector<uint64_t>& inputNumbers, const int& index, const uint64_t& sum)
{
	//When we reach the end, check if we match test value
	if (index == inputNumbers.size())
	{
		return sum == testValue;
	}
	else if (sum > testValue)
	{
		return false;
	}

	//Left branch +
	if (Calculate(testValue, inputNumbers, index + 1, sum + inputNumbers[index])){
		return true;
	}

	//right branch *
	if(Calculate(testValue, inputNumbers, index + 1, sum * inputNumbers[index])){
		return true;
	}

	return false;
}