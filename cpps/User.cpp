#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/User.h"
#include <fstream>

const std::string &User::getName() const {
  return this->name;
}
size_t User::getWeight() const {
  return this->weight;
}
size_t User::getHeight() const {
  return this->height;
}
size_t User::getAge() const {
  return this->age;
}
bool User::isPremium() const {
  return this->hasPremium;
}
const Gender &User::getGender() const {
  return this->gender;
}
const ActivityLevel &User::getActivityLevel() const {
  return this->activityLevel;
}
const Goal &User::getGoal() const {
  return this->goal;
}
std::ofstream &User::serialize(std::ofstream &os) const {
  long long length = name.length();
  os.write(reinterpret_cast<const char *>(&length), sizeof(length));
  os.write(name.data(), length);
  os.write(reinterpret_cast<const char*>(&age), sizeof(age));
  os.write(reinterpret_cast<const char*>(&height), sizeof(height));
  os.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
  os.write(reinterpret_cast<const char*>(&gender), sizeof(gender));
  os.write(reinterpret_cast<const char*>(&activityLevel), sizeof(activityLevel));
  os.write(reinterpret_cast<const char*>(&goal), sizeof(goal));

  os.write(reinterpret_cast<const char*>(&hasPremium), sizeof(hasPremium));

  return os;
}
std::ifstream &User::deserialize(std::ifstream &is) {
  long long length;
  is.read(reinterpret_cast<char *>(&length), sizeof(length));
  name.resize(length);

  is.read(reinterpret_cast<char *>(&name), sizeof(name));
  is.read(reinterpret_cast<char *>(&age), sizeof(age));
  is.read(reinterpret_cast<char *>(&height), sizeof(height));
  is.read(reinterpret_cast<char *>(&weight), sizeof(weight));
  is.read(reinterpret_cast<char *>(&gender), sizeof(gender));
  is.read(reinterpret_cast<char *>(&activityLevel), sizeof(activityLevel));
  is.read(reinterpret_cast<char *>(&goal), sizeof(goal));
  is.read(reinterpret_cast<char *>(&hasPremium), sizeof(hasPremium));

  return is;

}