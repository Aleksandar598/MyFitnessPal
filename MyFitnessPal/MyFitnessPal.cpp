#include <iostream>
#include <string>
#include <fstream>
#include <ctime>


const double MALE_BMR_COEF = 88.362;
const double MALE_WEIGHT_COEF = 13.397;
const double MALE_HEIGHT_COEF = 4.799;
const double MALE_AGE_COEF = 5.677;
const double FEMALE_BMR_COEF = 447.593;
const double FEMALE_WEIGHT_COEF = 9.247;
const double FEMALE_HEIGHT_COEF = 3.098;
const double FEMALE_AGE_COEF = 4.330;
const double VERY_LOW_ACTIVITY = 1.2; 
const double LOW_ACTIVITY = 1.375;
const double MEDIUM_ACTIVITY = 1.55;
const double HIGH_ACTIVITY = 1.725;
const double VERY_HIGH_ACTIVITY = 1.9;
const size_t MAX_INPUT_SIZE = 1024;
const unsigned NUM_UNSIGNED_INFO = 3;
const unsigned NUM_BOOL_INFO = 2;
const unsigned NUM_DOUBLE_INFO = 3;
const size_t DATE_SIZE = 11;
const std::string DATENAME = "date";
const std::string txt = ".txt";
const std::string allProfiles = "allProfiles.txt";
const char DELIMITER = ':';
char mealDifferenciator = 'm';
char workoutDifferenciator = 'w';

