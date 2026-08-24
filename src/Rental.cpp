#include "Rental.h"

using namespace std;

Rental::Rental()
{
    rentalId = 0;
    carId = 0;
    userId = 0;
    reservationId = 0;
    startDate = 0;
    expectedReturnDate = 0;
    actualReturnDate = 0;
    totalCost = 0;
    fineAmount = 0;
    isPaid = false;
    status = RENTAL_ACTIVE;
}

Rental::Rental(int id, int car, int user, int resId, int start, int expectedReturn)
{
    rentalId = id;
    carId = car;
    userId = user;
    reservationId = resId;
    startDate = start;
    expectedReturnDate = expectedReturn;
    actualReturnDate = 0;
    totalCost = 0;
    fineAmount = 0;
    isPaid = false;
    status = RENTAL_ACTIVE;
}

int Rental::getRentalId()
{
    return rentalId;
}

void Rental::setRentalId(int id)
{
    rentalId = id;
}

int Rental::getCarId()
{
    return carId;
}

void Rental::setCarId(int car)
{
    carId = car;
}

int Rental::getUserId()
{
    return userId;
}

void Rental::setUserId(int user)
{
    userId = user;
}

int Rental::getReservationId()
{
    return reservationId;
}

void Rental::setReservationId(int resId)
{
    reservationId = resId;
}

int Rental::getStartDate()
{
    return startDate;
}

void Rental::setStartDate(int start)
{
    startDate = start;
}

int Rental::getExpectedReturnDate()
{
    return expectedReturnDate;
}

void Rental::setExpectedReturnDate(int expected)
{
    expectedReturnDate = expected;
}

int Rental::getActualReturnDate()
{
    return actualReturnDate;
}

void Rental::setActualReturnDate(int actual)
{
    actualReturnDate = actual;
}

int Rental::getTotalCost()
{
    return totalCost;
}

void Rental::setTotalCost(int cost)
{
    totalCost = cost;
}

int Rental::getFineAmount()
{
    return fineAmount;
}

void Rental::setFineAmount(int fine)
{
    fineAmount = fine;
}

bool Rental::getIsPaid()
{
    return isPaid;
}

void Rental::setIsPaid(bool paid)
{
    isPaid = paid;
}

RentalStatus Rental::getStatus()
{
    return status;
}

void Rental::setStatus(RentalStatus s)
{
    status = s;
}

string Rental::getStatusString()
{
    if (status == RENTAL_ACTIVE)
    {
        return "Active";
    }
    else if (status == RENTAL_RETURNED)
    {
        return "Returned";
    }
    else if (status == RENTAL_OVERDUE)
    {
        return "Overdue";
    }

    return "Unknown";
}
