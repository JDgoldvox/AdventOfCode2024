#include "ExampleDay.h"

string ExampleDay::Run() {
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

string ExampleDay::Part1(ifstream& inStream) {
	return string();
}

string ExampleDay::Part2(ifstream& inStream) {
	return string();
}