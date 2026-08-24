#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum UserRole
{
    ROLE_GUEST,
    ROLE_CUSTOMER,
    ROLE_STAFF,
    ROLE_MAINTENANCE,
    ROLE_MANAGER
};

class User
{
private:
    int userId;
    string username;
    string passwordHash;
    string fullName;
    string phoneNumber;
    UserRole role;
    bool isBlocked;
    int totalDebt;
    int reservationCount;

public:
    User();
    User(int id, string uname, string passHash, string name, string phone, UserRole r);

    int getUserId();
    void setUserId(int id);

    string getUsername();
    void setUsername(string uname);

    string getPasswordHash();
    void setPasswordHash(string hash);

    string getFullName();
    void setFullName(string name);

    string getPhoneNumber();
    void setPhoneNumber(string phone);

    UserRole getRole();
    void setRole(UserRole r);

    bool getIsBlocked();
    void setIsBlocked(bool blocked);

    int getTotalDebt();
    void setTotalDebt(int debt);
    void addDebt(int amount);

    int getReservationCount();
    void setReservationCount(int count);
    void incrementReservation();
    void decrementReservation();

    string getRoleString();
};

#endif