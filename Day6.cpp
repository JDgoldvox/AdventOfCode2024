#include "Day6.h"

string Day6::Run() {
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

string Day6::Part1(ifstream& inStream) {
	return string();
}

string Day6::Part2(ifstream& inStream) {
	return string();
}