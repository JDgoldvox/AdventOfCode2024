#include "Day5.h"

string Day5::Run() {
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

string Day5::Part1(ifstream& inStream) {

	string line = "";
	int middlePageSum = 0;

	while (getline(inStream, line))
	{
		if (isRules)
		{
			WriteRuleSet(line);
		}
		else if(!isRules) //we are reading updates
		{
			vector<int> correctPageOrder = ReturnCorrectlyOrderedPages(line);
			
			//middle page
			int pagesNum = correctPageOrder.size();
			if (pagesNum == 0) //no pages
			{
				continue;
			}

			int middlePage = correctPageOrder[(pagesNum - 1)/ 2];
			//add to middle page sum
			middlePageSum += middlePage;
		}
		
	}

	return to_string(middlePageSum);
}

string Day5::Part2(ifstream& inStream) {
	string line = "";
	int middlePageSum = 0;

	while (getline(inStream, line))
	{
		if (isRules)
		{
			WriteRuleSet(line);
		}
		else if (!isRules) //we are reading updates
		{
			vector<int> correctPageOrder = ReturnIncorrectlyOrderedPages(line);

			//middle page
			int pagesNum = correctPageOrder.size();
			if (pagesNum == 0) //no pages
			{
				continue;
			}

			int middlePage = correctPageOrder[(pagesNum - 1) / 2];
			//add to middle page sum
			middlePageSum += middlePage;
		}

	}

	return to_string(middlePageSum);
}

void Day5::WriteRuleSet(const string& line)
{
	//start off writing rules into table
	if (line.size() > 0)
	{
		//loop over line
		int lineSize = line.size();
		int target = 0;
		int rule = 0;
		string currentNum = "";

		for (int i = 0; i < lineSize; i++)
		{
			//is a digit
			if (IsCharDigit(line[i]))
			{
				currentNum += line[i];
			}
			else if (line[i] == '|')
			{
				//emplace first number and convert to int
				target = stoi(currentNum);
				currentNum.clear();
			}
		}
		//emplace second number and convert to int
		rule = stoi(currentNum);

		if (rules.find(target) != rules.end())
		{
			//target already has rules
			rules[target].insert(rule);
		}
		else
		{
			//create new rule set
			rules.emplace(target, set<int>{rule});
		}
	}
	else 
	{
		isRules = false;
	}
}

/// <summary>
/// print rule table
/// </summary>
void Day5::DebugRules() {
	for (const auto& [target, rules] : rules)
	{
		cout << target << " : ";

		for (const int& num : rules)
		{
			cout << num << ", ";
		}

		cout << endl;
	}
}

vector<int> Day5::ReturnCorrectlyOrderedPages(const string& line)
{
	vector<int>nums = ReturnNumbersFromString(line);

	//higher points = lower order
	map<int, set<int>> orderScore;

	set<int> numbersWithNoRules;

	//score the numbers
	int numsListSize = nums.size();
	int score = 0;
	for (int numIndex = 0; numIndex < numsListSize; numIndex++)
	{
		//get rule set
		set<int> ruleSet;
		int currentScore = 0;
		int currentNum = nums[numIndex];

		//if there are rules
		if (rules.find(currentNum) != rules.end())
		{
			ruleSet = rules.at(currentNum);
			
			//check whether the other numbers are inside current number's rule set
			for (const int& otherNum: nums)
			{
				if (otherNum == currentNum)
				{
					continue;
				}

				if (ruleSet.find(otherNum) != ruleSet.end())
				{
					currentScore++;
				}
				else {
				}
			}

			//insert score into table
			orderScore[currentScore].insert(currentNum);
		}
		else {
			//insert score into table
			orderScore[0].insert(currentNum);
		}
	}

	//combine all orders together

	vector<int> correctOrder;

	for (const auto& [score, pageNumbers] : orderScore)
	{
		for (const int& pageNum : pageNumbers)
		{
			correctOrder.push_back(pageNum);
		}
	}

	//higher number = more likely it is first
	reverse(correctOrder.begin(), correctOrder.end());

	//check if they are in the same order as it started in
	bool isCorrect = true;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] != correctOrder[i]) {
			isCorrect = false;
			break;
		}
	}

	if (!isCorrect)
	{
		return vector<int>();
	}
	
	return correctOrder;
}

vector<int> Day5::ReturnNumbersFromString(const string& line) {

	int lineSize = line.size();
	vector<int> listOfNums;
	string currentNum = "";

	for (int i = 0; i < lineSize; i++)
	{
		if (IsCharDigit(line[i]))
		{
			currentNum += line[i];
		}
		else if (line[i] == ',')
		{
			listOfNums.push_back(stoi(currentNum));
			currentNum.clear();
		}
	}

	//include last num
	listOfNums.push_back(stoi(currentNum));

	return listOfNums;
}

bool Day5::IsCharDigit(const char& character) {
	if (character > 47 && character < 58)
	{
		return true;
	}
	else {
		return false;
	}
}

vector<int> Day5::ReturnIncorrectlyOrderedPages(const string& line)
{
	vector<int>nums = ReturnNumbersFromString(line);

	//higher points = lower order
	map<int, set<int>> orderScore;

	set<int> numbersWithNoRules;

	//score the numbers
	int numsListSize = nums.size();
	int score = 0;
	for (int numIndex = 0; numIndex < numsListSize; numIndex++)
	{
		//get rule set
		set<int> ruleSet;
		int currentScore = 0;
		int currentNum = nums[numIndex];

		//if there are rules
		if (rules.find(currentNum) != rules.end())
		{
			ruleSet = rules.at(currentNum);

			//check whether the other numbers are inside current number's rule set
			for (const int& otherNum : nums)
			{
				if (otherNum == currentNum)
				{
					continue;
				}

				if (ruleSet.find(otherNum) != ruleSet.end())
				{
					currentScore++;
				}
				else {
				}
			}

			//insert score into table
			orderScore[currentScore].insert(currentNum);
		}
		else {
			//insert score into table
			orderScore[0].insert(currentNum);
		}
	}

	//combine all orders together
	vector<int> correctOrder;

	for (const auto& [score, pageNumbers] : orderScore)
	{
		for (const int& pageNum : pageNumbers)
		{
			correctOrder.push_back(pageNum);
		}
	}

	//higher number = more likely it is first
	reverse(correctOrder.begin(), correctOrder.end());

	//check if they are in the same order as it started in
	bool isCorrect = true;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] != correctOrder[i]) {
			isCorrect = false;
			break;
		}
	}

	if (isCorrect)
	{
		return vector<int>();
	}

	return correctOrder;
}