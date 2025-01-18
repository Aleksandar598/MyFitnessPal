#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include "player.h"
#include "constants.h"

std::string currentDate() {
	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);
	char dateString[DATE_SIZE];
	std::strftime(dateString, sizeof(dateString), "%Y-%m-%d", &localTime);
	std::string dateStr(dateString);
	return dateStr;
}
std::string inputDate(bool& exit) {
	std::string input;
reInputDate:
	int iter = 0;
	std::cout << "Please enter date:(yyyy-mm-dd)" << std::endl;
	std::cin >> input;
	if (exitCheck(input, exit)) return 0;
	while (input[iter]) {
		if (input[iter] < '0' || input[iter]> '9') {
			if (input[iter] != '-') {
				std::cerr << "date is not the right format, please input again!";
				goto reInputDate;
			}
		}
	}
	return input;
}
bool cinFailCheck() {
	if (std::cin.fail()) {
		std::cerr << "Input was not valid, try again:" << std::endl;
		std::cin.clear();
		return true;
	}
	return false;
}
void dateFileEditing(const std::string name, double dailyCalories) {
	std::string filename = DATENAME + name + txt;
	std::fstream File(filename);
	if (!File.is_open()) {
		std::ofstream file(filename);
		file << currentDate() << DELIMITER << dailyCalories;
	}
}
char stringToChar(const std::string string, bool& fail) {
	if (strLen(string) > 2 || strLen(string) == 1) {
		fail = true;
		return 0;
	}
	return string[0];
}
void allProfilesFileCreation() {
	std::ifstream File(allProfiles);
	if (File.is_open()) {
		File.close();
		return;
	}
	else {
		std::ofstream File(allProfiles);
		File.close();
	}
}
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
	std::ifstream file(allProfiles);
	if (!file.is_open()) allProfilesFileCreation();
	std::getline(file, str, '\n');
	file.close();
	str = str + DELIMITER + name; //adds the user to the allProfiles.txt
	std::ofstream WriteAllProfiles(allProfiles);
	WriteAllProfiles << str;
	WriteAllProfiles.close();
}
bool newProfileName(bool& exit, std::string& profile) {
	std::string str;
	std::ifstream File(allProfiles);
	if (!File.is_open()) {
		allProfilesFileCreation();
		std::ifstream File(allProfiles); //to be improved, not closed in allProfilesFileCreation()
	}
redo:
	while (std::getline(File, str, DELIMITER)) {
		if (str == profile) {
			std::cout << "Username already exists, please choose another one:" << std::endl;
			std::getline(std::cin, profile);
			File.clear();
			File.seekg(0, std::ios::beg);
			if (exitCheck(profile, exit)) return false;
			goto redo;
		}
	}
	File.close();
}
void searchProfileName(bool& exit, std::string& profile) {
	std::string str;
	std::ifstream File(allProfiles);
	if (!File.is_open()) {
		allProfilesFileCreation();
		std::ifstream File(allProfiles);
	}
redo:
	while (std::getline(File, str, DELIMITER)) {
		if (str == profile) {

			std::cout << "Profile found, loading info..." << std::endl;
			File.close();
			return;
		}
	}
	std::cout << "Profile not found,please re-enter username:" << std::endl;
	std::cin >> profile;
	File.clear();
	File.seekg(0, std::ios::beg);
	if (exitCheck(profile, exit)) return;
	goto redo;
	File.close();
}
bool failCheck(bool fail) {
	if (fail) {
		std::cerr << "There was an error in the program execution";
		return true;
	}
	return false;
}
bool failedInput(bool& fail) {
	if (fail) {
		std::cerr << "Please enter a valid input" << std::endl;
		fail = false;
		return true;
	}
	return false;
}
bool failIntegerInput(const std::string string, bool& fail) {
	size_t iter = 0;
	while (string[iter]) {
		if (string[iter] < '0' || string[iter]>'9') {
			fail = true;
			failedInput(fail);
			return true;
		}
		iter++;
	}
	return false;
}

