#include "CarRentalSystem.h"
#include <fstream>
#include <sstream>

using namespace std;

CarRentalSystem::CarRentalSystem()
{
    nextUserId = 1;
    nextCarId = 1;
    nextReservationId = 1;
    nextRentalId = 1;
    currentUser = nullptr;

    config.loadFromFile();
    loadData();

    if (usernameTable.search("admin") == nullptr)
    {
        User admin(nextUserId, "admin", Utils::hashPassword("ADMIN"), "System Admin", "09852147562", ROLE_MANAGER);
        userList.addToEnd(admin);
        usernameTable.insert("admin", nextUserId);
        nextUserId++;
    }

    if (usernameTable.search("staff") == nullptr)
    {
        User staff(nextUserId, "staff", Utils::hashPassword("STAFF"), "Staff Member", "09123654884", ROLE_STAFF);
        userList.addToEnd(staff);
        usernameTable.insert("staff", nextUserId);
        nextUserId++;
    }

    if (usernameTable.search("maint") == nullptr)
    {
        User maint(nextUserId, "maint", Utils::hashPassword("MAINT"), "Maintenance Worker", "09412563985", ROLE_MAINTENANCE);
        userList.addToEnd(maint);
        usernameTable.insert("maint", nextUserId);
        nextUserId++;
    }
}

CarRentalSystem::~CarRentalSystem()
{
    saveData();
    config.saveToFile();
}

void CarRentalSystem::checkAndUpdateStatuses()
{
    updateOverdueRentals();
    updateMaintenanceCars();
    checkAndBlockDebtors();
    checkAndUnblockDebtors();
}

void CarRentalSystem::updateOverdueRentals()
{
    int today = Utils::getCurrentDate();

    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);

        if (rental->getStatus() == RENTAL_ACTIVE)
        {
            if (today > rental->getExpectedReturnDate())
            {
                rental->setStatus(RENTAL_OVERDUE);
            }
        }
    }
    saveData();
}

void CarRentalSystem::updateMaintenanceCars()
{
    int today = Utils::getCurrentDate();

    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);

        if (car->getStatus() == CAR_MAINTENANCE)
        {
            int endDate = car->getMaintenanceEndDate();

            if (endDate > 0 && today >= endDate)
            {
                car->setStatus(CAR_AVAILABLE);
                car->setMaintenanceEndDate(0);
                processReservationQueue(car->getCarId());
            }
        }
    }
    saveData();
}

void CarRentalSystem::checkAndBlockDebtors()
{
    int debtLimit = config.getDebtLimit();

    for (int i = 0; i < userList.getCount(); i++)
    {
        User* user = userList.getByIndex(i);

        if (user->getRole() == ROLE_CUSTOMER)
        {
            if (user->getTotalDebt() >= debtLimit && !user->getIsBlocked())
            {
                user->setIsBlocked(true);
            }
        }
    }
    saveData();
}

void CarRentalSystem::checkAndUnblockDebtors()
{
    int debtLimit = config.getDebtLimit();

    for (int i = 0; i < userList.getCount(); i++)
    {
        User* user = userList.getByIndex(i);

        if (user->getRole() == ROLE_CUSTOMER)
        {
            if (user->getTotalDebt() < debtLimit && user->getIsBlocked())
            {
                user->setIsBlocked(false);
            }
        }
    }
    saveData();
}

