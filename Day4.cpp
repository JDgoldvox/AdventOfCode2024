#include "Day4.h"

string Day4::Run() {
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

string Day4::Part1(ifstream& inStream) {
	return string();
}

string Day4::Part2(ifstream& inStream) {
	return string();
}