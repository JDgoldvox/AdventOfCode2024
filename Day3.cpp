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
	return string();
}

string Day3::Part2(ifstream& inStream) {
	return string();
}