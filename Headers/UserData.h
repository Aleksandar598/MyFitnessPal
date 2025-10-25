#pragma once
#include <string>
#include <vector>

class Activity;
class User;

class UserData {
  User* user = nullptr;
  std::vector<Activity*> activities;
  size_t calorieBalance=0;

public:
  UserData() = default;
  UserData(User* user);
  UserData(const UserData& other);
  UserData& operator=(const UserData& other);
  ~UserData();

  User* getUser() const;
  void addActivity(Activity* activity);
  void removeActivity(size_t index);
  Activity* getActivity(size_t index) const;

  std::ofstream& serialize(std::ofstream& ofs) const;
  std::ifstream& deserialize(std::ifstream& ifs);

private:
  void copyFrom(const UserData& other);
  void free();
};


#
