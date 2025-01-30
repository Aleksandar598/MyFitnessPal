#include <iostream>
#include <string>
#include <fstream>
#include "constants.h"
#include "player.h"
#include "registerFunctions.h"
#include "uncategorizedFunctions.h"
#include "FunctionsThatWorkWithFiles.h"

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
void reg(std::string& name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], bool& exit, bool& logout) {
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
	speedOfWeightInput(doubleDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter = 0;
	genderInput(boolDataArray[iter], exit, logout);
	if (exit || logout) return;
	iter++;
	premiumInput(boolDataArray[iter], exit, logout);
	if (exit || logout) return;
	newUserFileCreation(name, password, unsignedDataArray, doubleDataArray, boolDataArray);
}
void login(std::string& name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	doesProfileExistLogin(name, exit, logout);
	if (exit || logout) return;
	loadData(name, password, unsignedDataArray, doubleDataArray, boolDataArray);
	do {
		std::cout << "Please enter ypur password:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == password) {
			std::cout << "Successfully logged in!" << std::endl;
			return;
		}
		std::cout << "Incorrect password, please enter your password again:" << std::endl;
	} while (true);
}
void generalScreen() {

}
int main() {
	int dailyCalorieBalance = 0;
	unsigned caloriesIntake = 0;
	unsigned caloriesUsed = 0;
	unsigned age = 0;
	unsigned height = 0;
	unsigned goal = 0;
	double speedOfWeight = 0;
	double weight = 0.0;
	double activityLevel = 0.0;
	bool gender = false;
	bool isPremium = false;
	bool exit = false;
	bool logout = false;
	std::string name = "null";
	std::string password = "null";
	unsigned* unsignedDataArray[numOfUnsignedData] = { &age, &height, &goal};
	double* doubleDataArray[numOfDoubleData] = { &weight, &activityLevel,&speedOfWeight};
	bool* boolDataArray[numOfBoolData] = {&gender, &isPremium };
	if (startingScreen(exit, logout)) {
		if (exit) return 0;
		reg(name, password, unsignedDataArray, doubleDataArray, boolDataArray, exit, logout);
	}
	else login(name, password, unsignedDataArray, doubleDataArray, boolDataArray, exit, logout);

}