void CarRentalSystem::loadData()
{
    ifstream carFile("cars.dat");
    if (carFile.is_open())
    {
        int id;
        string plate, brand, model, type, color;
        int year, price, status, income, times, maintEnd;

        while (carFile >> id)
        {
            carFile >> plate >> brand >> model >> type >> year >> color >> price >> status >> income >> times >> maintEnd;

            Car car(id, plate, brand, model, type, year, color, price);
            car.setStatus((CarStatus)status);
            car.setTotalIncome(income);
            car.setTimesRented(times);
            car.setMaintenanceEndDate(maintEnd);

            carList.addToEnd(car);

            string searchKey = brand + "_" + model;
            carNameIndex.insert(searchKey, id);

            if (id >= nextCarId)
            {
                nextCarId = id + 1;
            }
        }
        carFile.close();
    }

    ifstream userFile("users.dat");
    if (userFile.is_open())
    {
        int id;
        string uname, passHash, fullName, phone;
        int role;
        bool blocked;
        int debt, resCount;

        while (userFile >> id)
        {
            userFile >> uname >> passHash >> fullName >> phone >> role >> blocked >> debt >> resCount;

            for (int i = 0; i < fullName.length(); i++)
            {
                if (fullName[i] == '_')
                {
                    fullName[i] = ' ';
                }
            }
            User user(id, uname, passHash, fullName, phone, (UserRole)role);
            user.setIsBlocked(blocked);
            user.setTotalDebt(debt);
            user.setReservationCount(resCount);
            userList.addToEnd(user);
            usernameTable.insert(uname, id);

            if (id >= nextUserId)
            {
                nextUserId = id + 1;
            }
        }
        userFile.close();
    }

    ifstream resFile("reservations.dat");
    if (resFile.is_open())
    {
        int id, carId, userId, start, end, created, status, priority;

        while (resFile >> id)
        {
            resFile >> carId >> userId >> start >> end >> created >> status >> priority;

            Reservation res(id, carId, userId, start, end, created);
            res.setStatus((ReservationStatus)status);
            res.setPriority(priority);

            reservationList.addToEnd(res);

            if (id >= nextReservationId)
            {
                nextReservationId = id + 1;
            }
        }
        resFile.close();
    }

    ifstream rentFile("rentals.dat");
    if (rentFile.is_open())
    {
        int id, carId, userId, resId, start, expected, actual, cost, fine;
        bool paid;
        int status;

        while (rentFile >> id)
        {
            rentFile >> carId >> userId >> resId >> start >> expected >> actual >> cost >> fine >> paid >> status;

            Rental rental(id, carId, userId, resId, start, expected);
            rental.setActualReturnDate(actual);
            rental.setTotalCost(cost);
            rental.setFineAmount(fine);
            rental.setIsPaid(paid);
            rental.setStatus((RentalStatus)status);

            rentalList.addToEnd(rental);

            if (id >= nextRentalId)
            {
                nextRentalId = id + 1;
            }
        }
        rentFile.close();
    }

    ifstream dateFile("currentdate.dat");
    if (dateFile.is_open())
    {
        int savedDate;
        dateFile >> savedDate;
        Utils::setCurrentDate(savedDate);
        dateFile.close();
    }
}

void CarRentalSystem::saveData()
{
    ofstream carFile("cars.dat");
    if (carFile.is_open())
    {
        for (int i = 0; i < carList.getCount(); i++)
        {
            Car* car = carList.getByIndex(i);
            carFile << car->getCarId() << " ";
            carFile << car->getPlateNumber() << " ";
            carFile << car->getBrand() << " ";
            carFile << car->getModel() << " ";
            carFile << car->getCarType() << " ";
            carFile << car->getYear() << " ";
            carFile << car->getColor() << " ";
            carFile << car->getDailyPrice() << " ";
            carFile << car->getStatus() << " ";
            carFile << car->getTotalIncome() << " ";
            carFile << car->getTimesRented() << " ";
            carFile << car->getMaintenanceEndDate() << endl;
        }

        carFile.close();
    }
    ofstream userFile("users.dat");
    if (userFile.is_open())
    {
        for (int i = 0; i < userList.getCount(); i++)
        {
            User* user = userList.getByIndex(i);

            string fullName = user->getFullName();
            for (int j = 0; j < fullName.length(); j++)
            {
                if (fullName[j] == ' ')
                {
                    fullName[j] = '_';
                }
            }
            userFile << user->getUserId() << " ";
            userFile << user->getUsername() << " ";
            userFile << user->getPasswordHash() << " ";
            userFile << fullName << " ";
            userFile << user->getPhoneNumber() << " ";
            userFile << user->getRole() << " ";
            userFile << user->getIsBlocked() << " ";
            userFile << user->getTotalDebt() << " ";
            userFile << user->getReservationCount() << endl;
        }
        userFile.close();
    }

    ofstream resFile("reservations.dat");
    if (resFile.is_open())
    {
        for (int i = 0; i < reservationList.getCount(); i++)
        {
            Reservation* res = reservationList.getByIndex(i);
            resFile << res->getReservationId() << " ";
            resFile << res->getCarId() << " ";
            resFile << res->getUserId() << " ";
            resFile << res->getStartDate() << " ";
            resFile << res->getEndDate() << " ";
            resFile << res->getCreatedDate() << " ";
            resFile << res->getStatus() << " ";
            resFile << res->getPriority() << endl;
        }
        resFile.close();
    }
    ofstream rentFile("rentals.dat");
    if (rentFile.is_open())
    {
        for (int i = 0; i < rentalList.getCount(); i++)
        {
            Rental* rental = rentalList.getByIndex(i);
            rentFile << rental->getRentalId() << " ";
            rentFile << rental->getCarId() << " ";
            rentFile << rental->getUserId() << " ";
            rentFile << rental->getReservationId() << " ";
            rentFile << rental->getStartDate() << " ";
            rentFile << rental->getExpectedReturnDate() << " ";
            rentFile << rental->getActualReturnDate() << " ";
            rentFile << rental->getTotalCost() << " ";
            rentFile << rental->getFineAmount() << " ";
            rentFile << rental->getIsPaid() << " ";
            rentFile << rental->getStatus() << endl;
        }
        rentFile.close();
    }
    ofstream dateFile("currentdate.dat");
    if (dateFile.is_open())
    {
        dateFile << Utils::getCurrentDate();
        dateFile.close();
    }
}

