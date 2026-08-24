#ifndef CONFIG_H
#define CONFIG_H

using namespace std;

class Config
{
private:
    int fineRatePerDay;
    int maxRentalDays;
    int maxReservationsPerUser;
    int reservationHoldDays;
    int debtLimitForBlock;

public:
    Config();

    void setFineRate(int rate);
    int getFineRate();

    void setMaxRentalDays(int days);
    int getMaxRentalDays();

    void setMaxReservations(int max);
    int getMaxReservations();

    void setReservationHoldDays(int days);
    int getReservationHoldDays();

    void setDebtLimit(int limit);
    int getDebtLimit();

    void loadFromFile();
    void saveToFile();
};

#endif
