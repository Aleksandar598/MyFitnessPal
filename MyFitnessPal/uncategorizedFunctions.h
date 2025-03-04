#pragma once
/*
Soltuion to course project #9
Introduction to proramming course
Faculty of Matematics and Informatics of Sofia University
Winter semester 2024/2025

@ Aleksandar Angelov
@ GCC
File has uncategorized functions
*/
void menuSeparator() {
	std::cout << "==================" << std::endl;
}
void failedInput() {
	std::cout << "Input was not valid, please re-enter:" << std::endl;
}
bool logoutOrExitCheck(const std::string input, bool& exit,bool& logout) {
	if (input == "exit" || input == "Exit") {
		exit = true;
		return true;
	}
	if (input == "logout" || input == "Logout") {
		logout = true;
		return true;
	}
	return false;
}
void yesOrNo(std::string input,bool& fail, bool& nameIsGood) {
	if (input == "Yes" || input == "yes") {
		nameIsGood = false;
		return;
	}
	if (input == "No" || input == "no") {
		nameIsGood = true;
		return;
	}
	failedInput();
	fail = true;
}
bool isUnsigned(const std::string str) {
	size_t iter = 0;
	while (str[iter]) {
		if (str[iter] > '9' || str[iter] < '0') {
			failedInput();
			return false;
		}
		iter++;
	}
	return true;
}
bool isDouble(const std::string str) {
	size_t iter = 0;
	bool dotFound = false;
	while (str[iter]) {
		if (str[iter] > '9' || str[iter] < '0') {
			if (str[iter] == '.' && !dotFound) {
				dotFound = true;
			}
			else return false;
		}
		iter++;
	}
	return true;
}
std::string currentDate() {
	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);
	char dateString[DATE_SIZE];
	std::strftime(dateString, sizeof(dateString), "%Y-%m-%d", &localTime);
	std::string dateStr(dateString);
	return dateStr;
}
size_t strLen(const std::string string) {
	size_t counter = 0;
	while (string[counter]) {
		counter++;
	}
	return counter;
}
bool checkForDatestring(const std::string string) {
	if (strLen(string) != (DATE_SIZE - 1)) return false;
	for (int iter = 0;iter < DATE_SIZE - 1;iter++) {
		if (iter == 4 || iter == 7) {
			if (string[iter] != '-') {
				return false;
			}
			else continue;
		}
		if (string[iter] < '0' || string[iter]>'9') return false;
	}
	return true;
}
void removeFirstCharacterFromString(std::string& string) {
	size_t iter = 0;
	while (string[iter]) {
		string[iter] = string[iter + 1];
		iter++;
	}
	string[iter] = '\0';
}
void vectorDataPrint(std::vector<std::string> dailyInfo) {
	size_t counter = 1;
	std::cout << "Workouts and meals for the day:" << std::endl;
	for (size_t iter = 0;iter < dailyInfo.size();iter++) {
		std::cout << counter << ". " << dailyInfo[iter] << "   Calories:  " << dailyInfo[iter + 1] << std::endl;
		counter++;
		iter++;
	}
}
void howToUse(bool& exit,bool& logout ) {
	menuSeparator();
	std::string input;
	std::cout << "Basic commands:" << std::endl;
	std::cout << "exit - ends the program and logs out the user if logged in" << std::endl;
	std::cout << "logout - logs out the user and returns him to the starting menu" << std::endl;
	std::cout << "These are the only two commands that you can always type to activate" << std::endl;
	std::cout << "Enjoy using MyFitnessPal! Press anything to return" << std::endl;
	std::getline(std::cin, input);
	logoutOrExitCheck(input, exit, logout);
}
bool doesStrinConatinDots(std::string str) {
	int i = 0;
	while (str[i]) {
		if (str[i] == ':') {
			std::cout << "Input cannot contain ':'" << std::endl;
			return true;
		}
	}
	return false;
}