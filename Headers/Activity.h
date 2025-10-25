#pragma once
#include <string>
enum class ActivityType : bool {
  workout,
  meal
};
class Activity {
  std::string name;
  unsigned long long calories = 0;
  ActivityType activityType = ActivityType::workout;

public:

  const ActivityType* getActivityType() const;
  unsigned long long getCalories() const;
  std::string getName() const;

  void setName(const std::string &name);
  void setCalories(unsigned long long calories);
  void setActivityType(const ActivityType& activityType);

  std::ofstream& serialize(std::ofstream& ofs);
  std::ifstream& deserialize(std::ifstream& ifs);
};



