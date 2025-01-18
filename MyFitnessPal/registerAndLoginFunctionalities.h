#pragma once
#include "constants.h"
#include "player.h"
void newProfileFile(const std::string name, const std::string password, unsigned* userDataUnsigned[], bool* userDataBool[], double* userDataDouble[]) {
	std::string str;
	std::string filename = name + txt;
	std::ofstream userFile(filename);
	userFile << password << ':';
	for (int iter = 0; iter < NUM_UNSIGNED_INFO;iter++) {
		userFile << *userDataUnsigned[iter] << DELIMITER;
	}
	for (int iter = 0; iter < NUM_BOOL_INFO;iter++) {
		userFile << *userDataBool[iter] << DELIMITER;
	}
	for (int iter = 0; iter < NUM_DOUBLE_INFO;iter++) {
		userFile << *userDataDouble[iter] << DELIMITER;
	}
	userFile << std::endl;
	userFile.close();
	std::fstream file(allProfiles);
	if (!file.is_open()) allProfilesFileCreation();
	std::getline(file, str, '\n');
	str = str + DELIMITER + name; //adds the user to the allProfiles.txt
	file >> str;
	file.close();
};
bool newProfileName(bool& exit, std::string& profile) {
	std::string str;
	std::ifstream File(allProfiles);
	if (!File.is_open()) {
		allProfilesFileCreation();
		std::ifstream File(allProfiles); //to be improved, not closed in allProfilesFileCreation()
	}
redo:
	while (!File.eof()) {
		std::getline(File, str, DELIMITER);
		if (str == profile) {
			std::cout << "Username already exists, please choose another one:" << std::endl;
			std::cin >> profile;
			File.clear();
			File.seekg(0, std::ios::beg);
			if (exitCheck(profile, exit)) return false;
			goto redo;
		}
	}
	File.close();
}
void mOrf(const std::string str, bool* a, bool& fail) {
	if (str == "male" || str == "Male") {
		*a = false;
		return;
	}
	if (str == "female" || str == "Female") {
		*a = true;
		return;
	}
	fail = true;
}
std::string genderOutput(const bool a) {
	if (a) return "Female";
	else return "Male";
}
void speedToWeight(const std::string input, unsigned* speed, bool& fail) {
	if (input == "0.25" || input == "0.25 kg") {
		*speed = SLOW_SPEEDTOWEIGHT;
		return;
	}
	if (input == "0.5" || input == "0.5 kg") {
		*speed = MEDIUM_SPEEDTOWEIGHT;
		return;
	}
	if (input == "0.75" || input == "0.75 kg") {
		*speed = HIGH_SPEEDTOWEIGHT;
		return;
	}
	if (input == "1" || input == "1 kg") {
		*speed = VERY_HIGH_SPEEDTOWEIGHT;
		return;
	}
	fail = true;
}
std::string speedToWeightOutput(const unsigned speedToWeight) {
	if (speedToWeight == SLOW_SPEEDTOWEIGHT) return "0.25 kg a week";
	if (speedToWeight == MEDIUM_SPEEDTOWEIGHT) return "0.5 kg a week";
	if (speedToWeight == HIGH_SPEEDTOWEIGHT) return "0.75 kg a week";
	if (speedToWeight == VERY_HIGH_SPEEDTOWEIGHT) return "1 kg a week";
	if (speedToWeight == 0) return "0 kg a week";
	return "";
}
void activityInput(const std::string str, double* activityLevel, bool& fail) {
	if (str == "very low" || str == "Very low") {
		*activityLevel = VERY_LOW_ACTIVITY;
		return;
	}
	if (str == "low" || str == "Low") {
		*activityLevel = LOW_ACTIVITY;
		return;
	}
	if (str == "medium" || str == "Medium") {
		*activityLevel = MEDIUM_ACTIVITY;
		return;
	}
	if (str == "high" && str == "High") {
		*activityLevel = HIGH_ACTIVITY;
		return;
	}
	if (str == "very high" || str == "Very high") {
		*activityLevel = VERY_HIGH_ACTIVITY;
		return;
	}
	fail = true;

}
std::string activityLevelOutput(const unsigned activityLevel) {
	if (activityLevel == VERY_LOW_ACTIVITY) return "Very low";
	if (activityLevel == LOW_ACTIVITY) return "Low";
	if (activityLevel == MEDIUM_ACTIVITY) return "Medium";
	if (activityLevel == HIGH_ACTIVITY) return "High";
	if (activityLevel == VERY_HIGH_ACTIVITY) return "Very high";
	return "";
}
void goalInput(const std::string str, unsigned* goal, bool& fail) {
	if (str == "lose weight" || str == "Lose weight") {
		*goal = LOSE_WEIGHT;
		return;
	}
	if (str == "keep weight" || str ==  "Keep weight") {
		*goal = KEEP_WEIGHT;
		return;
	}
	if (str == "gain weight" || str == "Gain weight") {
		*goal = GAIN_WEIGHT;
		return;
	}
	fail = true;
	return;
}
std::string goalOutput(const unsigned goal) {
	if (goal == LOSE_WEIGHT) {
		return "lose weight";
	}
	if (goal == KEEP_WEIGHT) {
		return "keep weight";
	}
	if (goal == GAIN_WEIGHT) {
		return "gain weight";
	}
	return "";
}
void wantsPremium(const std::string str, bool* isPremium, bool& fail) {
	if (str == "yes" || str == "Yes") {
		*isPremium = 1;
		return;
	}
	if (str == "no" || str == "No") {
		*isPremium = 0;
		return;
	}
	fail = true;

}
std::string isPremiumOutput(const bool isPremium) {
	if (isPremium) return "Yes";
	return "No";
}
void nameInput(bool& exit, std::string& input)
{
	std::cout << "Please enter a name to use when logging in:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, input);
	newProfileName(exit, input);
}
void passwordInput(std::string& input, std::string& password)
{
	std::cout << "Enter a password you would like to use:" << std::endl;
	std::getline(std::cin, input);
	password = input;
}
void ageInputMain(std::string& input, bool& fail, bool& exit, unsigned int* age, unsigned int& iter)
{
	std::cout << "Next we need to know your age:" << std::endl;
ageLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	if (failIntegerInput(input, fail)) goto ageLabel;
	*age = stringToInt(input, fail);
	iter++;
}
void goalInputMain(std::string& input, unsigned* goal, unsigned& iter, bool& fail, bool& exit)
{
	do {
		std::cout << "What is your goal?(lose weight, keep weight, gain weight)" << std::endl;
		std::getline(std::cin, input);
		goalInput(input, goal, fail);
		if (exitCheck(input, exit)) return;
	} 
	while (failedInput(fail));
	iter++;
}
void speedToWeightInput(unsigned int* speedOfWeight, unsigned int& iter, std::string& input, bool& fail, bool& exit)
{
	do {
		fail = false;
		std::cout << "How fast would you like to lose/gain weight in a week?(0.25 kg, 0.5 kg, 0.75 kg or 1 kg)" << std::endl;
		std::getline(std::cin, input);
		speedToWeight(input, speedOfWeight, fail);
		if (exitCheck(input, exit)) return;
	} 
	while (failedInput(fail));
	iter++;
}
void activityLevelInput(std::string& input, bool& exit, double* activityLevel, unsigned int& iter, bool& fail)
{
	std::cout << "We need to know your activity level";
	std::cout << " (choose between Very low(sitting work, no workout), Low(training 1-3 times a week), Medium(3-5 times a week), High(6-7 times a week), Very High(Physical work, heavy workouts))" << std::endl;
activityLevelLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	activityInput(input, activityLevel, fail);
	if (failedInput(fail)) goto activityLevelLabel;
	iter = 0;
}
void genderInput(std::string& input, bool& exit, bool* gender, unsigned int& iter, bool& fail)
{
	std::cout << "Please enter your gender(Male or Female):" << std::endl;
genderLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	mOrf(input, gender, fail);
	iter++;
	if (failedInput(fail)) goto genderLabel;
}
void premiumInput(std::string& input, bool& exit, bool* isPremium, unsigned int iter, bool& fail)
{
	std::cout << "Lastly, do you want to subscribe to Premium?(Yes or No)" << std::endl;
wantsPremiumLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	wantsPremium(input, isPremium, fail);
	if (failedInput(fail)) goto wantsPremiumLabel;
}
void weightInput(std::string& input, bool& exit, double* weight, unsigned int& iter, bool& fail)
{
	std::cout << "Please enter your weight(in kilograms):" << std::endl;
weightLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	*weight = stringToDouble(input, fail);
	if (failedInput(fail)) goto weightLabel;
	iter++;
}
void heightInput(std::string& input, bool& exit, unsigned* height, unsigned int& iter, bool& fail)
{
	do {
		std::cout << "Enter your height(in centimeters) below:" << std::endl;
		std::getline(std::cin, input);
		if (exitCheck(input, exit)) return;
		if (!isStringDouble(input)) fail = true;
	} 
	while (failedInput(fail));
	*height = std::stod(input);
	iter = 0;
	return;
}
bool loadInfo(bool& fail, std::string name, std::string password, unsigned* userDataUnsigned[], bool* userDataBool[], double* userDataDouble[]) {

	std::string str;
	std::string filename = name + txt;
	std::ifstream File(filename);
	bool check = false;
	File >> check;
	if (!check) return false;
	File >> password;
	std::cin.ignore();
	for (int iter = 0;iter < NUM_UNSIGNED_INFO; iter++) {
		std::getline(File, str, DELIMITER);
		*userDataUnsigned[iter] = stringToInt(str, fail);
	}
	for (int iter = 0;iter < NUM_BOOL_INFO;iter++) {
		*userDataBool[iter] = stringToInt(str, fail);
	}
	for (int iter = 0;iter < NUM_DOUBLE_INFO;iter++) {
		*userDataDouble[iter] = stringToDouble(str, fail);
	}
	File.close();
	return true;
}
