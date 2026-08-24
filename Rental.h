#ifndef RENTAL_H
#define RENTAL_H

#include <string>

using namespace std;

enum RentalStatus
{
    RENTAL_ACTIVE,
    RENTAL_RETURNED,
    RENTAL_OVERDUE
};

class Rental
{
private:
    int rentalId;
    int carId;
    int userId;
    int reservationId;
    int startDate;
    int expectedReturnDate;
    int actualReturnDate;
    int totalCost;
    int fineAmount;
    bool isPaid;
    RentalStatus status;

public:
    Rental();
    Rental(int id, int car, int user, int resId, int start, int expectedReturn);

    int getRentalId();
    void setRentalId(int id);

    int getCarId();
    void setCarId(int car);

    int getUserId();
    void setUserId(int user);

    int getReservationId();
    void setReservationId(int resId);

    int getStartDate();
    void setStartDate(int start);

    int getExpectedReturnDate();
    void setExpectedReturnDate(int expected);

    int getActualReturnDate();
    void setActualReturnDate(int actual);

    int getTotalCost();
    void setTotalCost(int cost);

    int getFineAmount();
    void setFineAmount(int fine);

    bool getIsPaid();
    void setIsPaid(bool paid);

    RentalStatus getStatus();
    void setStatus(RentalStatus s);

    string getStatusString();
};

#endif