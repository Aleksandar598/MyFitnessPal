
enum class UserTypes {
    user
};
class User;
class UserData;

class UserFactory {
public:
    static UserData* createUser(const UserTypes& type);
};