bool CarRentalSystem::registerUser(string username, string password, string fullName, string phone)
{
    if (usernameTable.exists(username))
    {
        return false;
    }
    string passHash = Utils::hashPassword(password);
    User newUser(nextUserId, username, passHash, fullName, phone, ROLE_CUSTOMER);
    userList.addToEnd(newUser);
    usernameTable.insert(username, nextUserId);
    nextUserId++;
    saveData();
    return true;
}

User* CarRentalSystem::loginUser(string username, string password)
{
    int* userIdPtr = usernameTable.search(username);

    if (userIdPtr == nullptr)
    {
        return nullptr;
    }

    int userId = *userIdPtr;

    for (int i = 0; i < userList.getCount(); i++)
    {
        User* user = userList.getByIndex(i);

        if (user->getUserId() == userId)
        {
            string passHash = Utils::hashPassword(password);

            if (user->getPasswordHash() == passHash)
            {
                currentUser = user;

                return user;
            }

            return nullptr;
        }
    }

    return nullptr;
}

void CarRentalSystem::logoutUser()
{
    currentUser = nullptr;
}

User* CarRentalSystem::getCurrentUser()
{
    return currentUser;
}

bool CarRentalSystem::addCar(string plate, string brand, string model, string type, int year, string color, int price)
{
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        if (car->getPlateNumber() == plate)
        {
            return false;
        }
    }
    Car newCar(nextCarId, plate, brand, model, type, year, color, price);
    carList.addToEnd(newCar);
    string searchKey = brand + "_" + model;
    carNameIndex.insert(searchKey, nextCarId);
    nextCarId++;
    saveData();
    return true;
}

bool CarRentalSystem::updateCar(int carId, string plate, string brand, string model, string type, int year, string color, int price)
{
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        if (car->getCarId() == carId)
        {
            car->setPlateNumber(plate);
            car->setBrand(brand);
            car->setModel(model);
            car->setCarType(type);
            car->setYear(year);
            car->setColor(color);
            car->setDailyPrice(price);
            saveData();
            return true;
        }
    }
    return false;
}

Car* CarRentalSystem::getCarById(int carId)
{
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        if (car->getCarId() == carId)
        {
            return car;
        }
    }
    return nullptr;
}

Car* CarRentalSystem::getCarByPlate(string plate)
{
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        if (car->getPlateNumber() == plate)
        {
            return car;
        }
    }
    return nullptr;
}

DoublyLinkedList<Car>* CarRentalSystem::getAllCars()
{
    return &carList;
}

DoublyLinkedList<Car> CarRentalSystem::searchCars(string brand, string type, int minPrice, int maxPrice)
{
    DoublyLinkedList<Car> results;

    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        bool match = true;

        if (brand != "" && car->getBrand() != brand)
        {
            match = false;
        }

        if (type != "" && car->getCarType() != type)
        {
            match = false;
        }

        if (minPrice > 0 && car->getDailyPrice() < minPrice)
        {
            match = false;
        }

        if (maxPrice > 0 && car->getDailyPrice() > maxPrice)
        {
            match = false;
        }

        if (match)
        {
            results.addToEnd(*car);
        }
    }

    return results;
}

