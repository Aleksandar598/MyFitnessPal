#pragma once
void nameInput(std::string& name, bool& exit, bool& logout) {
	bool nameCheck = false;
	std::string input;
	menuSeparator();
	do {
		bool fail = false;
		std::cout << "Please enter an Username you will use:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		doesProfileExistReg(input, exit, logout);
		if (exit || logout) return;
		name = input;
		do {
			std::cout << "Is this the name you would like to use: " << input << std::endl;
			fail = false;
			std::getline(std::cin, input);	
			if (logoutOrExitCheck(input, exit, logout)) return;
			yesOrNo(input, fail, nameCheck);
		} while (fail);
	} while (nameCheck);
}
void passwordInput(std::string& password, bool& exit, bool& logout) {
	std::string input;
	menuSeparator();
	do {
		std::cout << "Please enter a password you will use:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		password = input;
		std::cout << "Please enter password again to confirm: " << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input != password) {
			std::cout << "Passwords do not match!" << std::endl;
		}
		return;
	} while (true);
}
void ageInput(unsigned* age, bool&exit,bool&logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "Please enter your age:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
	} while (!isUnsigned(input));
	*age = std::stoi(input);
}
void heightInput(unsigned* height, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "Please enter your height:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
	} while (!isUnsigned(input));
	*height = std::stoi(input);
}
void goalInput(unsigned* goal, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "What is your goal?(lose weight, keep weight, gain weight):" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == "lose weight" || input == "Lose weight") {
			*goal = LOSE_WEIGHT;
			return;
		}
		if (input == "keep weight" || input == "Keep weight") {
			*goal = KEEP_WEIGHT;
			return;
		}
		if (input == "gain weight" || input == "Gain weight") {
			*goal = GAIN_WEIGHT;
			return;
		}
		failedInput();
	} while (true);
}
void weightInput(double* weight, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "Please enter you weight(In kg)" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (isDouble(input)) {
			*weight = std::stod(input);
			return;
		}
		failedInput();
	} while (true);
	
}
void activityLevelInput(double* activityLevel, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "Please enter your activity level";
		std::cout << " (choose between Very low(sitting work, no workout), Low(training 1-3 times a week), Medium(3-5 times a week), High(6-7 times a week), Very High(Physical work, heavy workouts))" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == "very low" || input == "Very low") {
			*activityLevel = VERY_LOW_ACTIVITY;
			return;
		}
		if (input == "low" || input == "Low") {
			*activityLevel = LOW_ACTIVITY;
			return;
		}
		if (input == "medium" || input == "Medium") {
			*activityLevel = MEDIUM_ACTIVITY;
			return;
		}
		if (input == "high" || input == "High") {
			*activityLevel = HIGH_ACTIVITY;
			return;
		}
		if (input == "very high" || input == "Very high") {
			*activityLevel = VERY_HIGH_ACTIVITY;
			return;
		}
		failedInput();
	} while (true);
}
void speedOfWeightInput(double* speedOfWeight, bool& exit, bool& logout) { 
	menuSeparator();
	std::string input;
	do {
		std::cout << "How fast would you like to lose/gain weight in a week?(0.25kg,0.5 kg. 0.75 kg or 1 kg)" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == "0.25" || input == "0.25 kg") {
			*speedOfWeight = SLOW_SPEEDTOWEIGHT;
			return;
		}
		if (input == "0.5" || input == "0.5 kg") {
			*speedOfWeight = MEDIUM_SPEEDTOWEIGHT;
			return;
		}
		if (input == "0.75" || input == "0.75 kg") {
			*speedOfWeight = HIGH_SPEEDTOWEIGHT;
			return;
		}
		if (input == "1" || input == "1 kg") {
			*speedOfWeight = VERY_HIGH_SPEEDTOWEIGHT;
			return;
		}
		failedInput();
	} while (true);
}
void genderInput(bool* gender, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "Enter your gender(male or female):" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == "male" || input == "Male") {
			*gender = false;
			return;
		}
		if (input == "female" || input == "Female") {
			*gender = true;
			return;
		}
		failedInput();
	} while (true);

}
void premiumInput(bool* isPremium, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	do {
		std::cout << "Would you like to subscribe to Premium? It is only 4.99$ and offers great features such as daily macronutrients calculator!:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == "yes" || input == "Yes") {
			*isPremium = true;
			return;
		}
		if (input == "no" || input == "No") {
			*isPremium = false;
			return;
		}
		failedInput();
	} while (true);
}