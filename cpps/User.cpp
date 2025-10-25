#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/User.h"
#include <fstream>

size_t User::ID = 0;

User::User(){
  ++ID;
}

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
size_t User::getID() const {
  return this->ID;
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
bool User::isPasswordCorrect(const std::string &password) const {
  if (password == this->password) return true;
  return false;
}
std::ofstream &User::serialize(std::ofstream &ofs) const {
  long long length = name.length();
  ofs.write(reinterpret_cast<char *>(&ID), sizeof(ID));
  ofs.write(reinterpret_cast<const char *>(&length), sizeof(length));
  ofs.write(name.data(), length);
  ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));
  ofs.write(reinterpret_cast<const char*>(&height), sizeof(height));
  ofs.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
  ofs.write(reinterpret_cast<const char*>(&gender), sizeof(gender));
  ofs.write(reinterpret_cast<const char*>(&activityLevel), sizeof(activityLevel));
  ofs.write(reinterpret_cast<const char*>(&goal), sizeof(goal));

  ofs.write(reinterpret_cast<const char*>(&hasPremium), sizeof(hasPremium));

  return ofs;
}
std::ifstream &User::deserialize(std::ifstream &ifs) {
  long long length;
  ifs.read(reinterpret_cast<char *>(&ID), sizeof(ID));
  ifs.read(reinterpret_cast<char *>(&length), sizeof(length));
  name.resize(length);

  ifs.read(reinterpret_cast<char *>(&name), sizeof(name));
  ifs.read(reinterpret_cast<char *>(&age), sizeof(age));
  ifs.read(reinterpret_cast<char *>(&height), sizeof(height));
  ifs.read(reinterpret_cast<char *>(&weight), sizeof(weight));
  ifs.read(reinterpret_cast<char *>(&gender), sizeof(gender));
  ifs.read(reinterpret_cast<char *>(&activityLevel), sizeof(activityLevel));
  ifs.read(reinterpret_cast<char *>(&goal), sizeof(goal));
  ifs.read(reinterpret_cast<char *>(&hasPremium), sizeof(hasPremium));

  return ifs;

}