DoublyLinkedList<Car> CarRentalSystem::getAvailableCars()
{
    DoublyLinkedList<Car> results;

    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        if (car->getStatus() == CAR_AVAILABLE)
        {
            results.addToEnd(*car);
        }
    }
    return results;
}

DoublyLinkedList<Car> CarRentalSystem::getCarsForReservation()
{
    DoublyLinkedList<Car> results;

    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);

        if (car->getStatus() != CAR_MAINTENANCE)
        {
            results.addToEnd(*car);
        }
    }
    return results;
}

DoublyLinkedList<Rental> CarRentalSystem::getOverdueRentals()
{
    DoublyLinkedList<Rental> results;
    int today = Utils::getCurrentDate();

    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);

        if (rental->getStatus() == RENTAL_ACTIVE || rental->getStatus() == RENTAL_OVERDUE)
        {
            if (today > rental->getExpectedReturnDate())
            {
                results.addToEnd(*rental);
            }
        }
    }
    return results;
}

bool CarRentalSystem::createReservation(int carId, int startDate, int endDate)
{
    if (currentUser == nullptr)
    {
        return false;
    }

    if (currentUser->getIsBlocked())
    {
        return false;
    }

    if (currentUser->getReservationCount() >= config.getMaxReservations())
    {
        return false;
    }

    Car* car = getCarById(carId);
    if (car == nullptr)
    {
        return false;
    }

    if (car->getStatus() == CAR_MAINTENANCE)
    {
        return false;
    }

    if (hasOverlappingReservation(carId, startDate, endDate))
    {
        return false;
    }

    int currentDate = Utils::getCurrentDate();
    Reservation newRes(nextReservationId, carId, currentUser->getUserId(), startDate, endDate, currentDate);
    newRes.setStatus(RESERVATION_CONFIRMED);
    reservationList.addToEnd(newRes);
    currentUser->incrementReservation();
    if (car->getStatus() == CAR_AVAILABLE)
    {
        car->setStatus(CAR_RESERVED);
    }
    nextReservationId++;
    saveData();
    return true;
}

bool CarRentalSystem::cancelReservation(int reservationId)
{
    for (int i = 0; i < reservationList.getCount(); i++)
    {
        Reservation* res = reservationList.getByIndex(i);

        if (res->getReservationId() == reservationId)
        {
            if (res->getStatus() == RESERVATION_CONFIRMED || res->getStatus() == RESERVATION_PENDING)
            {
                res->setStatus(RESERVATION_CANCELLED);
                User* user = getUserById(res->getUserId());
                if (user != nullptr)
                {
                    user->decrementReservation();
                }
                int carId = res->getCarId();
                Car* car = getCarById(carId);
                if (car != nullptr && car->getStatus() == CAR_RESERVED)
                {
                    bool hasOtherReservation = false;
                    for (int j = 0; j < reservationList.getCount(); j++)
                    {
                        Reservation* otherRes = reservationList.getByIndex(j);
                        if (otherRes->getCarId() == carId && otherRes->getReservationId() != reservationId)
                        {
                            if (otherRes->getStatus() == RESERVATION_CONFIRMED ||otherRes->getStatus() == RESERVATION_PENDING)
                            {
                                hasOtherReservation = true;
                                break;
                            }
                        }
                    }
                    if (!hasOtherReservation)
                    {
                        car->setStatus(CAR_AVAILABLE);
                    }
                }
                processReservationQueue(carId);
                saveData();
                return true;
            }
        }
    }
    return false;
}

bool CarRentalSystem::hasOverlappingReservation(int carId, int startDate, int endDate)
{
    for (int i = 0; i < reservationList.getCount(); i++)
    {
        Reservation* res = reservationList.getByIndex(i);

        if (res->getCarId() != carId)
        {
            continue;
        }
        if (res->getStatus() == RESERVATION_CANCELLED || res->getStatus() == RESERVATION_COMPLETED)
        {
            continue;
        }
        bool overlaps = !(endDate < res->getStartDate() || startDate > res->getEndDate());
        if (overlaps)
        {
            return true;
        }
    }
    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);

        if (rental->getCarId() != carId)
        {
            continue;
        }
        if (rental->getStatus() == RENTAL_RETURNED)
        {
            continue;
        }
        bool overlaps = !(endDate < rental->getStartDate() || startDate > rental->getExpectedReturnDate());
        if (overlaps)
        {
            return true;
        }
    }
    return false;
}

