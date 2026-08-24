#ifndef CAR_H
#define CAR_H

#include <string>
#include "DoublyLinkedList.h"

using namespace std;

enum CarStatus
{
    CAR_AVAILABLE,
    CAR_RESERVED,
    CAR_RENTED,
    CAR_MAINTENANCE
};

struct MaintenanceRecord
{
    int date;
    string description;
    int cost;
    int expectedEndDate;
};

class Car
{
private:
    int carId;
    string plateNumber;
    string brand;
    string model;
    string carType;
    int year;
    string color;
    int dailyPrice;
    CarStatus status;
    int totalIncome;
    int timesRented;
    int maintenanceEndDate;
    DoublyLinkedList<MaintenanceRecord> maintenanceHistory;

public:
    Car();
    Car(int id, string plate, string br, string mod, string type, int yr, string clr, int price);

    int getCarId();
    void setCarId(int id);

    string getPlateNumber();
    void setPlateNumber(string plate);

    string getBrand();
    void setBrand(string br);

    string getModel();
    void setModel(string mod);

    string getCarType();
    void setCarType(string type);

    int getYear();
    void setYear(int yr);

    string getColor();
    void setColor(string clr);

    int getDailyPrice();
    void setDailyPrice(int price);

    CarStatus getStatus();
    void setStatus(CarStatus s);

    int getTotalIncome();
    void setTotalIncome(int income);
    void addIncome(int amount);

    int getTimesRented();
    void setTimesRented(int times);
    void incrementRented();

    int getMaintenanceEndDate();
    void setMaintenanceEndDate(int date);

    void addMaintenanceRecord(MaintenanceRecord record);
    DoublyLinkedList<MaintenanceRecord>* getMaintenanceHistory();

    string getStatusString();
};

#endif