#pragma once
void doesProfileExistReg(std::string& name, bool& exit, bool& logout) { //the idea between those 2 separate functions is so files are not opened multiple times
	std::ifstream allProfilesFile(allProfiles);
	if (!allProfilesFile.is_open()) {
		std::ofstream allProfilesFile(allProfiles);
		allProfilesFile.close();
		return;
	}
	std::string read;
	while (std::getline(allProfilesFile, read, DELIMITER)) {
		if (read == name) {
			menuSeparator();
			std::cout << "Username is taken please choose another one:" << std::endl;
			std::getline(std::cin, name);
			if (logoutOrExitCheck(name, exit, logout)) return;
			allProfilesFile.clear(); 
			allProfilesFile.seekg(0, std::ios::beg);
		}
	}
	allProfilesFile.close();
	return;
}
void doesProfileExistLogin(std::string name, bool& exit, bool& logout) {
	std::string read;
	std::ifstream allProfilesFile(allProfiles);
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
void newUserFileCreation(const std::string name, const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[]) {
	std::ofstream newFile(name + TXT);
	newFile << password << DELIMITER;
	for (int iter = 0;iter < numOfUnsignedData; iter++) {
		newFile << *unsignedDataArray[iter] << DELIMITER;
	}
	for (int iter = 0;iter < numOfDoubleData; iter++) {
		newFile << *doubleDataArray[iter] << DELIMITER;
	}
	for (int iter = 0;iter < numOfBoolData; iter++) {
		newFile << *boolDataArray[iter] << DELIMITER;
	}
	newFile.close();
	std::string copy;
	std::ifstream allProfilesFile(allProfiles);
	std::getline(allProfilesFile, copy);
	copy = copy + name + DELIMITER;
	allProfilesFile.close();
	std::ofstream allProfilesFileWrite(allProfiles);
	allProfilesFileWrite << copy;
	allProfilesFileWrite.close();
}
void loadData(const std::string name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[]) {
	std::string copy;
	std::ifstream userFile(name + TXT);
	std::getline(userFile, copy, DELIMITER);
	password = copy;
	for (int iter = 0;iter < numOfUnsignedData;iter++) {
		std::getline(userFile, copy, DELIMITER);
		*unsignedDataArray[iter] = std::stoi(copy);
	}
	for (int iter = 0;iter < numOfDoubleData;iter++) {
		std::getline(userFile, copy, DELIMITER);
		*doubleDataArray[iter] = std::stod(copy);
	}
	for (int iter = 0;iter < numOfBoolData;iter++) {
		std::getline(userFile, copy, DELIMITER);
		*boolDataArray[iter] = std::stoi(copy);
	}
	userFile.close();
}