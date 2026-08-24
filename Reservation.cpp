#include "Reservation.h"

using namespace std;

Reservation::Reservation()
{
    reservationId = 0;
    carId = 0;
    userId = 0;
    startDate = 0;
    endDate = 0;
    createdDate = 0;
    status = RESERVATION_PENDING;
    priority = 0;
}

Reservation::Reservation(int id, int car, int user, int start, int end, int created)
{
    reservationId = id;
    carId = car;
    userId = user;
    startDate = start;
    endDate = end;
    createdDate = created;
    status = RESERVATION_PENDING;
    priority = created;
}

int Reservation::getReservationId()
{
    return reservationId;
}

void Reservation::setReservationId(int id)
{
    reservationId = id;
}

int Reservation::getCarId()
{
    return carId;
}

void Reservation::setCarId(int car)
{
    carId = car;
}

int Reservation::getUserId()
{
    return userId;
}

void Reservation::setUserId(int user)
{
    userId = user;
}

int Reservation::getStartDate()
{
    return startDate;
}

void Reservation::setStartDate(int start)
{
    startDate = start;
}

int Reservation::getEndDate()
{
    return endDate;
}

void Reservation::setEndDate(int end)
{
    endDate = end;
}

int Reservation::getCreatedDate()
{
    return createdDate;
}

void Reservation::setCreatedDate(int created)
{
    createdDate = created;
}

ReservationStatus Reservation::getStatus()
{
    return status;
}

void Reservation::setStatus(ReservationStatus s)
{
    status = s;
}

int Reservation::getPriority()
{
    return priority;
}

void Reservation::setPriority(int p)
{
    priority = p;
}

string Reservation::getStatusString()
{
    if (status == RESERVATION_PENDING)
    {
        return "Pending";
    }
    else if (status == RESERVATION_CONFIRMED)
    {
        return "Confirmed";
    }
    else if (status == RESERVATION_CANCELLED)
    {
        return "Cancelled";
    }
    else if (status == RESERVATION_COMPLETED)
    {
        return "Completed";
    }

    return "Unknown";
}