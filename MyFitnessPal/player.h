/*
Soltuion to course project #9
Introduction to proramming course
Faculty of Matematics and Informatics of Sofia University
Winter semester 2024/2025

@ Aleksandar Angelov
@ GCC
File declares functions
*/
void menuSeparator();
bool logoutOrExitCheck(std::string input, bool& exit, bool& logout);
void failedInput();
bool startingScreen(bool& exit, bool& logout);
void yesOrNo(std::string input, bool& fail, bool& nameIsGood);
void nameInput(std::string& name, bool& exit, bool& logout);
void passwordInput(std::string& password, bool& exit, bool& logout);
void doesProfileExistReg(std::string& name, bool& exit, bool& logout);
void doesProfileExistLogin(std::string name, bool& exit, bool& logout);
void loadData(const std::string name, std::string& password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], unsigned& calorieIntake, unsigned& caloriesUsed);
bool isUnsigned(const std::string str);
void ageInput(unsigned* age, bool& exit, bool& logout);
void heightInput(unsigned* height, bool& exit, bool& logout);
void goalInput(unsigned* goal, bool& exit, bool& logout);
void weightInput(double* weight, bool& exit, bool& logout);
void activityLevelInput(double* activityLevel, bool& exit, bool& logout);
void speedOfWeightInput(double* speedOfWeight, bool& exit, bool& logout);
void genderInput(bool* gender, bool& exit, bool& logout);
void premiumInput(bool* isPremium, bool& exit, bool& logout);
bool isDouble(const std::string str);
void UserDataSave(const std::string name, const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[]);
std::string currentDate();
size_t strLen(std::string string);
bool checkForDatestring(const std::string string);
double BMR(const unsigned age, const double weight, const unsigned height, const bool gender);
unsigned recommendedCalorieIntake(const unsigned age, const double weight, const unsigned height, const unsigned goal, const bool gender, const double activityLevel, const double speedOfWeight);
void addMealorWorkoutToFile(const std::string name, const std::string mealorWorkoutName, const unsigned calories);
void addMeal(const std::string name,bool& exit, bool& logout);
void addWorkout(const std::string name, bool& exit, bool& logout);
void loadCaloriesData(std::string name, unsigned& caloriesIntake, unsigned& caloriesUsed);
std::vector<std::string> loadDataForASpecificDay(const std::string name, const std::string date, bool& dateFound);
void vectorDataPrint(std::vector<std::string> dailyInfo);
void displayDataForToday(std::string name, bool& exit, bool& logout);
void displayDataForASpecificDay(std::string name, bool& exit, bool& logout);
bool deleteDataFromFile(const std::string name, const std::string date);
void ChoicePosInVector(size_t& choice);
std::vector<std::string> vectorDataModify(std::vector<std::string> dailyInfo, bool& deletion, bool& exit, bool& logout);
std::vector<std::string> changeWorkoutOrMeal(std::vector<std::string> dailyInfo, size_t choice, bool& exit, bool& logout);
void saveModifiedInfoForToday(const std::string name, std::vector<std::string> dailyInfo, const bool deletion);
void caloriesForToday(const unsigned caloriesIntake, const unsigned caloriesUsed, const int dailyCalorieBalance, const unsigned recommendedCalories, const unsigned goal, const bool isPremium, bool& exit, bool& logout);
void changeDataForToday(const std::string name, bool& exit, bool& logout);
void generalScreenNextAction(const std::string name, const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], unsigned& caloriesIntake, unsigned& caloriesUsed, int& dailyCalorieBalance, unsigned& recommendedCalories, unsigned& age, unsigned& height, unsigned& goal, double& speedOfWeight, double& weight, double& activityLevel, bool& gender, bool& isPremium, bool& exit, bool& logout, bool& reloadCalories);
bool generalScreenInput(const std::string input);
void caloriesForToday(const unsigned caloriesIntake, const unsigned caloriesUsed, const int dailyCalorieBalance, const unsigned recommendedCalories, const unsigned goal, const bool isPremium, bool& exit, bool& logout);
std::string speedToWeightOutput(const double speedToWeight);
std::string activityLevelOutput(const double activityLevel);
std::string genderOutput(const bool a);
std::string goalOutput(const unsigned goal);
std::string isPremiumOutput(const bool isPremium);
void displayMacronutrients(const int recommendedCalorieIntake, const unsigned goal);
void changePersonalData(const std::string name, const std::string password, unsigned* unsignedDataArray[], double* doubleDataArray[], bool* boolDataArray[], unsigned& age, unsigned& height, unsigned& goal, double& speedOfWeight, double& weight, double& activityLevel, bool& gender, bool& isPremium, bool& exit, bool& logout);
void deleteDataForSpecificDay(std::string name, bool& exit, bool& logout);
void speedOfWeightChange(double& speedOfWeight, const unsigned goal, bool& exit, bool& logout);
void howToUse(bool& exit, bool& logout);
void goalInputGeneralScreen(unsigned* goal, double* speedToWeight, bool& exit, bool& logout);
void ChoicePosInVector(size_t& choice);
bool doesStrinConatinDots(std::string str);