DoublyLinkedList<Reservation> CarRentalSystem::getUserReservations(int userId)
{
    DoublyLinkedList<Reservation> results;
    for (int i = 0; i < reservationList.getCount(); i++)
    {
        Reservation* res = reservationList.getByIndex(i);
        if (res->getUserId() == userId)
        {
            results.addToEnd(*res);
        }
    }
    return results;
}

Reservation* CarRentalSystem::getReservationById(int reservationId)
{
    for (int i = 0; i < reservationList.getCount(); i++)
    {
        Reservation* res = reservationList.getByIndex(i);
        if (res->getReservationId() == reservationId)
        {
            return res;
        }
    }
    return nullptr;
}

PriorityQueue<Reservation>* CarRentalSystem::getCarReservationQueue(int carId)
{
    PriorityQueue<Reservation>* queue = new PriorityQueue<Reservation>(100);

    for (int i = 0; i < reservationList.getCount(); i++)
    {
        Reservation* res = reservationList.getByIndex(i);

        if (res->getCarId() == carId && res->getStatus() == RESERVATION_PENDING)
        {
            queue->enqueue(*res, res->getPriority());
        }
    }
    return queue;
}

bool CarRentalSystem::convertToRental(int reservationId)
{
    Reservation* res = getReservationById(reservationId);
    if (res == nullptr)
    {
        return false;
    }
    if (res->getStatus() != RESERVATION_CONFIRMED)
    {
        return false;
    }
    Car* car = getCarById(res->getCarId());
    if (car == nullptr)
    {
        return false;
    }
    User* user = getUserById(res->getUserId());
    if (user == nullptr)
    {
        return false;
    }
    if (user->getIsBlocked())
    {
        return false;
    }
    Rental newRental(nextRentalId, res->getCarId(), res->getUserId(), reservationId,res->getStartDate(), res->getEndDate());
    int days = Utils::daysBetween(res->getStartDate(), res->getEndDate()) + 1;
    int cost = days * car->getDailyPrice();
    newRental.setTotalCost(cost);
    rentalList.addToEnd(newRental);
    res->setStatus(RESERVATION_COMPLETED);
    car->setStatus(CAR_RENTED);
    user->decrementReservation();
    nextRentalId++;
    saveData();
    return true;
}

bool CarRentalSystem::returnCar(int rentalId, bool needsMaintenance, int maintenanceEndDate)
{
    Rental* rental = getRentalById(rentalId);

    if (rental == nullptr)
    {
        return false;
    }

    if (rental->getStatus() == RENTAL_RETURNED)
    {
        return false;
    }

    Car* car = getCarById(rental->getCarId());

    if (car == nullptr)
    {
        return false;
    }

    User* user = getUserById(rental->getUserId());

    int currentDate = Utils::getCurrentDate();
    rental->setActualReturnDate(currentDate);
    rental->setStatus(RENTAL_RETURNED);

    int fine = calculateFine(rentalId);
    rental->setFineAmount(fine);

    if (user != nullptr)
    {
        int totalDebt = rental->getTotalCost() + fine;
        user->addDebt(totalDebt);
    }

    car->addIncome(rental->getTotalCost());
    car->incrementRented();

    if (needsMaintenance)
    {
        car->setStatus(CAR_MAINTENANCE);
        car->setMaintenanceEndDate(maintenanceEndDate);
    }
    else
    {
        car->setStatus(CAR_AVAILABLE);
        processReservationQueue(car->getCarId());
    }

    checkAndBlockDebtors();
    saveData();

    return true;
}
int CarRentalSystem::calculateFine(int rentalId)
{
    Rental* rental = getRentalById(rentalId);
    if (rental == nullptr)
    {
        return 0;
    }
    int currentDate = Utils::getCurrentDate();
    int expectedDate = rental->getExpectedReturnDate();
    if (currentDate <= expectedDate)
    {
        return 0;
    }
    int daysLate = Utils::daysBetween(expectedDate, currentDate);
    int fine = daysLate * config.getFineRate();
    return fine;
}

