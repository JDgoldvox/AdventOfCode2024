#include "Day5.h"

string Day5::Run() {
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

string Day5::Part1(ifstream& inStream) {
	return string();
}

string Day5::Part2(ifstream& inStream) {
	return string();
}