#pragma once

enum class ActivityType : bool {
  workout,
  meal
};
class Activity {
  unsigned long long calories = 0;
  ActivityType activityType = ActivityType::workout;

public:

  const ActivityType* getActivityType() const;
  unsigned long long getCalories() const;
  void setCalories(unsigned long long calories);
  void setActivityType(const ActivityType& activityType);
};