bool CarRentalSystem::extendRental(int rentalId, int newEndDate)
{
    Rental* rental = getRentalById(rentalId);
    if (rental == nullptr)
    {
        return false;
    }
    if (rental->getStatus() != RENTAL_ACTIVE)
    {
        return false;
    }
    int oldEndDate = rental->getExpectedReturnDate();
    if (hasOverlappingReservation(rental->getCarId(), oldEndDate + 1, newEndDate))
    {
        return false;
    }
    Car* car = getCarById(rental->getCarId());
    if (car == nullptr)
    {
        return false;
    }
    int extraDays = Utils::daysBetween(oldEndDate, newEndDate);
    int extraCost = extraDays * car->getDailyPrice();
    rental->setExpectedReturnDate(newEndDate);
    rental->setTotalCost(rental->getTotalCost() + extraCost);
    saveData();
    return true;
}

DoublyLinkedList<Rental> CarRentalSystem::getUserRentals(int userId)
{
    DoublyLinkedList<Rental> results;
    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);
        if (rental->getUserId() == userId)
        {
            results.addToEnd(*rental);
        }
    }
    return results;
}

Rental* CarRentalSystem::getRentalById(int rentalId)
{
    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);
        if (rental->getRentalId() == rentalId)
        {
            return rental;
        }
    }
    return nullptr;
}

Rental* CarRentalSystem::getActiveRentalByCarId(int carId)
{
    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);
        if (rental->getCarId() == carId &&
            (rental->getStatus() == RENTAL_ACTIVE || rental->getStatus() == RENTAL_OVERDUE))
        {
            return rental;
        }
    }
    return nullptr;
}

bool CarRentalSystem::processPayment(int userId, int amount)
{
    User* user = getUserById(userId);
    if (user == nullptr)
    {
        return false;
    }
    int currentDebt = user->getTotalDebt();
    if (amount >= currentDebt)
    {
        user->setTotalDebt(0);
    }
    else
    {
        user->setTotalDebt(currentDebt - amount);
    }
    checkAndUnblockDebtors();
    saveData();
    return true;
}

bool CarRentalSystem::addMaintenanceRecord(int carId, int date, string description, int cost, int endDate)
{
    Car* car = getCarById(carId);
    if (car == nullptr)
    {
        return false;
    }
    MaintenanceRecord record;
    record.date = date;
    record.description = description;
    record.cost = cost;
    record.expectedEndDate = endDate;
    car->addMaintenanceRecord(record);
    saveData();
    return true;
}

bool CarRentalSystem::setCarMaintenance(int carId, int endDate)
{
    Car* car = getCarById(carId);
    if (car == nullptr)
    {
        return false;
    }
    if (car->getStatus() == CAR_RENTED)
    {
        return false;
    }
    car->setStatus(CAR_MAINTENANCE);
    car->setMaintenanceEndDate(endDate);
    saveData();
    return true;
}

bool CarRentalSystem::setCarAvailable(int carId)
{
    Car* car = getCarById(carId);
    if (car == nullptr)
    {
        return false;
    }
    car->setStatus(CAR_AVAILABLE);
    car->setMaintenanceEndDate(0);
    processReservationQueue(carId);
    saveData();
    return true;
}

bool CarRentalSystem::blockUser(int userId)
{
    User* user = getUserById(userId);
    if (user == nullptr)
    {
        return false;
    }
    user->setIsBlocked(true);
    saveData();
    return true;
}

bool CarRentalSystem::unblockUser(int userId)
{
    User* user = getUserById(userId);
    if (user == nullptr)
    {
        return false;
    }
    if (user->getTotalDebt() >= config.getDebtLimit())
    {
        return false;
    }
    user->setIsBlocked(false);
    saveData();
    return true;
}

User* CarRentalSystem::getUserById(int userId)
{
    for (int i = 0; i < userList.getCount(); i++)
    {
        User* user = userList.getByIndex(i);
        if (user->getUserId() == userId)
        {
            return user;
        }
    }
    return nullptr;
}

User* CarRentalSystem::getUserByUsername(string username)
{
    int* userIdPtr = usernameTable.search(username);
    if (userIdPtr == nullptr)
    {
        return nullptr;
    }
    return getUserById(*userIdPtr);
}

SinglyLinkedList<User>* CarRentalSystem::getAllUsers()
{
    return &userList;
}

SinglyLinkedList<User> CarRentalSystem::getBlockedUsers()
{
    SinglyLinkedList<User> results;

    for (int i = 0; i < userList.getCount(); i++)
    {
        User* user = userList.getByIndex(i);
        if (user->getIsBlocked())
        {
            results.addToEnd(*user);
        }
    }
    return results;
}

