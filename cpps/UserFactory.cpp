#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/UserData.h"
#include "C:/Users/alexx/CLionProjects/MyFitnessPal/Headers/User.h"
#include "C:\Users\alexx\CLionProjects\MyFitnessPal\Headers\UserFactory.h"

UserData *UserFactory::createUser(const UserTypes &type) {
  switch (type) {
  case(UserTypes::user): return new UserData();
    default: return nullptr;
  }

}