#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

class Utils
{
private:
    static int currentDate;

public:
    static string hashPassword(string password);
    static int getCurrentDate();
    static void setCurrentDate(int date);
    static void advanceDate(int days);
    static int daysBetween(int date1, int date2);
    static string dateToString(int date);
    static int stringToDate(string dateStr);
    static bool isValidDate(int date);
    static int addDays(int date, int days);
};

#endif
