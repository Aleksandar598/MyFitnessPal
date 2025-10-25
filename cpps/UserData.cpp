#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/UserData.h"
#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/User.h"
#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/Activity.h"
#include <fstream>

UserData::UserData(User *user) {
  this->user = user;
}
UserData::UserData(const UserData &other) {
  copyFrom(other);
}
UserData &UserData::operator=(const UserData &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }
  return *this;
}
UserData::~UserData() {
  free();
}
User *UserData::getUser() const {
  return user;
}
void UserData::addActivity(Activity *activity) {
  activities.push_back(activity);
}
void UserData::removeActivity(size_t index) {
  activities.erase(activities.begin() + index);
}
Activity *UserData::getActivity(size_t index) const {
  return activities[index];
}
std::ofstream &UserData::serialize(std::ofstream &ofs) const {

  if (user == nullptr) {
    throw std::runtime_error("User does not exist");
  }
  user->serialize(ofs);
  size_t length = activities.size();
  ofs.write(reinterpret_cast<const char*>(&length), sizeof(length));
  for (size_t i = 0; i < length; i++) {
    activities[i]->serialize(ofs);
  }
  ofs.write(reinterpret_cast<const char*>(&calorieBalance), sizeof(calorieBalance));

  return ofs;
}
std::ifstream &UserData::deserialize(std::ifstream &ifs) {
  user->deserialize(ifs);
  size_t length = activities.size();
  ifs.read(reinterpret_cast<char*>(&length), sizeof(length));
  for (size_t i = 0; i < length; i++) {
    activities[i]->deserialize(ifs);
  }
  ifs.read(reinterpret_cast<char*>(&calorieBalance), sizeof(calorieBalance));
  return ifs;
}

void UserData::copyFrom(const UserData &other) {
  *this->user = *other.user;
  this->calorieBalance = other.calorieBalance;
  size_t size = other.activities.size();
  for (size_t i = 0; i < size; i++) {
    *this->activities[i] = *other.activities[i];
  }

}
void UserData::free() {
  for (size_t i = 0; i < this->activities.size(); i++) {
    delete this->activities[i];
  }
  delete this->user;
}