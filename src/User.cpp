#include "User.h"

using namespace std;

User::User()
{
    userId = 0;
    username = "";
    passwordHash = "";
    fullName = "";
    phoneNumber = "";
    role = ROLE_GUEST;
    isBlocked = false;
    totalDebt = 0;
    reservationCount = 0;
}

User::User(int id, string uname, string passHash, string name, string phone, UserRole r)
{
    userId = id;
    username = uname;
    passwordHash = passHash;
    fullName = name;
    phoneNumber = phone;
    role = r;
    isBlocked = false;
    totalDebt = 0;
    reservationCount = 0;
}

int User::getUserId()
{
    return userId;
}

void User::setUserId(int id)
{
    userId = id;
}

string User::getUsername()
{
    return username;
}

void User::setUsername(string uname)
{
    username = uname;
}

string User::getPasswordHash()
{
    return passwordHash;
}

void User::setPasswordHash(string hash)
{
    passwordHash = hash;
}

string User::getFullName()
{
    return fullName;
}

void User::setFullName(string name)
{
    fullName = name;
}

string User::getPhoneNumber()
{
    return phoneNumber;
}

void User::setPhoneNumber(string phone)
{
    phoneNumber = phone;
}

UserRole User::getRole()
{
    return role;
}

void User::setRole(UserRole r)
{
    role = r;
}

bool User::getIsBlocked()
{
    return isBlocked;
}

void User::setIsBlocked(bool blocked)
{
    isBlocked = blocked;
}

int User::getTotalDebt()
{
    return totalDebt;
}

void User::setTotalDebt(int debt)
{
    totalDebt = debt;
}

void User::addDebt(int amount)
{
    totalDebt = totalDebt + amount;
}

int User::getReservationCount()
{
    return reservationCount;
}

void User::setReservationCount(int count)
{
    reservationCount = count;
}

void User::incrementReservation()
{
    reservationCount++;
}

void User::decrementReservation()
{
    if (reservationCount > 0)
    {
        reservationCount--;
    }
}

string User::getRoleString()
{
    if (role == ROLE_GUEST)
    {
        return "Guest";
    }
    else if (role == ROLE_CUSTOMER)
    {
        return "Customer";
    }
    else if (role == ROLE_STAFF)
    {
        return "Staff";
    }
    else if (role == ROLE_MAINTENANCE)
    {
        return "Maintenance";
    }
    else if (role == ROLE_MANAGER)
    {
        return "Manager";
    }

    return "Unknown";
}
