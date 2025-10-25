#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/FitnessContainer.h"
#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/UserData.h"
#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/User.h"
#include "C:\Users\alexx\CLionProjects\MyFitnessPal\Headers\UserFactory.h"
#include <stdexcept>
#include <fstream>
FitnessContainer::FitnessContainer(const FitnessContainer &other) {
  copyFrom(other);
}
FitnessContainer& FitnessContainer::operator=(const FitnessContainer &other) {
  if (this != &other) {
    free();
    copyFrom(other);
  }
  return *this;
}
FitnessContainer::~FitnessContainer() {
  free();
}
void FitnessContainer::addUserData(UserData *user) {
  if (user == nullptr) throw std::invalid_argument("FitnessContainer::addUserData: user is null");
  this->profiles.push_back(user);
}
void FitnessContainer::deleteCurrentUserData() {
  if (currentUser == nullptr) throw std::invalid_argument("User is not logged in");
  size_t ID = this->currentUser->getUser()->getID();
  size_t size = this->profiles.size();
  for (size_t i = 0; i < size; i++) {
    if (this->profiles[i]->getUser()->getID() == ID) {
      this->profiles.erase(this->profiles.begin() + i);
      break;
    }
  }
  delete this->currentUser;
  this->currentUser = nullptr;
}
User *FitnessContainer::getCurrentUserData() {
  if (currentUser == nullptr) throw std::invalid_argument("User is not logged in");
  return this->currentUser->getUser();
}
bool FitnessContainer::isLoggedIn() {
  if (currentUser == nullptr) return false;
  return true;
}
void FitnessContainer::LogIn(const std::string &name,const std::string &password) {
  if (currentUser != nullptr) throw std::invalid_argument("User is already logged in");
  size_t size = this->profiles.size();
  for (size_t i = 0; i < size; i++) {
    if (this->profiles[i]->getUser()->getName() == name) {
      if (this->profiles[i]->getUser()->isPasswordCorrect(password)) {
        currentUser = this->profiles[i];
        return;
      }
      else throw std::invalid_argument("Wrong passowrd!");
    }
  }
  throw std::runtime_error("User not found");
}
std::ofstream &FitnessContainer::serialize(std::ofstream &os) const {
    size_t size= profiles.size();
    os.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (size_t i = 0; i < size; i++) {
        profiles[i]->serialize(os);
    }
  return os;
}
std::ifstream& FitnessContainer::deserialize(std::ifstream& is) {
  size_t size = 0;
  is.read(reinterpret_cast<char*>(&size), sizeof(size));

  // Изчистваме старото съдържание
  free();

  profiles.reserve(size);
  for (size_t i = 0; i < size; i++) {
    UserData* data = new UserData();
    data->deserialize(is);
    profiles.push_back(data);
  }

  currentUser = nullptr;
  return is;
}
void FitnessContainer::copyFrom(const FitnessContainer& other) {
  free(); // важно!

  long long searchID = (other.currentUser == nullptr)
                       ? -1
                       : other.currentUser->getUser()->getID();

  size_t indexAt = 0;
  profiles.reserve(other.profiles.size());

  for (size_t i = 0; i < other.profiles.size(); i++) {
    UserData* copy = new UserData(*other.profiles[i]);
    profiles.push_back(copy);
    if (other.profiles[i]->getUser()->getID() == searchID)
      indexAt = i;
  }

  currentUser = (searchID != -1) ? profiles[indexAt] : nullptr;
}

void FitnessContainer::free() {
  size_t size= profiles.size();
  for (size_t i = 0; i < size; i++) {
    delete profiles[i];
    profiles[i] = nullptr;
  }
}