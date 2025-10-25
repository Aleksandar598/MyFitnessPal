#include "../Activity.h"
const ActivityType* Activity::getActivityType() const {
  return &this->activityType;
}
unsigned long long Activity::getCalories() const {
  return this->calories;
}
void Activity::setCalories(unsigned long long calories) {
  this->calories = calories;
}
void Activity::setActivityType(const ActivityType &activityType) {
  this->activityType = activityType;
}