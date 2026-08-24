#include "Utils.h"
#include <sstream>

using namespace std;

int Utils::currentDate = 14030315;

string Utils::hashPassword(string password)
{
    unsigned long hash = 5381;
    for (int i = 0; i < password.length(); i++)
    {
        hash = ((hash << 5) + hash) + password[i];
    }

    stringstream ss;
    ss << hash;

    return ss.str();
}

int Utils::getCurrentDate()
{
    return currentDate;
}

void Utils::setCurrentDate(int date)
{
    currentDate = date;
}

void Utils::advanceDate(int days)
{
    int year = currentDate / 10000;
    int month = (currentDate / 100) % 100;
    int day = currentDate % 100;

    day = day + days;

    while (day > 30)
    {
        day = day - 30;
        month++;

        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    currentDate = year * 10000 + month * 100 + day;
}

int Utils::daysBetween(int date1, int date2)
{
    int year1 = date1 / 10000;
    int month1 = (date1 / 100) % 100;
    int day1 = date1 % 100;

    int year2 = date2 / 10000;
    int month2 = (date2 / 100) % 100;
    int day2 = date2 % 100;

    int totalDays1 = year1 * 365 + month1 * 30 + day1;
    int totalDays2 = year2 * 365 + month2 * 30 + day2;

    return totalDays2 - totalDays1;
}

string Utils::dateToString(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    stringstream ss;
    ss << year << "/" << month << "/" << day;

    return ss.str();
}

int Utils::stringToDate(string dateStr)
{
    int year, month, day;
    char slash;

    stringstream ss(dateStr);
    ss >> year >> slash >> month >> slash >> day;

    return year * 10000 + month * 100 + day;
}

bool Utils::isValidDate(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    if (year < 1400 || year > 1450)
    {
        return false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > 31)
    {
        return false;
    }

    return true;
}

int Utils::addDays(int date, int days)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    day = day + days;

    while (day > 30)
    {
        day = day - 30;
        month++;

        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    return year * 10000 + month * 100 + day;
}