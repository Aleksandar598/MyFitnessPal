#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include "constants.h"
#include "player.h"
#include "registerFunctions.h"
#include "uncategorizedFunctions.h"
#include "FunctionsThatWorkWithFiles.h"
#include "generalScreenFunctions.h"

bool startingScreen(bool& exit,bool& logout) {
	do {
		std::string input;
		menuSeparator();
		std::cout << "Hello to MyFitnessPal! Would you like to login or register?" << std::endl;
		std::getline(std::cin, input);
		if (input == "register" || input == "Register") {
			return true;
		}
		if (input == "login" || input == "Login") {
			return false;
		}
		if (logoutOrExitCheck(input, exit, logout)) return true;
		failedInput();
	}
	while (true);

}
void reg(std::string& name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[],unsigned& goal, bool& exit, bool& logout) {
	unsigned iter = 0;
	menuSeparator();
	std::cout << "Welcome to the Registration Menu!" << std::endl;
	nameInput(name, exit, logout);
	if (exit || logout) return;
	passwordInput(password, exit, logout);
	if (exit || logout) return;
	ageInput(unsignedDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter++;
	heightInput(unsignedDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter++;
	goalInput(unsignedDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter = 0;
	weightInput(doubleDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter++;
	activityLevelInput(doubleDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter++;
	if (goal == KEEP_WEIGHT) *doubleDataArray[iter] = 0;
	else speedOfWeightInput(doubleDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter = 0;
	genderInput(boolDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter++;
	premiumInput(boolDataArray[iter], exit, logout);
	if (exit || logout) return;
	UserDataSave(name, password, unsignedDataArray, doubleDataArray, boolDataArray);
	saveNewUserName(name);
}
void login(std::string& name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[],unsigned& calorieIntake,unsigned&caloriesUsed, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	std::cout << "Please enter your name:" << std::endl;
	std::getline(std::cin, name);
	doesProfileExistLogin(name, exit, logout);
	if (exit || logout) return;
	loadData(name, password, unsignedDataArray, doubleDataArray, boolDataArray, calorieIntake, caloriesUsed);
	do {
		std::cout << "Please enter your password:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == password) {
			std::cout << "Successfully logged in!" << std::endl;
			return;
		}
		std::cout << "Incorrect password, please enter your password again:" << std::endl;
	} while (true);
}
void generalScreen(const std::string name,const std::string password,unsigned* unsignedDataArray[],double* doubleDataArray[],bool* boolDataArray[], unsigned& caloriesIntake,unsigned& caloriesUsed, int& dailyCalorieBalance, unsigned& age,unsigned&height,unsigned& goal, double& speedOfWeight, double& weight, double& activityLevel, bool& gender, bool& isPremium, bool& exit, bool& logout) {
	menuSeparator();
	bool reloadCalories = false;
	loadCaloriesData(name, caloriesIntake, caloriesUsed);
	dailyCalorieBalance = caloriesIntake - caloriesUsed;
	do {
		if (reloadCalories) {
			loadCaloriesData(name, caloriesIntake, caloriesUsed);
			dailyCalorieBalance = caloriesIntake - caloriesUsed;
			reloadCalories = false;
		}
		unsigned recommendedDailyCalories = recommendedCalorieIntake(age, weight, height, goal, gender, activityLevel, speedOfWeight);
		std::cout << "Welcome to the general screen, " << name << '!' << std::endl;
		std::cout << "Your daily calorie intake is: " << caloriesIntake << std::endl;
		std::cout << "Your daily calorie usage is: " << caloriesUsed << std::endl;
		std::cout << "Your daily calorie balance is: " << dailyCalorieBalance << std::endl;
		std::cout << "Recommended daily calorie intake: " << recommendedDailyCalories << std::endl;
		generalScreenNextAction(name,password, unsignedDataArray, doubleDataArray, boolDataArray, caloriesIntake,caloriesUsed,dailyCalorieBalance,recommendedDailyCalories,age,height,goal,speedOfWeight, weight, activityLevel, gender, isPremium, exit,logout,reloadCalories);
		if (exit || logout) return;
	} while (true);
}
int main() {
	int dailyCalorieBalance = 0;
	unsigned calorieIntake = 0;
	unsigned caloriesUsed = 0;
	unsigned age = 0;
	unsigned height = 0;
	unsigned goal = 0;
	double speedOfWeight = 0.0;
	double weight = 0.0;
	double activityLevel = 0.0;
	bool gender = false;
	bool isPremium = false;
	bool exit = false;
	bool logout = false;
	std::string name = "null";
	std::string password = "null";
	unsigned* unsignedDataArray[NUM_OF_UNSIGNED_DATA] = { &age, &height, &goal };
	double* doubleDataArray[NUM_OF_DOUBLE_DATA] = { &weight, &activityLevel, &speedOfWeight };
	bool* boolDataArray[NUM_OF_BOOL_DATA] = { &gender, &isPremium };
	do {
		logout = false;
		if (startingScreen(exit, logout)) {
			if (exit) return 0;
			reg(name, password, unsignedDataArray, doubleDataArray, boolDataArray, goal, exit, logout);
		}
		else login(name, password, unsignedDataArray, doubleDataArray, boolDataArray, calorieIntake, caloriesUsed, exit, logout);
		if (exit) return 0;
		generalScreen(name, password, unsignedDataArray, doubleDataArray, boolDataArray, calorieIntake, caloriesUsed, dailyCalorieBalance, age, height, goal, speedOfWeight, weight, activityLevel, gender, isPremium, exit, logout);
		if (exit) return 0;
	} while (logout);
}