SinglyLinkedList<User> CarRentalSystem::getUsersWithDebt()
{
    SinglyLinkedList<User> results;

    for (int i = 0; i < userList.getCount(); i++)
    {
        User* user = userList.getByIndex(i);
        if (user->getTotalDebt() > 0)
        {
            results.addToEnd(*user);
        }
    }
    return results;
}

void CarRentalSystem::processReservationQueue(int carId)
{
    Car* car = getCarById(carId);
    if (car == nullptr)
    {
        return;
    }
    if (car->getStatus() != CAR_AVAILABLE)
    {
        return;
    }
    for (int i = 0; i < reservationList.getCount(); i++)
    {
        Reservation* res = reservationList.getByIndex(i);
        if (res->getCarId() == carId && res->getStatus() == RESERVATION_PENDING)
        {
            res->setStatus(RESERVATION_CONFIRMED);
            car->setStatus(CAR_RESERVED);
            saveData();
            break;
        }
    }
}

void CarRentalSystem::addToReturnQueue(int rentalId)
{
    returnQueue.enqueue(rentalId);
}

int CarRentalSystem::processReturnQueue()
{
    if (returnQueue.isEmpty())
    {
        return -1;
    }
    return returnQueue.dequeue();
}

int CarRentalSystem::getTotalIncome()
{
    int total = 0;
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        total = total + car->getTotalIncome();
    }
    return total;
}

int CarRentalSystem::getTotalFines()
{
    int total = 0;
    for (int i = 0; i < rentalList.getCount(); i++)
    {
        Rental* rental = rentalList.getByIndex(i);
        total = total + rental->getFineAmount();
    }
    return total;
}

double CarRentalSystem::getFleetUsageRate()
{
    int totalCars = carList.getCount();
    if (totalCars == 0)
    {
        return 0.0;
    }
    int rentedCars = 0;
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        if (car->getStatus() == CAR_RENTED)
        {
            rentedCars++;
        }
    }
    return (double)rentedCars / totalCars * 100.0;
}

bool CarRentalSystem::exportReport(string filename)
{
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        return false;
    }
    file << "Car Rental System Report" << endl;
    file << "======================" << endl << endl;
    file << "Report Date: " << Utils::dateToString(Utils::getCurrentDate()) << endl << endl;
    file << "Total Income: " << getTotalIncome() << " Toman" << endl;
    file << "Total Fines: " << getTotalFines() << " Toman" << endl;
    file << "Fleet Usage Rate: " << getFleetUsageRate() << "%" << endl << endl;
    file << "Total Cars: " << carList.getCount() << endl;
    file << "Total Users: " << userList.getCount() << endl;
    file << "Total Reservations: " << reservationList.getCount() << endl;
    file << "Total Rentals: " << rentalList.getCount() << endl << endl;
    file << "Car Details:" << endl;
    file << "ID,Plate,Brand,Model,Status,Income,TimesRented" << endl;
    for (int i = 0; i < carList.getCount(); i++)
    {
        Car* car = carList.getByIndex(i);
        file << car->getCarId() << ",";
        file << car->getPlateNumber() << ",";
        file << car->getBrand() << ",";
        file << car->getModel() << ",";
        file << car->getStatusString() << ",";
        file << car->getTotalIncome() << ",";
        file << car->getTimesRented() << endl;
    }
    file.close();
    return true;
}

bool CarRentalSystem::exportData(string filename)
{
    saveData();
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        return false;
    }
    file << "BACKUP_FILE" << endl;
    file << "Date: " << Utils::getCurrentDate() << endl;
    file << "Cars: " << carList.getCount() << endl;
    file << "Users: " << userList.getCount() << endl;
    file << "Reservations: " << reservationList.getCount() << endl;
    file << "Rentals: " << rentalList.getCount() << endl;
    file.close();
    return true;
}

bool CarRentalSystem::importData(string filename)
{
    ifstream file(filename.c_str());
    if (!file.is_open())
    {
        return false;
    }
    string header;
    file >> header;
    if (header != "BACKUP_FILE")
    {
        file.close();
        return false;
    }
    file.close();
    loadData();
    return true;
}

Config* CarRentalSystem::getConfig()
{
    return &config;
}