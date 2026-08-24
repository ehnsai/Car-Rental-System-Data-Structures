#include "Car.h"

using namespace std;

Car::Car()
{
    carId = 0;
    plateNumber = "";
    brand = "";
    model = "";
    carType = "";
    year = 0;
    color = "";
    dailyPrice = 0;
    status = CAR_AVAILABLE;
    totalIncome = 0;
    timesRented = 0;
    maintenanceEndDate = 0;
}

Car::Car(int id, string plate, string br, string mod, string type, int yr, string clr, int price)
{
    carId = id;
    plateNumber = plate;
    brand = br;
    model = mod;
    carType = type;
    year = yr;
    color = clr;
    dailyPrice = price;
    status = CAR_AVAILABLE;
    totalIncome = 0;
    timesRented = 0;
    maintenanceEndDate = 0;
}

int Car::getCarId()
{
    return carId;
}

void Car::setCarId(int id)
{
    carId = id;
}

string Car::getPlateNumber()
{
    return plateNumber;
}

void Car::setPlateNumber(string plate)
{
    plateNumber = plate;
}

string Car::getBrand()
{
    return brand;
}

void Car::setBrand(string br)
{
    brand = br;
}

string Car::getModel()
{
    return model;
}

void Car::setModel(string mod)
{
    model = mod;
}

string Car::getCarType()
{
    return carType;
}

void Car::setCarType(string type)
{
    carType = type;
}

int Car::getYear()
{
    return year;
}

void Car::setYear(int yr)
{
    year = yr;
}

string Car::getColor()
{
    return color;
}

void Car::setColor(string clr)
{
    color = clr;
}

int Car::getDailyPrice()
{
    return dailyPrice;
}

void Car::setDailyPrice(int price)
{
    dailyPrice = price;
}

CarStatus Car::getStatus()
{
    return status;
}

void Car::setStatus(CarStatus s)
{
    status = s;
}

int Car::getTotalIncome()
{
    return totalIncome;
}

void Car::setTotalIncome(int income)
{
    totalIncome = income;
}

void Car::addIncome(int amount)
{
    totalIncome = totalIncome + amount;
}

int Car::getTimesRented()
{
    return timesRented;
}

void Car::setTimesRented(int times)
{
    timesRented = times;
}

void Car::incrementRented()
{
    timesRented++;
}

int Car::getMaintenanceEndDate()
{
    return maintenanceEndDate;
}

void Car::setMaintenanceEndDate(int date)
{
    maintenanceEndDate = date;
}

void Car::addMaintenanceRecord(MaintenanceRecord record)
{
    maintenanceHistory.addToEnd(record);
}

DoublyLinkedList<MaintenanceRecord>* Car::getMaintenanceHistory()
{
    return &maintenanceHistory;
}

string Car::getStatusString()
{
    if (status == CAR_AVAILABLE)
    {
        return "Available";
    }
    else if (status == CAR_RESERVED)
    {
        return "Reserved";
    }
    else if (status == CAR_RENTED)
    {
        return "Rented";
    }
    else if (status == CAR_MAINTENANCE)
    {
        return "Maintenance";
    }

    return "Unknown";
}
