#pragma once

void nameInput(bool& exit, std::string& input);

void passwordInput(std::string& input, std::string& password);

void heightInput(std::string& input, bool& exit, double* userDataDouble[], unsigned int& iter, bool& fail, bool& retFlag);

void speedToWeightInput(unsigned int* userDataUnsigned[], unsigned int& iter, std::string& input, bool& fail, bool& exit, bool& retFlag);

void goalInput(std::string& input, unsigned int* userDataUnsigned[], unsigned int& iter, bool& fail, bool& exit, bool& retFlag);

void ageInput(std::string& input, bool& fail, unsigned int* userDataUnsigned[], unsigned int iter);

void weightInput(std::string& input, bool& exit, double* userDataDouble[], unsigned int& iter, bool& fail, bool& retFlag);

void activityLevelInput(std::string& input, bool& exit, double* userDataDouble[], unsigned int& iter, bool& fail, bool& retFlag);

void genderInput(std::string& input, bool& exit, bool* userDataBool[], unsigned int& iter, bool& fail, bool& retFlag);

void premiumInput(std::string& input, bool& exit, bool* userDataBool[], unsigned int iter, bool& fail, bool& retFlag);
