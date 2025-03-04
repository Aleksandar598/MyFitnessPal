#pragma once
/*
Soltuion to course project #9
Introduction to proramming course
Faculty of Matematics and Informatics of Sofia University
Winter semester 2024/2025

@ Aleksandar Angelov
@ GCC
File contains functions that are use files
*/
void doesProfileExistReg(std::string& name, bool& exit, bool& logout) { //the idea between those 2 separate functions is so files are not opened multiple times
	std::ifstream allProfilesFile(ALLPROFILES);
	if (!allProfilesFile.is_open()) {
		std::ofstream allProfilesFile(ALLPROFILES);
		allProfilesFile.close();
		return;
	}
	std::string read;
	while (std::getline(allProfilesFile, read, DELIMITER)) {
		if (read == name) {
			menuSeparator();
			std::cout << "Username is taken please choose another one:" << std::endl;
			std::getline(std::cin, name);
			if (logoutOrExitCheck(name, exit, logout)) {
				allProfilesFile.close();
				return;
			}
			allProfilesFile.clear(); 
			allProfilesFile.seekg(0, std::ios::beg);
		}
	}
	allProfilesFile.close();
	return;
}
void doesProfileExistLogin(std::string name, bool& exit, bool& logout) {
	std::string read;
	std::ifstream allProfilesFile(ALLPROFILES);
	do {
		while (std::getline(allProfilesFile, read, DELIMITER)) {
			if (read == name) {
				return;
			}
		}
		std::cout << "No user found, please enter username again:" << std::endl;
		std::getline(std::cin, name);
		if (logoutOrExitCheck(name, exit, logout)) return;
		allProfilesFile.clear();
		allProfilesFile.seekg(0, std::ios::beg);
	} while (true);
	allProfilesFile.close();
}
void UserDataSave(const std::string name, const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[]) {
	std::ofstream newFile(name + TXT);
	newFile << password << DELIMITER;
	for (int iter = 0;iter < NUM_OF_UNSIGNED_DATA; iter++) {
		newFile << *unsignedDataArray[iter] << DELIMITER;
	}
	for (int iter = 0;iter < NUM_OF_DOUBLE_DATA; iter++) {
		newFile << *doubleDataArray[iter] << DELIMITER;
	}
	for (int iter = 0;iter < NUM_OF_BOOL_DATA; iter++) {
		newFile << *boolDataArray[iter] << DELIMITER;
	}
	newFile.close();
}
void saveNewUserName(const std::string name){
	std::string copy;
	std::ifstream allProfilesFile(ALLPROFILES);
	std::getline(allProfilesFile, copy);
	copy = copy + name + DELIMITER;
	allProfilesFile.close();
	std::ofstream allProfilesFileWrite(ALLPROFILES);
	allProfilesFileWrite << copy;
	allProfilesFileWrite.close();
}
void loadData(const std::string name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[],unsigned& calorieIntake, unsigned& caloriesUsed) {
	bool dateFound = false;
	std::string copy;
	std::string date = currentDate();
	std::ifstream userFile(name + TXT);
	std::getline(userFile, copy, DELIMITER);
	password = copy;
	for (int iter = 0;iter < NUM_OF_UNSIGNED_DATA;iter++) {
		std::getline(userFile, copy, DELIMITER);
		*unsignedDataArray[iter] = std::stoi(copy);
	}
	for (int iter = 0;iter < NUM_OF_DOUBLE_DATA;iter++) {
		std::getline(userFile, copy, DELIMITER);
		*doubleDataArray[iter] = std::stod(copy);
	}
	for (int iter = 0;iter < NUM_OF_BOOL_DATA;iter++) {
		std::getline(userFile, copy, DELIMITER);
		*boolDataArray[iter] = std::stoi(copy);
	}
	userFile.close();
	std::ifstream dateFile(name + DATEFILE + TXT);
	while (std::getline(dateFile, copy, DELIMITER)) {
		if (copy == date) {
			dateFound = true;
			break;
		}
	}
	while (std::getline(dateFile, copy, DELIMITER) && dateFound) {
		if (checkForDatestring(copy)) {
			break;
		}
		if (copy[0] == WORKOUT_DIFFERENTIATOR) {
			std::getline(dateFile, copy, DELIMITER);
			caloriesUsed += std::stoi(copy);
		}
		if (copy[0] == MEAL_DIFFERENTIATOR) {
			std::getline(dateFile, copy, DELIMITER);
			calorieIntake += std::stoi(copy);
		}
	}
	dateFile.close();
}
void loadCaloriesData(std::string name, unsigned& caloriesIntake, unsigned& caloriesUsed) {
	std::string read;
	std::string date = currentDate();
	bool dateFound = false;
	caloriesIntake = 0;
	caloriesUsed = 0;
	std::ifstream dateFile(name + DATEFILE + TXT);
	if (!dateFile.is_open()) {    //First thing done in general screen will open the file, so no furhter checks are needed
		std::ofstream dateFile(name + DATEFILE + TXT);
		dateFile.close();
		return;
	}
	while (std::getline(dateFile, read, DELIMITER)) {
		if (read == date) {
			dateFound = true;
			break;
		}
	}
	while (std::getline(dateFile, read, DELIMITER) && dateFound)
	{
		if (checkForDatestring(read)) {
			break;
		}
		if (read[0] == WORKOUT_DIFFERENTIATOR) {
			std::getline(dateFile, read, DELIMITER);
			caloriesUsed += std::stoi(read);
		}
		if (read[0] == MEAL_DIFFERENTIATOR) {
			std::getline(dateFile, read, DELIMITER);
			caloriesIntake += std::stoi(read);
		}
	}
	dateFile.close();
}
void addMealorWorkoutToFile(const std::string name, const std::string mealorWorkoutName, const unsigned calories) {
	std::string copy;
	std::string read;
	std::string date = currentDate();
	std::ifstream dateFile(name + DATEFILE + TXT);
	std::getline(dateFile, copy);
	dateFile.clear();
	dateFile.seekg(0, std::ios::beg);
	while (std::getline(dateFile, read, DELIMITER)) {
		if (read == date) {
			dateFile.close();
			std::ofstream dateFileWrite(name + DATEFILE + TXT);
			dateFileWrite << copy <<  mealorWorkoutName << DELIMITER << calories << DELIMITER;
			dateFileWrite.close();
			return;
		}
	}
	std::ofstream dateFileWrite(name + DATEFILE + TXT);
	dateFileWrite << copy << date << DELIMITER << mealorWorkoutName << DELIMITER << calories << DELIMITER;
	dateFileWrite.close();
}
std::vector<std::string> loadDataForASpecificDay(const std::string name, const std::string date, bool& dateFound) {
	std::string read;
	dateFound = false;
	std::vector<std::string> dailyInfo;
	std::ifstream dateFile(name + DATEFILE + TXT);
	while(std::getline(dateFile, read,DELIMITER))
	{
		if (read == date) {
			dateFound = true;
			break;
		}
	}
	while (std::getline(dateFile, read, DELIMITER) && dateFound) {
		if (checkForDatestring(read)) {
			break;
		}
		if (read[0] == WORKOUT_DIFFERENTIATOR) {
			removeFirstCharacterFromString(read);
			read = "workout " + read;
			dailyInfo.push_back(read);
		}
		if (read[0] == MEAL_DIFFERENTIATOR) {
			removeFirstCharacterFromString(read);
			read = "meal " + read;
			dailyInfo.push_back(read);
		}
		std::getline(dateFile, read, DELIMITER);
		dailyInfo.push_back(read);
	}
	dateFile.close();
	return dailyInfo;
}
bool deleteDataFromFile(const std::string name, const std::string date) {
	std::string read;
	std::string copy;
	bool dateFound = false;
	std::ifstream dateFile(name + DATEFILE + TXT);
	while (std::getline(dateFile, read, DELIMITER))
	{
		if (read == date) {
			dateFound = true;
			break;
		}
		copy += read + DELIMITER;
	}
	if (!dateFound) {
		dateFile.close();
		return false;
	}
	while (std::getline(dateFile, read, DELIMITER))
	{
		if (checkForDatestring(read)) {
			copy += read + DELIMITER;
			break;
		}
	}
	while (std::getline(dateFile, read, DELIMITER))
	{
		copy += read + DELIMITER;
	}
	dateFile.close();
	std::ofstream dateFileWrite(name + DATEFILE + TXT);
	dateFileWrite << copy;
	dateFileWrite.close();
	return dateFound;
}
void saveModifiedInfoForToday(const std::string name, std::vector<std::string> dailyInfo, const bool deletion) {
	std::ifstream dateFile(name + DATEFILE + TXT);
	std::string copy;
	std::string read;
	std::string date = currentDate();
	while (std::getline(dateFile, read, DELIMITER))
	{
		if (read == date) {
			break;
		}
		copy += read + DELIMITER;
	}
	if (dailyInfo.size() == 0) {
		std::ofstream dateFileWrite(name + DATEFILE + TXT);
		dateFileWrite << copy;
		dateFileWrite.close();
		return;
	}
	if (deletion) {
		std::ofstream dateFileWrite(name + DATEFILE + TXT);
		dateFileWrite << copy;
		for (int i = 0;i < sizeof(dailyInfo);i++) {
			dateFileWrite << dailyInfo[i] + DELIMITER;
		}
		dateFileWrite.close();
		return;
	}
	else copy += read + DELIMITER;
	while (std::getline(dateFile, read, DELIMITER))
	{
		if (checkForDatestring(read)) {
			copy += read + DELIMITER;
			break;
		}
	}
	for (size_t iter = 0;iter < dailyInfo.size();iter++) {
		copy += dailyInfo[iter] + DELIMITER;
		std::getline(dateFile, read, DELIMITER);
	}
	std::getline(dateFile, read);
	copy = copy + read;
	dateFile.close();
	std::ofstream dateFileWrite(name + DATEFILE + TXT);
	dateFileWrite << copy;
	dateFileWrite.close();
}

