#include "Day2.h"

string Day2::Run() {
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

string Day2::Part1(ifstream& inStream) {
	string line;
	int safeReports = 0;

	//go through every line in file
	while (getline(inStream, line)) {
		stringstream ss(line);
		vector<int> nums;
		string numAsString;

		bool isIncreasing = false;
		bool isSafe = true;

		//loop through all characters in mulitple number chunks
		while (ss >> numAsString) {
			//convert string num to int num
			int num = stoi(numAsString);

			//add to vec
			nums.push_back(num);

			//figure out if we are decreasing or increasing ONLY if we have 2 nums in vector
			if (nums.size() == 2) {
				if (nums[0] < nums[1]) {
					isIncreasing = true;
				}
				else {
					isIncreasing = false;
				}
			}

			//check if we are matching requirements

			//check if we are still increasing or decreasing
			if (nums.size() > 1) {
				if (!IsSafePart1(nums, isIncreasing)) {
					//cout << "NOT SAFE\n";
					isSafe = false;
					break;
				}
			}
		}

		if (isSafe) {
			safeReports++;
		}
	}

	return to_string(safeReports);
}

string Day2::Part2(ifstream& inStream) {
	string line;
	int safeReports = 0;

	//go through every line in file
	while (getline(inStream, line)) {
		stringstream ss(line);
		vector<int> nums;
		string numAsString;

		bool isIncreasing = false;
		bool isSafe = true;

		//loop through all characters in mulitple number chunks
		while (ss >> numAsString) {
			//convert string num to int num
			int num = stoi(numAsString);

			//add to vec
			nums.push_back(num);
		}

		//check trend
		if (!HasTrend(nums, isIncreasing)) {
			cout << "FAIL\n";
			continue;
		}

		//check if numbers match range with Problem Dampener (1 wrong number)
		if (!PassRange(nums, isIncreasing)) {
			cout << "FAIL\n";
			continue;
		}

		safeReports++;
		cout << "PASS\n";
	}

	return to_string(safeReports);
}

bool Day2::IsSafePart1(vector<int>& nums, bool isIncreasing) {

	int difference = 0;
	int currentNum = nums[nums.size() - 1];
	int previousNum = nums[nums.size() - 2];

	//check if we are continuing pattern
	if (isIncreasing) {
		//current - previous = positive if safe
		difference = currentNum - previousNum;

		//check if pattern is continuing
		if (difference <= 0) {
			return false;
		}
	}
	else {
		//current - previous = negative if safe
		difference = nums[nums.size() - 1] - nums[nums.size() - 2];

		//check if pattern is continuing
		if (difference >= 0) {
			return false;
		}
	}

	//check if we are in safe range
	if (abs(currentNum - previousNum) > 3) {
		return false;
	}

	return true;
}

/// <summary>
/// Compare whether the trend increases or decreases overall. If there is too much of a change, return false with no trend.
/// </summary>
/// <param name="nums"></param>
/// <param name="isIncreasing"></param>
/// <returns></returns>
bool Day2::HasTrend(vector<int>& nums, bool& isIncreasing) {
	cout << "------------\n";
	int increase = 0;
	int decrease = 0;
	int noDifference = 0;

	int sizeOfList = nums.size();
	int lastElementIndex = sizeOfList - 1;
	//loop through entire list of numbers
	for (int i = 0; i < sizeOfList; i++) {

		//do not compare last element with last element + 1
		if (i == lastElementIndex) {
			break;
		}

		//check if next number increases or decreases
		if (nums[i] < nums[i + 1]) 
		{
			cout << "inc\n";
			increase++;
		}
		else if (nums[i] > nums[i + 1])
		{
			cout << "dec\n";
			decrease++;
		}
		else {
			cout << "net 0\n";
			noDifference++;
		}
		
		//no more than 1 no difference
		if (noDifference > 1) {
			cout << "FAILED PATTERN\n";
			return false;
		}

		//if equal at 2 or above fail
		if (increase >= 2 && decrease >= 2) {
			cout << "FAILED PATTERN\n";
			return false;
		}

		//no more than 1 decrease if increasing
		if (increase > decrease && decrease > 1) {
			cout << "FAILED PATTERN\n";
			return false;
		}

		//no more than 1 increase if decreasing
		if (decrease > increase && increase > 1) {
			cout << "FAILED PATTERN\n";
			return false;
		}

		//if no difference happens once and 
		if (noDifference && increase >= 1 && decrease >= 1) {
			return false;
		}
	}

	//set increasing or decreasing
	if (increase > decrease) {
		isIncreasing = true;
	}
	else {
		isIncreasing = false;
	}

	return true;
}

bool Day2::PassRange(const vector<int>& nums, const bool& isIncreasing) {

	////go through every number to check if range matches
	//int sizeOfList = nums.size();
	//int lastIndex = sizeOfList - 1;
	//int difference = 0;
	//int errors = 0;

	//std::cout << "____________\n";
	//for (int x : nums) {
	//	std::cout << x << " ";
	//}
	//std::cout << std::endl;

	//for (int i = 0; i < sizeOfList; i++) {

	//	if (i == lastIndex) {
	//		
	//		//check prev
	//		int prevNum = nums[i - 1];
	//		int currentNum = nums[i];
	//		if (!IsPairInRange(prevNum, currentNum)) {
	//			errors++;
	//		}

	//		if (errors > 1) {
	//			return false;
	//		}

	//		break;;
	//	}

	//	int currentNum = nums[i];
	//	int nextNum = nums[i + 1];

	//	//if next is not following pattern
	//	if (currentNum > nextNum && isIncreasing) {
	//		errors++;
	//		i++;
	//		std::cout << nextNum << " skipped\n";

	//		//check if new connected numbers make sense

	//		//check if pattern continuing
	//		int nextNextNum = nums[i + 1];

	//		if (!IsPairFollowingPattern(currentNum, nextNextNum, isIncreasing) 
	//			&&!IsPairInRange(nums[i - 1], nums[i + 1])) 
	//		{
	//			std::cout << nextNum << " joined numbers failed\n";

	//			//has prev
	//			if (i != 1) {
	//				errors++;
	//				continue;
	//			}

	//			int prevNum = nums[i - 1];
	//			//check whether prev links with next
	//			if (!IsPairFollowingPattern(prevNum, nextNextNum, isIncreasing)
	//				&& !IsPairInRange(prevNum, nextNextNum))
	//			{

	//			}
	//			else {
	//				errors++;
	//			}
	//		}

	//		if (errors > 1) {
	//			return false;
	//		}
	//		continue;
	//	}

	//	//if next is not in range
	//	if (!IsPairInRange(currentNum, nextNum)) {
	//		errors++;
	//		i++;
	//		std::cout << nextNum << " skipped\n";

	//		//check if pattern continuing
	//		if (!IsPairFollowingPattern(nums[i - 1], nums[i + 1], isIncreasing)) {
	//			std::cout << nextNum << " joined numbers failed\n";
	//			errors++;
	//		}

	//		if (!IsPairInRange(nums[i - 1], nums[i + 1])) {
	//			std::cout << nextNum << " joined numbers failed\n";
	//			errors++;
	//		}
	//		continue;
	//	}

	//	if (errors > 1) {
	//		return false;
	//	}

	//}

	return true;
}

bool Day2::IsPairInRange(const int& a, const int& b) {
	
	int a1 = abs(a); 
	int a2 = abs(b);

	if (abs(a1 - a2) > 3) {
		return false;
	}
	else {
		return true;
	}
}

bool Day2::IsPairFollowingPattern(const int& prev, const int& next, const bool& isIncreasing) {

	//if increasing
	if (prev > next && isIncreasing) {
		return true;
	}
	else if (prev < next && !isIncreasing) {
		return true;
	}
	else {
		return false;
	}
}