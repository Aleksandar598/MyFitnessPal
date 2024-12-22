#include <iostream>
#include <string>
const size_t MAX_INPUT_SIZE = 1024;
bool failCheck(bool fail) {
	if (std::cin.fail() || fail==true) return true;
	return false;
}
bool startingMenu(bool& fail){     //This function will be used for the starting menu
	std::string input;
	std::cout << "Hello to MyFitnessPal!" << std::endl;
	std::cout << "Would you like to Login or Register?" << std::endl;
	std::cin >> input;
	if (input != "Login" || input != "login" || input != "Register" || input != "register") fail = true;

}
bool LogOut(std::string input) { //This function will check if the user has typed LogOut
	if (input == "Log Out") return true;
	return false;
}
int main() {
	bool fail = false;
	unsigned age = 0;
	unsigned height = 0; //in centimeters
	unsigned weight = 0; //in kg
	unsigned activityLevel = 0;
	unsigned goal = 0; //0 for losing weight, 1 for keeping shape, 2 for gaining weight
	char gender = false;
	startingMenu(fail);
}
