#include "C:\Users\alexx\CLionProjects\MyFitnessPal\Headers\Activity.h"
#include <fstream>

const ActivityType* Activity::getActivityType() const {
  return &this->activityType;
}
unsigned long long Activity::getCalories() const {
  return this->calories;
}
std::string Activity::getName() const {
  return this->name;
}
void Activity::setName(const std::string &name) {
  this->name = name;
}

void Activity::setCalories(unsigned long long calories) {
  this->calories = calories;
}
void Activity::setActivityType(const ActivityType &activityType) {
  this->activityType = activityType;
}
std::ofstream &Activity::serialize(std::ofstream &ofs) {
  size_t size = name.length();
  ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
  ofs.write(name.data(), size);
  ofs.write(reinterpret_cast<const char*>(&calories), sizeof(calories));
  ofs.write(reinterpret_cast<const char*>(&activityType), sizeof(activityType));
  return ofs;
}
std::ifstream &Activity::deserialize(std::ifstream &ifs) {
  size_t size;
  ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
  name.resize(size);
  ifs.read(name.data(), size);
  ifs.read(reinterpret_cast<char*>(&calories), sizeof(calories));
  ifs.read(reinterpret_cast<char*>(&activityType), sizeof(activityType));
  return ifs;
}