#pragma once
void menuSeparator() {
	std::cout << "==================" << std::endl;
	std::cout << std::endl;
}
void failedInput() {
	std::cout << "Input was not valid, please re-enter:" << std::endl;
}
bool logoutOrExitCheck(const std::string input, bool& exit,bool& logout) {
	if (input == "exit" || input == "Exit") {
		exit = true;
		return true;
	}
	if (input == "logout" && input == "Logout") {
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