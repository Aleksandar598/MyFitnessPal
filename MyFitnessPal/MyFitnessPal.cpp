#include <iostream>
#include <string>

size_t MAX_INPUT_SIZE = 1024;

bool failCheck(bool fail) {
	if (fail) {
		std::cout << "There was an error in the program execution";
		return true;
	}
	return false;
}

bool exitCheck(std::string toCheck, bool& exit) { //check if the user wished to exit the program
	if (toCheck == "exit") {
		exit = true;
		return true;
	}
	return false;
}
void mOrf(std::string str, char& a, bool& fail) {
	if (str == "male" || str == "Male") {
		a = 'm';
		return;
	}
	if (str == "female" || str == "Female") {
		a = 'f';
		return;
	}
	fail = true;
}
void activityInput(std::string str, unsigned& activityLevel, bool& fail) {
	if (str == "very low" || str == "Very low") {
		activityLevel = 1;
		return;
	}
	if (str == "low" || str == "Low") {
		activityLevel = 2;
		return;
	}
	if (str == "medium" || str == "Medium") {
		activityLevel = 3;
		return;
	}
	if (str == "high" && str == "High") {
		activityLevel = 4;
		return;
	}
	if (str == "very high" || str == "Very high") {
		activityLevel = 5;
		return;
	}
	fail = true;
}
void goalInput(std::string str, unsigned& goal, bool& fail) {
	if (str == "lose weight" || "Lose weight") {
		goal = 1;
		return;
	}
	if (str == "keep weight" || "Keep weight") {
		goal = 2;
		return;
	}
	if (str == "gain weight" || "Gain weight") {
		goal = 3;
		return;
	}
	fail = true;
}
void wantsPremium(std::string str, bool& isPremium, bool& fail) {
	if (str == "yes" || str == "Yes") {
		isPremium = true;
		return;
	}
	if (str == "no" || str == "No") {
		isPremium = false;
		return;
	}
	fail = true;

}
int charToInt(char a) { //validation already made in stringToUnsigned
	return a - '0';
}
unsigned stringToInt(std::string string, bool& fail) {
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
void reg(bool& fail, bool& exit, std::string name,std::string password, unsigned& age, char& gender, unsigned& height, unsigned& weight, unsigned& activityLevel, unsigned& goal, bool& isPremium) {
	std::string input;
	std::cout << "Welcome to the Registration Menu!" << std::endl;
	std::cout << "Please enter a name to use when logging in:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, input);
	name = input; //need to add validation if such filename exists
	std::cout << "Enter a password you would like to use:" << std::endl;
	std::getline(std::cin, input);
	password = input;
	if (fail || exitCheck(input, exit)) return;
	std::cout << "Next we need to know your age:" << std::endl;
	std::getline(std::cin, input);
	age = stringToInt(input, fail);
	if (fail || exitCheck(input, exit)) return; //will check for failure in input, and failCheck will end program in main
	std::cout << "Please enter your gender(Male or Female):" << std::endl;
	std::getline(std::cin, input);
	mOrf(input, gender, fail);
	if (fail || exitCheck(input, exit)) return;
	std::cout << "Enter your height(in centimeters) below:" << std::endl;
	std::getline(std::cin, input);
	height = stringToInt(input, fail);
	if (fail || exitCheck(input, exit)) return;
	std::cout << "Please enter your weight(in kilograms):" << std::endl;
	std::getline(std::cin, input);
	weight = stringToInt(input, fail);
	if (fail || exitCheck(input, exit)) return;
	std::cout << "We need to know your activity level";
	std::cout << " (choose between Very low, Low, Medium, High, Very High)" << std::endl;
	std::getline(std::cin, input);
	activityInput(input, activityLevel, fail);
	if (fail || exitCheck(input, exit)) return;
	std::cout << "What is your goal?(lose weight, keep weight, gain weight)" << std::endl;
	std::getline(std::cin, input);
	goalInput(input, goal, fail);
	if (fail || exitCheck(input, exit)) return;
	std::cout << "Lastly, do you want to subscribe to Premium?(Yes or No)" << std::endl;
	std::getline(std::cin, input);
	wantsPremium(input, isPremium, fail);
	if (fail || exitCheck(input, exit)) return;
	//to add file saving
	
}
int main()
{
	bool fail = false;
	bool exit = false;
	unsigned nextAction = 0;
	std::string name = "null";
	std::string password = "null";
	unsigned age, weight, height, activityLevel, goal;
	bool isPremium;
	char gender;
	startingScreen(fail, exit, nextAction);
	if (failCheck(fail)) return 1;
	if (exit) return 0;
	if (!nextAction) reg(fail, exit, name,password, age, gender, height, weight, activityLevel, goal, isPremium);
	if (exit) return 0;
	if (failCheck(fail)) return 2;

}
