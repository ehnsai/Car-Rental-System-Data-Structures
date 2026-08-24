#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

using namespace std;

enum ReservationStatus
{
    RESERVATION_PENDING,
    RESERVATION_CONFIRMED,
    RESERVATION_CANCELLED,
    RESERVATION_COMPLETED
};

class Reservation
{
private:
    int reservationId;
    int carId;
    int userId;
    int startDate;
    int endDate;
    int createdDate;
    ReservationStatus status;
    int priority;

public:
    Reservation();
    Reservation(int id, int car, int user, int start, int end, int created);

    int getReservationId();
    void setReservationId(int id);

    int getCarId();
    void setCarId(int car);

    int getUserId();
    void setUserId(int user);

    int getStartDate();
    void setStartDate(int start);

    int getEndDate();
    void setEndDate(int end);

    int getCreatedDate();
    void setCreatedDate(int created);

    ReservationStatus getStatus();
    void setStatus(ReservationStatus s);

    int getPriority();
    void setPriority(int p);

    string getStatusString();
};

#endif
