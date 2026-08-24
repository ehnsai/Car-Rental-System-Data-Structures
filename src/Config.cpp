#include "Config.h"
#include <fstream>

using namespace std;

Config::Config()
{
    fineRatePerDay = 50000;
    maxRentalDays = 14;
    maxReservationsPerUser = 3;
    reservationHoldDays = 3;
    debtLimitForBlock = 1000000;
}

void Config::setFineRate(int rate)
{
    fineRatePerDay = rate;
}

int Config::getFineRate()
{
    return fineRatePerDay;
}

void Config::setMaxRentalDays(int days)
{
    maxRentalDays = days;
}

int Config::getMaxRentalDays()
{
    return maxRentalDays;
}

void Config::setMaxReservations(int max)
{
    maxReservationsPerUser = max;
}

int Config::getMaxReservations()
{
    return maxReservationsPerUser;
}

void Config::setReservationHoldDays(int days)
{
    reservationHoldDays = days;
}

int Config::getReservationHoldDays()
{
    return reservationHoldDays;
}

void Config::setDebtLimit(int limit)
{
    debtLimitForBlock = limit;
}

int Config::getDebtLimit()
{
    return debtLimitForBlock;
}

void Config::loadFromFile()
{
    ifstream file("config.dat");
    if (file.is_open())
    {
        file >> fineRatePerDay;
        file >> maxRentalDays;
        file >> maxReservationsPerUser;
        file >> reservationHoldDays;
        file >> debtLimitForBlock;
        file.close();
    }
}

void Config::saveToFile()
{
    ofstream file("config.dat");
    if (file.is_open())
    {
        file << fineRatePerDay << endl;
        file << maxRentalDays << endl;
        file << maxReservationsPerUser << endl;
        file << reservationHoldDays << endl;
        file << debtLimitForBlock << endl;
        file.close();
    }
}