bool exitCheck(const std::string toCheck, bool& exit) { //check if the user wished to exit the program
	if (toCheck == "exit") {
		exit = true;
		return true;
	}
	return false;
}
bool logoutCheck(const std::string toCheck, bool& logout) {
	if (toCheck == "logout" || toCheck == "Logout") {
		std::cout << "Successfully logged out!" << std::endl;
		return true;
	}
	return false;
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
	return;
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
	if (str == "keep weight" || str == "Keep weight") {
		*goal = KEEP_WEIGHT;
		return;
	}
	if (str == "gain weight" || str == "Gain weight") {
		*goal = GAIN_WEIGHT;
		return;
	}
	fail = true;
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
bool workoutOrMeal(const std::string input, bool& fail) {
	if (input == "workout" || input == "Workout") return true;
	if (input == "meal" || input == "Meal") return false;
	fail = true;
	return false;
}
int charToInt(const char a) { //validation already made in stringToUnsigned
	return a - '0';
}
size_t strLen(std::string string) {
	size_t counter =0 ;
	while (string[counter]) {
		counter++;
	}
	return counter - 1;
}
bool multipleDotsCheck(std::string string) {
	size_t iter = 0;
	int dotcount = 0;
	while (string[iter]) {
		if (string[iter] == '.') dotcount++;
		if (dotcount > 1) return true;
		iter++;
	}
	return false;
}
int stringToInt(const std::string string, bool& fail) {
	size_t number = 0;
	size_t iter = 0;
	while (string[iter]) {
		if (string[iter] < '0' || string[iter]>'9') {
			fail = true;
			return 0;
		}
		number = number * 10 + charToInt(string[iter]);
		iter++;
	}
	return number;
}
void startingScreen(bool& fail, bool& exit, unsigned& nextAction) {
	std::string input;
	std::cout << "Welcome to MyFitnessPal!" << std::endl;
	do {
		std::cout << "Would you like to login or register(You can also always type exit to exit the program)" << std::endl;
		std::getline(std::cin, input);
		if (exitCheck(input, exit)) return;
		if (input == "register" || input == "Register") {
			nextAction = 0;
			return;
		}
		if (input == "login" || input == "Login") {
			nextAction = 1;
			return;
		}
		fail = true;
	} while (failedInput(fail));
}
double BMR(double bmr, const bool gender, const double weight, const unsigned height, const unsigned age) {
	if (!gender)
		bmr = MALE_BMR_COEF + MALE_WEIGHT_COEF * weight + MALE_HEIGHT_COEF * height - MALE_AGE_COEF * age;
	else {
		bmr = FEMALE_BMR_COEF + FEMALE_WEIGHT_COEF * weight + FEMALE_HEIGHT_COEF * height - FEMALE_AGE_COEF * age;
	}
	return bmr;
}
void dailyNeededCalories(int& dailyCal, double bmr, const bool gender, const double weight, const unsigned height, const double activityLevel, const unsigned age) {
	dailyCal = BMR(bmr, gender, weight, height, age) * activityLevel;

}
bool loadInfo(bool& fail, std::string& name, std::string& password, unsigned* userDataUnsigned[], bool* userDataBool[], double* userDataDouble[]) {

	std::string str;
	std::string filename = name + txt;
	std::ifstream File(filename);
	if (!File.is_open()) return false;
	std::getline(File, password, DELIMITER);
	for (int iter = 0;iter < NUM_UNSIGNED_INFO; iter++) {
		std::getline(File, str, DELIMITER);
		*userDataUnsigned[iter] = stringToInt(str, fail);
	}
	for (int iter = 0;iter < NUM_BOOL_INFO;iter++) {
		*userDataBool[iter] = stringToInt(str, fail);
	}
	for (int iter = 0;iter < NUM_DOUBLE_INFO;iter++) {
		*userDataDouble[iter] = std::stod(str);
	}
	File.close();
	return true;
}
void nameInput(std::string& name, bool& exit, std::string& input)
{
		std::cout << "Please enter a name to use when logging in:" << std::endl;
		std::getline(std::cin, input);
		newProfileName(exit, input);
		name = input;
}
void passwordInput(std::string& input, std::string& password)
{
	std::cout << "Enter a password you would like to use:" << std::endl;
	std::getline(std::cin, input);
	password = input;
}
void ageInputMain(std::string& input, bool& fail, bool& exit, unsigned int* age, unsigned int& iter)
{
	do {
		std::cout << "Next we need to know your age:" << std::endl;
		std::getline(std::cin, input);
		if (exitCheck(input, exit)) return;
	} 
	while (failIntegerInput(input, fail));
	*age = stringToInt(input, fail);
	iter++;
	return;
}
void goalInputMain(std::string& input, unsigned* goal, unsigned& iter, bool& fail, bool& exit)
{
	std::cout << "What is your goal?(lose weight, keep weight, gain weight)" << std::endl;
goalLabel:
	std::getline(std::cin, input);
	goalInput(input, goal, fail);
	if (exitCheck(input, exit)) return;
	if (failedInput(fail)) goto goalLabel;
	iter++;
}
void speedToWeightInput(unsigned int* speedOfWeight, unsigned int& iter, std::string& input, bool& fail, bool& exit)
{
	do{
	std::cout << "How fast would you like to lose/gain weight in a week?(0.25kg,0.5 kg. 0.75 kg or 1 kg)" << std::endl;
	
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
void reg(bool& fail, bool& exit, std::string& name, std::string& password, unsigned* userDataUnsigned[], bool* userDataBool[], double* userDataDouble[]) {
	std::string input;
	unsigned iter = 0;
	std::cout << "Welcome to the Registration Menu!" << std::endl;
	nameInput(name, exit, input);
	if (exit) return;
	passwordInput(input, password);
	if (exitCheck(input, exit)) return;
	ageInputMain(input, fail, exit, userDataUnsigned[iter], iter);
	if (exit) return;
	goalInputMain(input, userDataUnsigned[iter], iter, fail, exit);
	if (exit) return;
	if (*userDataUnsigned[iter - 1] != 2) {
		speedToWeightInput(userDataUnsigned[iter], iter, input, fail, exit);
	}
	else userDataUnsigned[iter] = 0;
	if (exit) return;
	heightInput(input, exit, userDataUnsigned[iter], iter, fail);
	if (exit) return;
	weightInput(input, exit, userDataDouble[iter], iter, fail);
	if (exit) return;
	activityLevelInput(input, exit, userDataDouble[iter], iter, fail);
	if (exit) return;
	genderInput(input, exit, userDataBool[iter], iter, fail);
	if (exit) return;
	premiumInput(input, exit, userDataBool[iter], iter, fail);
	if (exit) return;
	newProfileFile(name, password, userDataUnsigned, userDataBool, userDataDouble);
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
size_t stringLength(const std::string string) {
	size_t counter = 0;
	while (string[counter]) {
		counter++;
	}
	return counter;
}
bool isStringDouble(const std::string string) {
	if (stringLength(string) == 0) return false;
	if (stringLength(string) == 1 && string[0] == '.') return false;
	int iter = 0;
	bool dotCheck = false;
	while (string[iter]) {
		if (string[iter] > '9' || string[iter] < '0') {
			if (string[iter] == '.' && !dotCheck) {
				dotCheck = true;
			}
			else return false;
		}
		iter++;
	}
	return true;
}
void weightInput(std::string& input, bool& exit, double* weight, unsigned int& iter, bool& fail)
{
	do {
		std::cout << "Please enter your weight(in kilograms):" << std::endl;
		std::getline(std::cin, input);
		if (exitCheck(input, exit)) return;
		if (!isStringDouble(input)) fail = true;
	} 
	while (failedInput(fail));
	*weight = std::stod(input);
	iter++;
}
void heightInput(std::string& input, bool& exit, unsigned* height, unsigned int& iter, bool& fail)
{
	do {
		std::cout << "Enter your height(in centimeters) below:" << std::endl;
		std::getline(std::cin, input);
		if (exitCheck(input, exit)) return;
	} while ((failedInput(fail)));
	*height = std::stoi(input);
	iter = 0;
}
bool login(bool& fail, bool& exit, std::string& name, std::string& password, unsigned* userDataUnsigned[], bool* userDataBool[], double* userDataDouble[]) {
	std::string input;
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> name;
	if (exitCheck(name, exit)) return false;
	searchProfileName(exit, name);
	if (exitCheck(name, exit)) return false;
	loadInfo(fail, name, password, userDataUnsigned, userDataBool, userDataDouble);
	do {
		std::cout << "Please enter your password:" << std::endl;
		std::cin >> input;
		std::cin.ignore();
		if (exitCheck(input, exit)) return false;
	} while (password != input);
	std::cout << "Successfully loaded info! Hello " << name << "!" << std::endl;

}
void addAMealToFile(const std::string name, std::string meal, int calories) {
	std::string filename = DATENAME + name + txt;
	std::string copy;
	std::ifstream File(filename);
	bool found = false;
	std::string dateToday = currentDate();
	while (!File.eof()) {
		std::getline(File, copy, DELIMITER);
		if (copy == dateToday) {
			found = true;
			break;
		}
	}
	File.clear();
	File.seekg(0, std::ios::beg);
	std::getline(File, copy);
	if (found) {
		copy = copy + DELIMITER + meal + DELIMITER + std::to_string(calories);
	}
	else copy = copy + DELIMITER + dateToday + DELIMITER + meal + DELIMITER + std::to_string(calories);
	File.close();
	std::ofstream newFile(filename);
	newFile << copy;
	newFile.close();
}
void addADailyMeal(const std::string name, int& dailyCalories) {
	std::string input;
	int calories;
	std::cout << "Enter a name for the meal:" << std::endl;
	std::cin >> input;
	std::cout << "Enter calories:" << std::endl;
calorieLabel:
	std::cin >> calories;
	input = mealDifferenciator + input;
	if (cinFailCheck()) goto calorieLabel;
	dailyCalories = dailyCalories + calories;
	addAMealToFile(name, input, calories);
}
void addADailyWorkout(const std::string name, int& dailyCalories) {
	std::string input;
	int calories;
	std::cout << "Enter a name for the workout:" << std::endl;
	std::cin >> input;
	std::cout << "Enter calories burned:" << std::endl;
calorieLabel:
	std::cin >> calories;
	input = workoutDifferenciator + input;
	if (cinFailCheck()) goto calorieLabel;
	dailyCalories = dailyCalories - calories;
	addAMealToFile(name, input, calories);
}
std::string moveStrByOne(const std::string string) {
	std::string newStr;
	size_t iter = 1;
	while (string[iter]) {
		newStr[iter - 1] = string[iter];
	}
	return newStr;
}
void currentDateData(const std::string name) {
	std::string filename = DATENAME + name + txt;
	std::string getInfo;
	size_t iter = 0;
	std::string date = currentDate();
	std::vector<std::string> data;
	std::ifstream File(filename);
	if (!File.is_open()) {
		std::cout << "No recorded data exists" << std::endl;
		return;
	}
	while (std::getline(File, getInfo, DELIMITER)) {
		if (getInfo == date) break;
	}
	while (std::getline(File, getInfo, DELIMITER)) {
		data[iter] = moveStrByOne(getInfo);
		iter++;
		std::getline(File, getInfo, DELIMITER);
		data[iter] = getInfo;
		iter++;
	}
	File.close();
	DisplayDataFromVector(data, iter);
}
void specificDateData(const std::string name, bool& exit) {
	std::string filename = DATENAME + name + txt;
	std::string getInfo;
	size_t iter = 0;
	std::string date = inputDate(exit);
	std::vector<std::string> data;
	std::ifstream File(filename);
	if (!File.is_open()) {
		std::cout << "No recorded data exists" << std::endl;
		return;
	}
	while (std::getline(File, getInfo, DELIMITER)) {
		if (getInfo == date) break;
	}
	while (std::getline(File, getInfo, DELIMITER)) {
		std::getline(File, getInfo, DELIMITER);
		data[iter] = getInfo;
		iter++;
	}
	File.close();
	DisplayDataFromVector(data, iter);
}
void DisplayDataFromVector(const std::vector<std::string> data, const size_t size) {
	for (size_t iter = 1;iter < size;iter + 2) {
		std::cout << iter << '. ' << data[iter - 1] << "  " << data[iter] << std::endl;
	}
}
bool checkForDatestring(const std::string string) {
	int iter = 0;
	while (string[iter]) {
		if (string[iter] > '9' || string[iter] < '0' || iter>10) {      //10 is the size of a datestring(yyyy-mm-dd)
			return false;
		}
	}
	return true;
}

void deleteDataForADate(const std::string name, bool& exit) {
	std::string date;
	std::string input;
	std::string saveString = "";
	std::string filename = DATENAME + name + txt;
	std::cout << "Choose a day for which the data will be deleted" << std::endl;
	date = inputDate(exit);
	if (exit) return;
	std::ifstream File(filename);
	if (!File.is_open()) {
		std::cout << "No data found!" << std::endl;
		return;
	}
	while (std::getline(File, input, DELIMITER)) {
		if (input != date) {
			saveString = saveString + input + DELIMITER;
		}
		else break;
	}
	while (std::getline(File, input, DELIMITER)) {
		std::getline(File, input, DELIMITER);
		if (checkForDatestring(input)) {
			saveString = saveString + input + DELIMITER;
		}
	}
	std::getline(File, input);
	saveString = saveString + input;
	File.close();
	std::ofstream file(filename);
	file << saveString;
	file.close();
}
void changeDataForToday(const std::string name, bool& exit, bool& fail) {
	std::string filename = DATENAME + name + txt;
	std::string input;
	int calories = 0;
	size_t iter = 0;
	size_t change;
	std::vector<std::string> data;
	std::string saveString = "";
	std::string date = currentDate();
	std::ifstream File(filename);
	if (!File.is_open()) {
		std::cout << "No saved data exists" << std::endl;
		return;
	}
	while (std::getline(File, input, DELIMITER)) {
		if (input == date) break;
		saveString = saveString + input + DELIMITER;
	}
	if (!std::getline(File, input, DELIMITER)) {
		std::cout << "No data exists for today" << std::endl;
		return;
	}
	while (std::getline(File, input, DELIMITER)) {
		data[iter] = input;
		iter++;
	}
	File.close();
	DisplayDataFromVector(data, iter);
	std::cout << "Which would you like to modify?(Type the number of the meal/workout)" << std::endl;
reInputChange:
	std::cin >> change;
	change = change * 2 - 1; //vector contains both meal/workout and calories, while displaying the as one data, thus if workout is
	if (change > iter || std::cin.fail()) { //num 3 actual place for the name would be 5, and the calories burned will be at 6
		std::cout << "Invalid, please input again:" << std::endl;
		std::cin.clear();
		goto reInputChange;
	}
	std::cin.ignore();
	std::cout << "What would you like to change it to?(workout or meal)" << std::endl;
reInputWOrM:
	std::cin >> input;
	bool wOrM = workoutOrMeal(input, fail);
	if (fail) {
		std::cout << "Please input workout or meal" << std::endl;
		fail = false;
		goto reInputWOrM;
	}
	std::cout << "Please enter name for the workout/meal" << std::endl;
	std::cin >> input;
	if (wOrM) input = workoutDifferenciator + input;
	else input = mealDifferenciator + input;
	data[change] = input;
	change++;
	std::cout << "Enter calories gained/burned:" << std::endl;
reInputCalories:
	std::cin >> calories;
	if (cinFailCheck()) goto reInputCalories;
	data[change] = std::to_string(calories);
	for (int i = 0;i < iter;iter++) {
		saveString = saveString + DELIMITER + data[i];
	}
	std::ifstream file(filename);
	file >> saveString;
	std::cout << "Successfully saved changes" << std::endl;
}
void changePersonalData(unsigned& age, unsigned& goal, unsigned& speedOfWeight, double& weight, unsigned& height, bool& gender, bool& isPremium, bool& logout, bool& exit, bool& fail) {
	std::string input;
	std::string bait = ""; //its purpose is so i dont have to rewrite all of reg and the functions it calls
	unsigned iter = 0; //serves same purpose
	std::cout << "1.Age:" << age << std::endl;
	std::cout << "2.Goal:" << goalOutput(goal) << std::endl;
	std::cout << "3.Speed of gaining/losing weight:" << speedToWeightOutput(speedOfWeight) << std::endl;
	std::cout << "4.Weight:" << weight << std::endl;
	std::cout << "5.Height:" << height << std::endl;
	std::cout << "6.Gender:" << genderOutput(gender) << std::endl;
	std::cout << "7.isPremium:" << isPremiumOutput(isPremium) << std::endl;
	std::cout << "Type the number of what you wish to change:" << std::endl;
reInput:
	std::cin >> input;
	if (exitCheck(input, exit) || logoutCheck(input, logout)) return;
	unsigned switchNum = stringToInt(input, fail);
	switch (switchNum) {
	case 1: ageInputMain(bait, fail, exit, &age, iter); break;
	case 2: goalInputMain(bait, &goal, iter, fail, exit); break;
	case 3: speedToWeightInput(&speedOfWeight, iter, bait, fail, exit);
	case 4: weightInput(bait, exit, &weight, iter, fail); break;
	case 5: heightInput(bait, exit, &height, iter, fail);break;
	case 6: genderInput(bait, exit, &gender, iter, fail); break;
	case 7: premiumInput(bait, exit, &isPremium, iter, fail); break;
	default: {
		std::cout << "Please enter a valid number:" << std::endl;
		goto reInput;
	}
	}
}
bool generalScreenNextAction(bool& fail, bool& exit, bool& logout, const std::string input, const std::string name, unsigned& age, unsigned& goal, unsigned& speedOfWeight, double& activityLevel, double& weight, unsigned& height, bool& gender, bool& isPremium, int& caloriesIntake, int& caloriesUsed, double bmr, int dailyCalories) {
	char number = stringToChar(input, fail);
	if (failedInput(fail)) {
		return true;
	}
	switch (number) {
	case '1': dailyCalorieScreen(name, fail, exit, logout, dailyCalories, goal, speedOfWeight, activityLevel, bmr, isPremium); break;
	case '2': addADailyMeal(name, dailyCalories); break;
	case '3': addADailyWorkout(name, dailyCalories); break;
	case '4': currentDateData(name); break;
	case '5': specificDateData(name, exit); break;
	case '6': deleteDataForADate(name, exit); break;
	case '7': changeDataForToday(name, exit, fail); break;
	case '8': changePersonalData(age, goal, speedOfWeight, weight, height, gender, isPremium, logout, exit, fail); break;
	default: return true;
	}
}
void calculateMacronutriens(const unsigned int goal, int& carbohydrates, const int recommendedCalorieIntake, int& fat, int& protein, int& carbohydratesGrams, int& proteinGrams, int& fatGrams)
{
	if (goal == LOSE_WEIGHT) {
		carbohydrates = recommendedCalorieIntake * LOSE_WEIGHT_CARBOHYDRATES;
		fat = recommendedCalorieIntake * LOSE_WEIGHT_FAT;
		protein = recommendedCalorieIntake * LOSE_WEIGHT_PROTEIN;
	}
	if (goal == KEEP_WEIGHT) {
		carbohydrates = recommendedCalorieIntake * KEEP_WEIGHT_CARBOHYDRATES;
		fat = recommendedCalorieIntake * KEEP_WEIGHT_FAT;
		protein = recommendedCalorieIntake * KEEP_WEIGHT_PROTEIN;
	}
	if (goal == GAIN_WEIGHT) {
		carbohydrates = recommendedCalorieIntake * GAIN_WEIGHT_CARBOHYDRATES;
		fat = recommendedCalorieIntake * GAIN_WEIGHT_FAT;
		protein = recommendedCalorieIntake * GAIN_WEIGHT_PROTEIN;
	}
	carbohydratesGrams = carbohydrates / CARBOHYDRATES_CALORIES_PER_GRAM;
	proteinGrams = carbohydrates / PROTEIN_CALORIES_PER_GRAM;
	fatGrams = carbohydrates / FAT_CALORIES_PER_GRAM;
}
void displayMacronutrients(const int recommendedCalorieIntake, const unsigned goal, bool& exit, bool& logout) {
	int carbohydrates = 0;
	int fat = 0;
	int protein = 0;
	int proteinGrams = 0;
	int fatGrams = 0;
	int carbohydratesGrams = 0;
	calculateMacronutriens(goal, carbohydrates, recommendedCalorieIntake, fat, protein, carbohydratesGrams, proteinGrams, fatGrams);
	std::cout << "Recommended protein intake: " << protein << "calories or " << proteinGrams << " grams" << std::endl;
	std::cout << "Recommended carbohydrates intake: " << carbohydrates << "calories or " << carbohydratesGrams << " grams" << std::endl;
	std::cout << "Recommended fat intake: " << fat << "calories or " << fatGrams << " grams" << std::endl;
	std::cout << "Press enter to return to the general screen:" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	if (exitCheck(input, exit) || logoutCheck(input, logout)) return;
}
void dailyCalorieScreen(const std::string name, bool& fail, bool& exit, bool& logout, int& dailyCalories, const double goal, const double speedOfWeight, const double activityLevel, const int bmr, const double isPremium) {
	int recommendedCalorieIntake = 0;
	std::string input;
	recommendedCalories(recommendedCalorieIntake, speedOfWeight, goal, activityLevel, bmr);
	dailyCaloriesTillNow(name, dailyCalories, fail);
	std::cout << "Recommended calorie intake: " << recommendedCalorieIntake << std::endl;
	std::cout << "Current calorie intake: " << dailyCalories << std::endl;
	if (!isPremium) std::cout << "If you had premium macronutrients would be displayed here" << std::endl;
	if (isPremium) {
		displayMacronutrients(recommendedCalorieIntake, goal, exit, logout);
	}
	std::cout << "Type anything to return to general menu" << std::endl;
	std::getline(std::cin, input);
}
void dailyCaloriesTillNow(const std::string name, int& dailyCalories, bool& fail) {
	std::string filename = DATENAME + name + txt;
	std::string read;
	bool found = false;
	std::string date = currentDate();
	std::ifstream File(filename);
	if (!File.is_open()) return;
	while (std::getline(File, read, DELIMITER)) {
		if (read == date) {
			found = true;
			break;
		}
	}
	while (std::getline(File, read, DELIMITER) && !checkForDatestring(read)) {
		bool mOrW = false;
		if (read[0] = 'w') mOrW = true;
		if (read[0] = 'm') mOrW = false;
		std::getline(File, read, DELIMITER);
		if (mOrW) dailyCalories = dailyCalories - stringToInt(read, fail);
		if (!mOrW) dailyCalories = dailyCalories + stringToInt(read, fail);
	}
	File.close();
}
void recommendedCalories(int& recommendedCalories, const unsigned speedOfWeight, const unsigned goal, const double activityLevel, const int bmr) {
	int deficitOrGain = speedOfWeight*SPEED_TO_WEIGHT_COEF*CALORIES_PER_KILO;
	if (goal == LOSE_WEIGHT) recommendedCalories = bmr - deficitOrGain;
	if (goal == KEEP_WEIGHT) recommendedCalories = bmr;
	if (goal == GAIN_WEIGHT) recommendedCalories = bmr + deficitOrGain;
}
void generalScreen(bool& fail, bool& exit, bool& logout, const std::string name, unsigned& age, unsigned& goal, unsigned& speedOfWeight, double& weight, unsigned& height, double& activityLevel, bool& isPremium, bool& gender, int& caloriesIntake, int& caloriesUsed, int dailyCalories) {
	while (true) {
		std::string input;
		double bmr = 0.0;
		bmr = BMR(bmr, gender, weight, height, age);
		dailyNeededCalories(dailyCalories, bmr, gender, weight, height, activityLevel, age); 
		std::cout << "This is the General Screen!" << std::endl;
		std::cout << "What would you like to do:(enter a number representing your choice)" << std::endl;
		std::cout << "1.See calorie balance for today" << std::endl << "2.Add a meal" << std::endl << "3.Add a workout" << std::endl;
		std::cout << "4.Get your daily stats" << std::endl << "5.Get stats for a specific date" << std::endl;
		std::cout << "6.Delete data for a specific day" << std::endl << "7.Change meals and workouts for today" << std::endl;
		std::cout << "8.Edit personal data" << std::endl << "(You can also logout)" << std::endl;
		std::cin >> input;
		if (exitCheck(input, exit) || logoutCheck(input, logout)) {
			return;
		}
		generalScreenNextAction(fail, exit, logout, input, name, age, goal, speedOfWeight, activityLevel, weight, height, gender, isPremium, caloriesIntake, caloriesUsed, bmr, dailyCalories);
		if (exitCheck(input, exit) || logoutCheck(input, logout)) {
			return;
		}
	}
}
int main()
{
startingScreen:
	bool fail = false;
	bool exit = false;
	bool logout = false;
	unsigned nextAction = 0;
	std::string name = "null";
	std::string password = "null";
	unsigned age = 0;
	double weight = 0.0;
	unsigned height = 0;
	double activityLevel = 0.0;
	unsigned goal = 0;
	unsigned speedOfWeight = 0;
	bool isPremium = 0;
	bool gender = 0;
	double dailyCalories = 0.0;
	int caloriesIntake = 0;
	int caloriesUsed = 0;
	unsigned* userDataUnsigned[NUM_UNSIGNED_INFO] = { &age, &goal,&speedOfWeight, &height };
	bool* userDataBool[NUM_BOOL_INFO] = { &gender, &isPremium };
	double* userDataDouble[NUM_DOUBLE_INFO] = {&weight, &activityLevel };
	startingScreen(fail, exit, nextAction);
	if (failCheck(fail)) return 1;
	if (exit) return 0;
	if (nextAction) login(fail, exit, name, password, userDataUnsigned, userDataBool, userDataDouble);
	else reg(fail, exit, name, password, userDataUnsigned, userDataBool, userDataDouble);
	if (exit) return 0;
	if (failCheck(fail)) return 2;
	generalScreen(fail, exit, logout, name, age, goal, speedOfWeight, weight, height, activityLevel, isPremium, gender, caloriesIntake, caloriesUsed, dailyCalories);
	if (logout) {
		goto startingScreen;
	}
	if (failCheck(fail)) return 3;
	if (exit) return 0;
}