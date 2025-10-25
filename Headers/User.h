#pragma once
#include <string>
typedef unsigned long long size_t;

enum class Gender : bool {
  male,
  female
};

enum class ActivityLevel {
  sitting_work,
  light_activity,
  medium_activity,
  active_work,
  very_active
};

enum class Goal{
  lose_weight,
  keep_weight,
  gain_weight
};

class User {
  std::string name;
  std::string password;
  static size_t ID;

  size_t age = 0;
  size_t weight = 0;
  size_t height = 0;

  bool hasPremium = false;

  Goal goal = Goal::keep_weight;
  ActivityLevel activityLevel = ActivityLevel::medium_activity;
  Gender gender = Gender::male;

public:

  User();
  const std::string& getName() const;

  size_t getWeight() const;
  size_t getHeight() const;
  size_t getAge() const;
  size_t getID() const;

  bool isPremium() const;

  const Gender& getGender() const;
  const ActivityLevel& getActivityLevel() const;
  const Goal& getGoal() const;

  bool isPasswordCorrect(const std::string& password) const;
  std::ofstream& serialize(std::ofstream& os) const;
  std::ifstream& deserialize(std::ifstream& ifs);
};