#ifndef CARRENTALSYSTEM_H
#define CARRENTALSYSTEM_H

#include <string>
#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "PriorityQueue.h"
#include "Queue.h"
#include "User.h"
#include "Car.h"
#include "Reservation.h"
#include "Rental.h"
#include "Config.h"
#include "Utils.h"

using namespace std;

class CarRentalSystem
{
private:
    DoublyLinkedList<Car> carList;
    SinglyLinkedList<User> userList;
    AVLTree<int> carNameIndex;
    HashTable<int> usernameTable;
    DoublyLinkedList<Reservation> reservationList;
    DoublyLinkedList<Rental> rentalList;
    Queue<int> returnQueue;

    Config config;

    int nextUserId;
    int nextCarId;
    int nextReservationId;
    int nextRentalId;

    User* currentUser;

    void loadData();
    void saveData();

public:
    CarRentalSystem();
    ~CarRentalSystem();

    void checkAndUpdateStatuses();
    void updateOverdueRentals();
    void updateMaintenanceCars();
    void checkAndBlockDebtors();
    void checkAndUnblockDebtors();

    bool registerUser(string username, string password, string fullName, string phone);
    User* loginUser(string username, string password);
    void logoutUser();
    User* getCurrentUser();

    bool addCar(string plate, string brand, string model, string type, int year, string color, int price);
    bool updateCar(int carId, string plate, string brand, string model, string type, int year, string color, int price);
    Car* getCarById(int carId);
    Car* getCarByPlate(string plate);
    DoublyLinkedList<Car>* getAllCars();
    DoublyLinkedList<Car> searchCars(string brand, string type, int minPrice, int maxPrice);
    DoublyLinkedList<Car> getAvailableCars();
    DoublyLinkedList<Car> getCarsForReservation();
    DoublyLinkedList<Rental> getOverdueRentals();

    bool createReservation(int carId, int startDate, int endDate);
    bool cancelReservation(int reservationId);
    bool hasOverlappingReservation(int carId, int startDate, int endDate);
    DoublyLinkedList<Reservation> getUserReservations(int userId);
    Reservation* getReservationById(int reservationId);
    PriorityQueue<Reservation>* getCarReservationQueue(int carId);

    bool convertToRental(int reservationId);
    bool returnCar(int rentalId, bool needsMaintenance, int maintenanceEndDate);
    int calculateFine(int rentalId);
    bool extendRental(int rentalId, int newEndDate);
    DoublyLinkedList<Rental> getUserRentals(int userId);
    Rental* getRentalById(int rentalId);
    Rental* getActiveRentalByCarId(int carId);

    bool processPayment(int userId, int amount);
    bool addMaintenanceRecord(int carId, int date, string description, int cost, int endDate);
    bool setCarMaintenance(int carId, int endDate);
    bool setCarAvailable(int carId);

    bool blockUser(int userId);
    bool unblockUser(int userId);
    User* getUserById(int userId);
    User* getUserByUsername(string username);
    SinglyLinkedList<User>* getAllUsers();
    SinglyLinkedList<User> getBlockedUsers();
    SinglyLinkedList<User> getUsersWithDebt();

    void processReservationQueue(int carId);
    void addToReturnQueue(int rentalId);
    int processReturnQueue();

    int getTotalIncome();
    int getTotalFines();
    double getFleetUsageRate();
    bool exportReport(string filename);
    bool exportData(string filename);
    bool importData(string filename);

    Config* getConfig();
};

#endif