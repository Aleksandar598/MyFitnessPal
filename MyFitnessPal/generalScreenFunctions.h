#pragma once
void generalScreenNextAction(const std::string name,const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], unsigned& caloriesIntake, unsigned& caloriesUsed, int& dailyCalorieBalance,unsigned& recommendedCalories, unsigned& age, unsigned& height, unsigned& goal, double& speedOfWeight, double& weight, double& activityLevel, bool& gender, bool& isPremium, bool& exit, bool& logout, bool& reloadCalories) {
	std::string input;
	do {
		menuSeparator();
		std::cout << "What would you like to do next?" << std::endl;
		std::cout << "1. Display full calorie data for today." << std::endl;
		std::cout << "2. Add a Meal for the day." << std::endl;
		std::cout << "3. Add a Workout for the day." << std::endl;
		std::cout << "4. Display all workout and meals for today." << std::endl;
		std::cout << "5. Display all workout and meals for a specific day." << std::endl;
		std::cout << "6. Delete data for a specific day." << std::endl;
		std::cout << "7. Change workouts and meals for today." << std::endl;
		std::cout << "8. Change personal data." << std::endl;
		std::cout << "Please enter the number of the action you would like to take:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
	} while (!generalScreenInput(input));
	
	switch (input[0]) {
		case '1': caloriesForToday(caloriesIntake,caloriesUsed,dailyCalorieBalance,recommendedCalories,goal,isPremium,exit,logout) ; break;
		case '2':
			addMeal(name, exit, logout); 
			reloadCalories = true;
			break;
		case '3':
			addWorkout(name, exit, logout);
			reloadCalories = true; 
			break;
		case '4': displayDataForToday(name, exit, logout); break;
		case '5': displayDataForASpecificDay(name, exit, logout); break;
		case '6': deleteDataForSpecificDay(name, exit, logout); break;
		case '7':
			changeDataForToday(name, exit, logout);
			reloadCalories = true;
			break;
		case '8':
			changePersonalData(name, password, unsignedDataArray,doubleDataArray,boolDataArray,age,height,goal,speedOfWeight, weight,activityLevel,gender,isPremium,exit,logout);
			reloadCalories = true;
			break;
	}
}
bool generalScreenInput(const std::string input) {
	if (strLen(input) > 1 || strLen(input) == 0) {
		failedInput();
		return false;
	}
	if (input[0] > '8' || input[0] < '1') {
		failedInput();
		return false;
	}
	return true;
}
double BMR(const unsigned age, const double weight, const unsigned height, const bool gender) {
	double BMR = 0.0;
	if (!gender) {
		BMR = MALE_BMR_COEF + (MALE_WEIGHT_COEF * weight) + (MALE_HEIGHT_COEF * height) + (MALE_AGE_COEF * age);
	}
	if (gender) {
		BMR = FEMALE_BMR_COEF + (FEMALE_WEIGHT_COEF * weight) + (FEMALE_HEIGHT_COEF * height) + (FEMALE_AGE_COEF * age);
	}
	return BMR;
}
unsigned recommendedCalorieIntake(const unsigned age, const double weight, const unsigned height,const unsigned goal, const bool gender, const double activityLevel, const double speedOfWeight) {
	double recommendedCalorieIntake = BMR(age, weight, height, gender) * activityLevel;
	if (goal == 1) {
		recommendedCalorieIntake -= CALORIES_PER_KG_FOR_WEEK * speedOfWeight;
	}
	if (goal == 3) {
		recommendedCalorieIntake += CALORIES_PER_KG_FOR_WEEK * speedOfWeight;
	}
	return recommendedCalorieIntake;
}
void caloriesForToday(const unsigned caloriesIntake, const unsigned caloriesUsed, const int dailyCalorieBalance,const unsigned recommendedCalories,const unsigned goal, const bool isPremium, bool& exit, bool& logout) {
	menuSeparator();
	std::cout << "Your daily calorie intake is: " << caloriesIntake << std::endl;
	std::cout << "Your daily calorie usage is: " << caloriesUsed << std::endl;
	std::cout << "Your daily calorie balance is: " << dailyCalorieBalance << std::endl;
	std::cout << "Recommended daily calorie intake: " << recommendedCalories << std::endl;
	if (!isPremium)std::cout << "If you had premium, you would have access to daily macronutrients calculator!" << std::endl;
	else displayMacronutrients(recommendedCalories, goal);
	std::cout << "Press enter to return to the general screen:" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	if (logoutOrExitCheck(input, exit, logout)) return;
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
void displayMacronutrients(const int recommendedCalorieIntake, const unsigned goal) {
	int carbohydrates = 0;
	int fat = 0;
	int protein = 0;
	int proteinGrams = 0;
	int fatGrams = 0;
	int carbohydratesGrams = 0;
	calculateMacronutriens(goal, carbohydrates, recommendedCalorieIntake, fat, protein, carbohydratesGrams, proteinGrams, fatGrams);
	std::cout << "Recommended protein intake: " << protein << " calories or " << proteinGrams << " grams" << std::endl;
	std::cout << "Recommended carbohydrates intake: " << carbohydrates << " calories or " << carbohydratesGrams << " grams" << std::endl;
	std::cout << "Recommended fat intake: " << fat << " calories or " << fatGrams << " grams" << std::endl;
}
void addMeal(const std::string name,bool& exit,bool&logout) {
	menuSeparator();
	std::string input;
	std::string mealName;
	unsigned calories = 0;
	std::cout << "Please enter the name of the meal:" << std::endl;
	std::getline(std::cin, mealName);
	if (exit || logout) return;
	if (logoutOrExitCheck(mealName, exit, logout)) return;
	do {
		std::cout << "Please enter the amount of calories in the meal:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
	} while (!isUnsigned(input));
	mealName = MEAL_DIFFERENTIATOR + mealName;
	calories = std::stoi(input);
	addMealorWorkoutToFile(name, mealName, calories);
}
void addWorkout(const std::string name, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	std::string workoutName;
	unsigned calories = 0;
	std::cout << "Please enter the name of the workout:" << std::endl;
	std::getline(std::cin, workoutName);
	if (exit || logout) return;
	if (logoutOrExitCheck(workoutName, exit, logout)) return;
	do {
		std::cout << "Please enter the amount of calories used in the workout:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
	} while (!isUnsigned(input));
	workoutName = WORKOUT_DIFFERENTIATOR + workoutName;
	calories = std::stoi(input);
	addMealorWorkoutToFile(name, workoutName, calories);
}
void displayDataForToday(std::string name, bool& exit, bool& logout) {
	menuSeparator();
	std::string date = currentDate();
	std::string read;
	bool dateFound = false;
	std::vector<std::string> dailyInfo;
	dailyInfo = loadDataForASpecificDay(name, date, dateFound);
	if (dateFound)vectorDataPrint(dailyInfo);
	else std::cout << "There is no data for today yet!" << std::endl;
	std::cout << "Press anything to continue." << std::endl;
	std::getline(std::cin, read);
	logoutOrExitCheck(read, exit, logout);
}
void displayDataForASpecificDay(std::string name, bool& exit, bool& logout) {
	menuSeparator();
	std::string date;
	std::string read;
	bool dateExists = false;
	std::vector<std::string> dailyInfo;
	bool fail = false;
	do {
		fail = false;
		std::cout << "Please enter the date you would like to see the data for:(YYYY-MM-DD)" << std::endl;
		std::getline(std::cin, date);
		if (logoutOrExitCheck(date, exit, logout)) return;
		if (!checkForDatestring(date)) {
			failedInput();
			fail = true;
		}
	} while (fail);
	dailyInfo = loadDataForASpecificDay(name, date, dateExists);
	if (dateExists) vectorDataPrint(dailyInfo);
	else std::cout << "There is no data" << std::endl;
	std::cout << "Press anything to continue." << std::endl;
	std::getline(std::cin, read);
	logoutOrExitCheck(read, exit, logout);
}
void deleteDataForSpecificDay(std::string name, bool& exit, bool& logout) {
	menuSeparator();
	std::string date;
	bool fail = false;
	std::cout << "Please enter the date you would like to delete the data for:(YYYY-MM-DD)" << std::endl;
	do{
		fail = false;
		std::getline(std::cin, date);
		if (logoutOrExitCheck(date, exit, logout)) return;
		if (!checkForDatestring(date)) {
			failedInput();
			fail = true;
	}
	} while (fail);
	if (deleteDataFromFile(name, date)) {
		std::cout << "Data for " << date << " has been deleted." << std::endl;
	}
	else {
		std::cout << "No data for " << date << " was found." << std::endl;
	}
	std::cout << "Press anything to continue." << std::endl;
	std::getline(std::cin, date);
}
void changeDataForToday(const std::string name, bool& exit, bool& logout) {
	menuSeparator();
	std::string date = currentDate();
	bool dateFound = false;
	bool deletion = false;
	std::vector<std::string> dailyInfo;
	dailyInfo = loadDataForASpecificDay(name, date,dateFound);
	if (dateFound) {
		dailyInfo = vectorDataModify(dailyInfo,deletion, exit, logout);
		if (exit || logout) return;
		saveModifiedInfoForToday(name, dailyInfo, deletion);
		std::cout << "Data has been modified." << std::endl;
	}
	else std::cout << "Data for this day not found!" << std::endl;
	std::cout << "Press anything to continue." << std::endl;
	std::getline(std::cin, date);
}
std::vector<std::string> vectorDataModify(std::vector<std::string> dailyInfo,bool& deletion, bool& exit, bool& logout) {
	std::string input;
	size_t choice = 0;
	bool fail = false;
	vectorDataPrint(dailyInfo);
	do {
		fail = false;
		do {
			std::cout << "Please enter the number of the workout or meal you would like to change:" << std::endl;
			std::getline(std::cin, input);
			if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
		} while (!isUnsigned(input));
		choice = std::stoi(input);
		if (choice > dailyInfo.size() / 2+2) {
			failedInput();
			fail = true;
		}
	} while (fail);
	choice = choice * 2 - 2; // this way we will modify the data from the string
	do {
		fail = true;
		std::cout << "Would you like to delete the meal/workout?" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
		if (input == "Yes" || input == "yes") {
			dailyInfo.erase(dailyInfo.begin() + choice);
			dailyInfo.erase(dailyInfo.begin() + choice);
			deletion = true;
			fail = false;
		}
		if (input == "No" || input == "no") {
			dailyInfo = changeWorkoutOrMeal(dailyInfo, choice, exit, logout);
			if (exit || logout) return dailyInfo;
			fail = false;
		}
	} while (fail);
	return dailyInfo;
}
std::vector<std::string> changeWorkoutOrMeal(std::vector<std::string> dailyInfo, size_t choice, bool& exit, bool& logout) {
	std::string input;
	bool fail = true;
	do {
		std::cout << "What would you like to change it to?(Workout or meal)" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
		if (input == "Workout" || input == "workout") {
			fail = false;
			std::cout << "Please enter the name of the workout:" << std::endl;
			std::getline(std::cin, input);
			if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
			dailyInfo[choice] = WORKOUT_DIFFERENTIATOR + input;
			do {
				std::cout << "Please enter the amount of calories used in the workout:" << std::endl;
				std::getline(std::cin, input);
				if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
			} while (!isUnsigned(input));
			dailyInfo[choice + 1] = input;
		}
		if (input == "Meal" || input == "meal") {
			fail = false;
			std::cout << "Please enter the name of the meal:" << std::endl;
			std::getline(std::cin, input);
			if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
			dailyInfo[choice] = MEAL_DIFFERENTIATOR + input;
			do {
				std::cout << "Please enter the amount of calories in the meal:" << std::endl;
				std::getline(std::cin, input);
				if (logoutOrExitCheck(input, exit, logout)) return dailyInfo;
			} while (!isUnsigned(input));
			dailyInfo[choice + 1] = input;
		}
		if (fail) failedInput();
	} while (fail);
	return dailyInfo;
}
void changePersonalData(const std::string name,const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], unsigned& age, unsigned& height, unsigned& goal, double& speedOfWeight, double& weight, double& activityLevel, bool& gender, bool& isPremium, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	unsigned iter = 0;
	do {
		std::cout << "What would you like to change?" << std::endl;
		std::cout << "1. Age: " << age << std::endl;
		std::cout << "2. Height: " << height << std::endl;
		std::cout << "3. Goal: " << goalOutput(goal) << std::endl;
		std::cout << "4. Weight: " << weight << std::endl;
		std::cout << "5. Activity Level: " << activityLevelOutput(activityLevel) << std::endl;
		std::cout << "6. Speed of weight: " << speedToWeightOutput(speedOfWeight) << std::endl;
		std::cout << "7. Gender: " << genderOutput(gender) << std::endl;
		std::cout << "8. Premium: " << isPremiumOutput(isPremium) << std::endl;
		std::cout << "Please enter the number of the data you would like to change:" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
	} while (!generalScreenInput(input));
	generalScreenInput(input);
	switch (input[0]) {
	case '1': ageInput(&age, exit, logout); break;
	case '2': heightInput(&height, exit, logout); break;
	case '3': goalInputGeneralScreen(&goal,&speedOfWeight, exit, logout); break;
	case '4': weightInput(&weight, exit, logout); break;
	case '5': activityLevelInput(&activityLevel, exit, logout); break;
	case '6': speedOfWeightChange(speedOfWeight,goal, exit, logout); break;
	case '7': genderInput(&gender, exit, logout); break;
	case '8': premiumInput(&isPremium, exit, logout); break;
	}
	if (exit || logout) return;
	UserDataSave(name, password, unsignedDataArray, doubleDataArray, boolDataArray);
}
std::string speedToWeightOutput(const double speedToWeight) {
	if (std::fabs(speedToWeight - SLOW_SPEEDTOWEIGHT) < EPSILON) return "0.25 kg a week";
	if (std::fabs(speedToWeight - MEDIUM_SPEEDTOWEIGHT) < EPSILON) return "0.5 kg a week";
	if (std::fabs(speedToWeight - HIGH_SPEEDTOWEIGHT) < EPSILON) return "0.75 kg a week";
	if (std::fabs(speedToWeight - VERY_HIGH_SPEEDTOWEIGHT) < EPSILON) return "1 kg a week";
	return "0 kg a week";
}
std::string activityLevelOutput(const double activityLevel) {
	if (std::fabs(activityLevel - VERY_LOW_ACTIVITY) < EPSILON) return "Very low";
	if (std::fabs(activityLevel - LOW_ACTIVITY) < EPSILON) return "Low";
	if (std::fabs(activityLevel - MEDIUM_ACTIVITY) < EPSILON) return "Medium";
	if (std::fabs(activityLevel - HIGH_ACTIVITY) < EPSILON) return "High";
	if (std::fabs(activityLevel - VERY_HIGH_ACTIVITY) < EPSILON) return "Very high";
	return "";
}
std::string genderOutput(const bool a) {
	if (a) return "Female";
	else return "Male";
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
std::string isPremiumOutput(const bool isPremium) {
	if (isPremium) return "Yes";
	return "No";
}
void speedOfWeightChange(double& speedOfWeight,const unsigned goal, bool& exit, bool& logout) {
	menuSeparator();
	std::string input;
	if (goal == KEEP_WEIGHT) {
		std::cout << "First change your goal to either gain weight or lose weight!" << std::endl;
		std::cout << "Enter anything to continue" << std::endl;
		std::getline(std::cin, input);
		return;
	}
	do {
		std::cout << "How fast would you like to lose/gain weight in a week?(0.25kg,0.5 kg. 0.75 kg or 1 kg)" << std::endl;
		std::getline(std::cin, input);
		if (logoutOrExitCheck(input, exit, logout)) return;
		if (input == "0.25" || input == "0.25 kg") {
			speedOfWeight = SLOW_SPEEDTOWEIGHT;
			return;
		}
		if (input == "0.5" || input == "0.5 kg") {
			speedOfWeight = MEDIUM_SPEEDTOWEIGHT;
			return;
		}
		if (input == "0.75" || input == "0.75 kg") {
			speedOfWeight = HIGH_SPEEDTOWEIGHT;
			return;
		}
		if (input == "1" || input == "1 kg") {
			speedOfWeight = VERY_HIGH_SPEEDTOWEIGHT;
			return;
		}
		failedInput();
	} while (true);
}
void goalInputGeneralScreen(unsigned* goal,double* speedToWeight, bool& exit, bool& logout) {
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
			*speedToWeight = 0.0;
			return;
		}
		if (input == "gain weight" || input == "Gain weight") {
			*goal = GAIN_WEIGHT;
			return;
		}
		failedInput();
	} while (true);
}