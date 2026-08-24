#ifndef MENU_H
#define MENU_H

#include <string>
#include "CarRentalSystem.h"

using namespace std;

class Menu
{
private:
    CarRentalSystem* system;
    int boxWidth;
    int marginLeft;

    void clearScreen();
    void waitForEnter();
    void displayCurrentDate();

    void printTopBorder();
    void printBottomBorder();
    void printEmptyLine();
    void printLine(string text);
    void printCenteredLine(string text);
    void printSeparator();

    void showMainMenu();
    void showGuestMenu();
    void showCustomerMenu();
    void showBlockedCustomerMenu();
    void showStaffMenu();
    void showMaintenanceMenu();
    void showManagerMenu();

    void handleRegister();
    void handleLogin();

    void handleViewCars();
    void handleSearchCars();
    void handleViewCarDetails();

    void handleCreateReservation();
    void handleViewMyReservations();
    void handleCancelReservation();
    void handleViewMyRentals();
    void handleExtendRental();
    void handlePayDebt();

    void handleConvertToRental();
    void handleReturnCar();
    void handleProcessReservationQueue();
    void handleAddCar();
    void handleEditCar();
    void handleViewAllReservations();
    void handleViewOverdueRentals();
    void handlePayUserDebt();

    void handleAddMaintenanceRecord();
    void handleSetCarMaintenance();
    void handleSetCarAvailable();
    void handleViewMaintenanceCars();

    void handleViewReport();
    void handleBlockUser();
    void handleUnblockUser();
    void handleViewBlockedUsers();
    void handleExportData();
    void handleImportData();
    void handleConfigSettings();
    void handleAdvanceDate();
    void handleSetDate();

public:
    Menu(CarRentalSystem* sys);
    void initializeDate();
    void run();
};

#endif