std::string currentDate() {
	std::time_t currentTime = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &currentTime);
	char dateString[DATE_SIZE];
	std::strftime(dateString, sizeof(dateString), "%Y-%m-%d", &localTime);
	std::string dateStr(dateString);
	return dateStr;
}
bool cinFailCheck() {
	if (std::cin.fail()) {
		std::cerr << "Input was not valid, try again:" << std::endl;
		std::cin.clear();
		return true;
	}
	return false;
}
double dailyCaloriesFileReading(const std::string name, double& dailyCalories, bool& fail) {
	std::string read;
	std::string dateToday = currentDate();
	bool found = false;
	std::string filename = DATENAME + name + txt;
	std::ifstream File(filename);
	if (!File.is_open()) {
		std::cout << "No file exists with data" << std::endl;
		dailyCalories = 0;
		return;
	}
	while (!File.eof()) {
		std::getline(File, read, DELIMITER);
		if (read == dateToday) {
			found = true;
			break;
		}
	}
	if (found) {
		std::getline(File, read, DELIMITER);
		return stringToDouble(read, fail);
	}
	return 0;
}
void dateFileEditing(const std::string name, double dailyCalories, ) {
	std::string filename = DATENAME + name + txt;
	std::fstream File(filename);
	if (!File.is_open()) {
		std::ofstream file(filename);
		file << currentDate() << DELIMITER << dailyCalories;
	}


}
char stringToChar(const std::string string, bool& fail) {
	if (strLen(string) > 1|| strLen(string)==0) {
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
	std::fstream file(allProfiles);
	if (!file.is_open()) allProfilesFileCreation();
	std::getline(file, str, '\n');
	str = str + DELIMITER + name; //adds the user to the allProfiles.txt
	file >> str;
	file.close();
}
bool newProfileName(bool& exit, std::string& profile) {	
	std::string str;
	std::ifstream File(allProfiles);
	if (!File.is_open()) {
		allProfilesFileCreation();
		std::ifstream File(allProfiles); //to be improved, not closed in allProfilesFileCreation()
	}
redo:
	while(!File.eof()) {
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
void searchProfileName(bool& exit, std::string& profile) {
	std::string str;
	std::ifstream File(allProfiles);
	if (!File.is_open()) {
		allProfilesFileCreation();
		std::ifstream File(allProfiles);
	}
redo:
	while (!File.eof()) {
		std::getline(File, str, DELIMITER);
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
	while (string[iter] != 0) {
		if (string[iter] < '0' || string[iter]>'9') {
			fail = true;
			failedInput(fail);
			return true;
		}
		
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
		*a = 0;
		return;
	}
	if (str == "female" || str == "Female") {
		*a = 1;
		return;
	}
	fail = true;
}
void speedToWeight(const std::string input, unsigned* speed, bool& fail) {
	if (input == "0.25" && input == "0.25 kg") {
		*speed = 1;
		return;
	}
	if (input == "0.5" && input == "0.5 kg") {
		*speed = 2;
		return;
	}
	if (input == "0.75" && input == "0.75 kg") {
		*speed = 3;
		return;
	}
	if (input == "1" && input == "1 kg") {
		*speed = 4;
		return;
	}
	fail = true;
	failedInput(fail);
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
void goalInput(const std::string str, unsigned* goal, bool& fail) {
	if (str == "lose weight" || "Lose weight") {
		*goal = 1;
		return;
	}
	if (str == "keep weight" || "Keep weight") {
		*goal = 2;
		return;
	}
	if (str == "gain weight" || "Gain weight") {
		*goal = 3;
		return;
	}
	fail = true;
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
int charToInt(const char a) { //validation already made in stringToUnsigned
	return a - '0';
}
size_t strLen(std::string string) {
	size_t counter;
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
double stringToDouble(const std::string string, bool& fail) {
	if (multipleDotsCheck(string)) {
		fail = true;
		return 0;
	}
	size_t iter = 0;
	double num = 0.0;
	double decimalNum = 0.0;
	size_t length = strLen(string);
	bool dot = false;
	while (string[iter]) {
		if (string[iter] < '0' || string[iter]>'9') {
			if (string[iter] != '.') {
				return 1;
			}

		}
		if (string[iter] == '.') {
			dot = true;
			break;
		}
		num = num * 10 + charToInt(string[iter]);
		iter++;
	}
	iter = 0;
	while (dot) {
		char c = string[length - iter];
		if (c < '0' || c>'9') {
			if (c != '.') {
				fail = true;
				return 1;
			}

		}
		if (c == '.') break;
		decimalNum = decimalNum / 10 + charToInt(c);
		iter++;
	}
	decimalNum = decimalNum / 10;
	return num + decimalNum;

}
size_t stringToInt(const std::string string, bool& fail) {
	size_t number = 0;
	size_t iter = 0;
	while (string[iter]) {
		if (string[iter] < '0' || string[iter]>'9') {
			fail = true;
			return 0;
		}
		number = number * 10 + charToInt(string[iter]);
		++iter;
	}
	return number;
}
double stringToDouble(const std::string string, bool& fail) {
	size_t iter = 0;
	double num = 0.0;
	double decimalNum = 0.0;
	bool dot = false;
	while (string[iter]) {
		if (string[iter] < '0' || string[iter]>'9' || string[iter] != '.') {
			fail = true;
			return 0;
		}
		if (string[iter] && !dot) {
			num = num * 10 + charToInt(string[iter]);
			iter++;
			continue;
		}
		if (string[iter] && dot) {
			decimalNum = decimalNum / 10 + charToInt(string[iter]);
			iter++;
			continue;
		}
		if (string[iter] == '.') {
			dot = true;
			iter++;
		}

	}
	
}
void startingScreen(bool& fail, bool& exit, unsigned& nextAction) {
	std::string input;
	std::cout << "Welcome to MyFitnessPal!" << std::endl;
	std::cout << "Would you like to login or register(You can also always type exit to exit the program)" << std::endl;
	std::cin >> input;
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
}
double BMR(double bmr, const bool gender, const double weight,const double height, const unsigned age) {
	if (!gender)
		bmr = MALE_BMR_COEF + MALE_WEIGHT_COEF * weight + MALE_HEIGHT_COEF * height - MALE_AGE_COEF * age;
	else {
		bmr = FEMALE_BMR_COEF + FEMALE_WEIGHT_COEF * weight + FEMALE_HEIGHT_COEF * height - FEMALE_AGE_COEF * age;
	}
	return bmr;
}
void dailyNeededCalories(int& dailyCal,double bmr, const bool gender, const double weight, const double height, const double activityLevel, const unsigned age) {
	dailyCal = BMR(bmr, gender, weight, height, age)*activityLevel;

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
void reg(bool& fail, bool& exit, std::string& name,std::string& password, unsigned* userDataUnsigned[], bool* userDataBool[],double* userDataDouble[]) {
	std::string input;
	unsigned iter = 0;
	std::cout << "Welcome to the Registration Menu!" << std::endl;
	takenName:
	std::cout << "Please enter a name to use when logging in:" << std::endl;
	std::cin.ignore();
	newProfileName(exit, input);
	std::cout << "Enter a password you would like to use:" << std::endl;
	std::getline(std::cin, input);
	password = input;
	if (fail || exitCheck(input, exit)) return;
	std::cout << "Next we need to know your age:" << std::endl;
	ageLabel:
	std::getline(std::cin, input);
	if (failIntegerInput(input,fail)) goto ageLabel;
	*userDataUnsigned[iter] = stringToInt(input, fail);
	iter++;
	if (fail || exitCheck(input, exit)) return;
	std::cout << "What is your goal?(lose weight, keep weight, gain weight)" << std::endl;
	goalLabel:
	std::getline(std::cin, input);
	goalInput(input, userDataUnsigned[iter], fail);
	if (exitCheck(input, exit)) return;
	if (failedInput(fail)) goto goalLabel;
	iter++;
		if (!*userDataUnsigned[iter - 1] == 2) {
		std::cout << "How fast would you like to lose/gain weight in a week?(0.25kg,0.5 kg. 0.75 kg or 1 kg)";
		speedOfWeightLabel:
		std::cin >> input;
		speedToWeight(input, userDataUnsigned[iter], fail);
		if (exitCheck(input, exit)) return;
		if (failedInput(fail)) goto speedOfWeightLabel;
	}
	else userDataUnsigned[iter] = 0;
	iter = 0;
	std::cout << "Enter your height(in centimeters) below:" << std::endl;
	heightLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	*userDataDouble[iter] = stringToDouble(input, fail);
	if (failedInput(fail)) goto heightLabel;
	iter++;
	std::cout << "Please enter your weight(in kilograms):" << std::endl;
	weightLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	*userDataDouble[iter] = stringToDouble(input, fail);
	if (failedInput(fail)) goto weightLabel;
	iter++;
	std::cout << "We need to know your activity level";
	std::cout << " (choose between Very low(sitting work, no workout), Low(training 1-3 times a week), Medium(3-5 times a week), High(6-7 times a week), Very High(Physical work, heavy workouts))" << std::endl;
	activityLevelLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return; 
	activityInput(input, userDataDouble[iter], fail);
	if (failedInput(fail)) goto activityLevelLabel;
 	iter = 0;
	std::cout << "Please enter your gender(Male or Female):" << std::endl;
	genderLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	mOrf(input, userDataBool[iter], fail);
	iter++;
	if (failedInput(fail)) goto genderLabel;
	std::cout << "Lastly, do you want to subscribe to Premium?(Yes or No)" << std::endl;
	wantsPremiumLabel:
	std::getline(std::cin, input);
	if (exitCheck(input, exit)) return;
	wantsPremium(input, userDataBool[iter], fail);
	if (failedInput(fail)) goto wantsPremiumLabel;
	newProfileFile(name, password, userDataUnsigned, userDataBool, userDataDouble);
}
bool login(bool& fail, bool& exit, std::string name, std::string password, unsigned* userDataUnsigned[], bool* userDataBool[],double* userDataDouble[]) {
	reInput:
	bool check = false;
	std::cout << "Please enter your name:" << std::endl;
	std::cin >> name;
	if (exitCheck(name, exit)) return false;
	searchProfileName(exit, name);
	if (exitCheck(name, exit)) return false;
	loadInfo(fail, name, password, userDataUnsigned, userDataBool, userDataDouble);
	std::cout << "Successfully loaded info! Hello " << name << "!" << std::endl;

}
void addAMealToFile(const std::string name, std::string meal, int calories) {
	std::string filename = DATENAME + name +txt;
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
void todaysCheckout(const std::string name, double& dailyCalories, ) {

}
bool generalScreenNextAction(bool& fail, bool& exit, bool& logout, const std::string input, const std::string name, const unsigned* userDataUnsigned[], const double* userDataDouble[], const bool* userDataBool[], int& caloriesIntake, int& caloriesUsed, double bmr, int dailyCalories) {
	char number = stringToChar(input, fail);
	if (failedInput(fail)) {
		return true;
	}
	switch (number) {
	case '1': dailyCalorieScreen(); break;
	case '2': addADailyMeal(name, dailyCalories);
	case '3': addADailyWorkout(name, dailyCalories);
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '10':
	default: return true;
	}
}
void dailyCalorieScreen(bool& fail,bool&exit,bool&logout, const int dailyCalories, const double goal, const double speedOfWeight) {
	std::cout << "Recommended calorie intake:" << dailyCalories;
	std::cout << "Current calorie intake"; << 
}
int dailyCaloriesTillNow() {

}
void generalScreen(bool& fail, bool& exit,bool& logout,const std::string name,const unsigned age, const unsigned goal, const unsigned speedOfWeight, const double weight, const double height, const double activityLevel, const bool isPremium, const bool gender, int& caloriesIntake, int& caloriesUsed, double bmr, int dailyCalories) {
	std::string input;
	dailyNeededCalories(dailyCalories, bmr, gender,weight,height,activityLevel, age); //these are variables such as gender, weight, height, age
	generalScreenReInput:
	std::cout << "This is the General Screen!" << std::endl;
	std::cout << "What would you like to do:(enter a number representing your choice)" << std::endl;
	std::cout << "1.See calorie balance for today" << std::endl << "2.Add a meal" << std::endl << "3.Add a workout" << std::endl;
	std::cout << "6.Get your daily stats" << std::endl << "7.Get stats for a specific date" << std::endl;
	std::cout << "8.Delete data for a specific day" << std::endl << "9.Change meals and workouts for today" << std::endl;
	std::cout << "10.Edit personal data" << std::endl << "(You can also logout)" << std::endl;
	std::cin >> input;
	if (exitCheck(input, exit) || logoutCheck(input, logout)){
		return;
	}
	if (generalScreenNextAction()) goto generalScreenReInput;
	
}
int main()
{
	bool fail = false;
	bool exit = false;
	bool logout = false;
	unsigned nextAction = 0;
	std::string name = "null";
	std::string password = "null";
	unsigned age = 0;
	double weight = 0.0;
	double height = 0.0;
	double activityLevel = 0.0;
	unsigned goal = 0;
	unsigned speedOfWeight = 0;
	bool isPremium =0;
	bool gender =0;
	double BMR=0.0;
	double dailyCalories= 0.0;
	int caloriesIntake = 0;
	int caloriesUsed = 0;
	unsigned* userDataUnsigned[NUM_UNSIGNED_INFO] = {&age, &goal,&speedOfWeight};
	bool* userDataBool[NUM_BOOL_INFO] = { &gender, &isPremium };
	double* userDataDouble[NUM_DOUBLE_INFO] = { &height, &weight, &activityLevel};
	startingScreen(fail, exit, nextAction);
	if (failCheck(fail)) return 1;
	if (exit) return 0;
	if (nextAction) login(fail, exit, name, password, userDataUnsigned, userDataBool, userDataDouble);
	else reg(fail, exit, name, password, userDataUnsigned, userDataBool, userDataDouble);
	if (exit) return 0;
	if (failCheck(fail)) return 2;
	

}
