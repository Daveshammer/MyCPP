#include <iostream>
#include <memory>
#include <optional>
using namespace std;

class User {
private:
    string name;
    optional<string> nickname;
    optional<int> age;
public:
    User(string name, optional<string> nickname, optional<int> age) : name(name), nickname(nickname), age(age) {}

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "name: " << user.name; 
        if (user.nickname.has_value()) {
            os << ", nickname: " << user.nickname.value();
        }
        if (user.age.has_value()) {
            os << ", age: " << user.age.value();
        }
        return os;
    }
};

int main()
{
    User user1("Tom", "Tommy", 20);
    User user2("Jerry", nullopt, nullopt);
    cout << user1 << endl; // name: Tom, nickname: Tommy, age: 20
    cout << user2 << endl; // name: Jerry
}