#include "Menu.h"
#include <iostream>
#include <sstream>

using namespace std;

Menu::Menu(CarRentalSystem* sys)
{
    system = sys;
    boxWidth = 80;
    marginLeft = 20;
}

void Menu::clearScreen()
{
    ::system("cls");
}

void Menu::waitForEnter()
{
    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::printTopBorder()
{
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << " ";
    for (int i = 0; i < boxWidth; i++)
    {
        cout << "_";
    }
    cout << " " << endl;
}

void Menu::printBottomBorder()
{
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < boxWidth; i++)
    {
        cout << "_";
    }
    cout << "|" << endl;
}

void Menu::printEmptyLine()
{
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < boxWidth; i++)
    {
        cout << " ";
    }
    cout << "|" << endl;
}

void Menu::printLine(string text)
{
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "|  " << text;

    int spaces = boxWidth - text.length() - 2;
    for (int i = 0; i < spaces; i++)
    {
        cout << " ";
    }
    cout << "|" << endl;
}

void Menu::printCenteredLine(string text)
{
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "|";

    int textLen = text.length();
    int leftPad = (boxWidth - textLen) / 2;
    int rightPad = boxWidth - textLen - leftPad;

    for (int i = 0; i < leftPad; i++)
    {
        cout << " ";
    }
    cout << text;
    for (int i = 0; i < rightPad; i++)
    {
        cout << " ";
    }
    cout << "|" << endl;
}

void Menu::printSeparator()
{
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "|";
    for (int i = 0; i < boxWidth; i++)
    {
        cout << "-";
    }
    cout << "|" << endl;
}

void Menu::displayCurrentDate()
{
    string dateStr = "Today: " + Utils::dateToString(Utils::getCurrentDate());
    printCenteredLine(dateStr);
    printEmptyLine();
}

void Menu::initializeDate()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CAR RENTAL SYSTEM");
    printEmptyLine();
    printSeparator();
    printEmptyLine();
    printCenteredLine("Please enter today's date to start");
    printEmptyLine();
    printBottomBorder();

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter date (YYYY/MM/DD): ";

    string dateStr;
    cin >> dateStr;

    int date = Utils::stringToDate(dateStr);

    cout << endl;

    if (Utils::isValidDate(date))
    {
        Utils::setCurrentDate(date);

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Date set successfully!" << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Invalid date! Using default." << endl;
    }

    system->checkAndUpdateStatuses();

    waitForEnter();
}

void Menu::run()
{
    int choice;

    while (true)
    {
        system->checkAndUpdateStatuses();

        clearScreen();
        showMainMenu();

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Enter your choice: ";
        cin >> choice;

        if (choice == 0)
        {
            clearScreen();
            printTopBorder();
            printEmptyLine();
            printCenteredLine("GOODBYE!");
            printEmptyLine();
            printCenteredLine("Thank you for using Car Rental System");
            printEmptyLine();
            printBottomBorder();
            cout << endl;

            break;
        }

        User* currentUser = system->getCurrentUser();

        if (currentUser == nullptr)
        {
            switch (choice)
            {
            case 1:
                handleRegister();
                break;
            case 2:
                handleLogin();
                break;
            case 3:
                handleViewCars();
                break;
            case 4:
                handleSearchCars();
                break;
            case 5:
                handleViewCarDetails();
                break;
            default:
                break;
            }
        }
        else
        {
            UserRole role = currentUser->getRole();

            if (role == ROLE_CUSTOMER)
            {
                if (currentUser->getIsBlocked())
                {
                    switch (choice)
                    {
                    case 1:
                        handlePayDebt();
                        break;
                    case 2:
                        handleViewMyRentals();
                        break;
                    case 3:
                        system->logoutUser();
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    switch (choice)
                    {
                    case 1:
                        handleViewCars();
                        break;
                    case 2:
                        handleSearchCars();
                        break;
                    case 3:
                        handleCreateReservation();
                        break;
                    case 4:
                        handleViewMyReservations();
                        break;
                    case 5:
                        handleCancelReservation();
                        break;
                    case 6:
                        handleViewMyRentals();
                        break;
                    case 7:
                        handleExtendRental();
                        break;
                    case 8:
                        handlePayDebt();
                        break;
                    case 9:
                        system->logoutUser();
                        break;
                    default:
                        break;
                    }
                }
            }
            else if (role == ROLE_STAFF)
            {
                switch (choice)
                {
                case 1:
                    handleViewCars();
                    break;
                case 2:
                    handleConvertToRental();
                    break;
                case 3:
                    handleReturnCar();
                    break;
                case 4:
                    handleViewOverdueRentals();
                    break;
                case 5:
                    handleProcessReservationQueue();
                    break;
                case 6:
                    handleAddCar();
                    break;
                case 7:
                    handleEditCar();
                    break;
                case 8:
                    handleViewAllReservations();
                    break;
                case 9:
                    handlePayUserDebt();
                    break;
                case 10:
                    system->logoutUser();
                    break;
                default:
                    break;
                }
            }
            else if (role == ROLE_MAINTENANCE)
            {
                switch (choice)
                {
                case 1:
                    handleViewCars();
                    break;
                case 2:
                    handleViewMaintenanceCars();
                    break;
                case 3:
                    handleAddMaintenanceRecord();
                    break;
                case 4:
                    handleSetCarMaintenance();
                    break;
                case 5:
                    handleSetCarAvailable();
                    break;
                case 6:
                    system->logoutUser();
                    break;
                default:
                    break;
                }
            }
            else if (role == ROLE_MANAGER)
            {
                switch (choice)
                {
                case 1:
                    handleViewCars();
                    break;
                case 2:
                    handleViewReport();
                    break;
                case 3:
                    handleBlockUser();
                    break;
                case 4:
                    handleUnblockUser();
                    break;
                case 5:
                    handleViewBlockedUsers();
                    break;
                case 6:
                    handleExportData();
                    break;
                case 7:
                    handleImportData();
                    break;
                case 8:
                    handleConfigSettings();
                    break;
                case 9:
                    handleAdvanceDate();
                    break;
                case 10:
                    handleSetDate();
                    break;
                case 11:
                    system->logoutUser();
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void Menu::showMainMenu()
{
    User* currentUser = system->getCurrentUser();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CAR RENTAL SYSTEM");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();

    if (currentUser == nullptr)
    {
        showGuestMenu();
    }
    else
    {
        string welcome = "Welcome, " + currentUser->getFullName() + "!";
        printCenteredLine(welcome);

        string roleStr = "Role: " + currentUser->getRoleString();
        printCenteredLine(roleStr);

        if (currentUser->getTotalDebt() > 0)
        {
            stringstream ss;
            ss << "** Debt: " << currentUser->getTotalDebt() << " Toman **";
            printCenteredLine(ss.str());
        }

        if (currentUser->getIsBlocked())
        {
            printCenteredLine("!! ACCOUNT BLOCKED !!");
        }

        printEmptyLine();
        printSeparator();
        printEmptyLine();

        UserRole role = currentUser->getRole();

        if (role == ROLE_CUSTOMER)
        {
            if (currentUser->getIsBlocked())
            {
                showBlockedCustomerMenu();
            }
            else
            {
                showCustomerMenu();
            }
        }
        else if (role == ROLE_STAFF)
        {
            showStaffMenu();
        }
        else if (role == ROLE_MAINTENANCE)
        {
            showMaintenanceMenu();
        }
        else if (role == ROLE_MANAGER)
        {
            showManagerMenu();
        }
    }

    printSeparator();
    printLine("0. Exit");
    printEmptyLine();
    printBottomBorder();
    cout << endl;
}

void Menu::showGuestMenu()
{
    printCenteredLine("GUEST MENU");
    printEmptyLine();
    printSeparator();
    printEmptyLine();
    printLine("1. Register");
    printLine("2. Login");
    printLine("3. View Cars");
    printLine("4. Search Cars");
    printLine("5. View Car Details");
    printEmptyLine();
}

void Menu::showCustomerMenu()
{
    printCenteredLine("CUSTOMER MENU");
    printEmptyLine();
    printLine("1. View Cars");
    printLine("2. Search Cars");
    printLine("3. Create Reservation");
    printLine("4. View My Reservations");
    printLine("5. Cancel Reservation");
    printLine("6. View My Rentals");
    printLine("7. Extend Rental");
    printLine("8. Pay Debt");
    printLine("9. Logout");
    printEmptyLine();
}

void Menu::showBlockedCustomerMenu()
{
    printCenteredLine("BLOCKED ACCOUNT");
    printEmptyLine();
    printCenteredLine("You must pay your debt to unblock");
    printEmptyLine();
    printSeparator();
    printEmptyLine();
    printLine("1. Pay Debt");
    printLine("2. View My Rentals");
    printLine("3. Logout");
    printEmptyLine();
}

void Menu::showStaffMenu()
{
    DoublyLinkedList<Rental> overdue = system->getOverdueRentals();

    printCenteredLine("STAFF MENU");

    if (overdue.getCount() > 0)
    {
        stringstream ss;
        ss << "!! WARNING: " << overdue.getCount() << " overdue rental(s) !!";
        printCenteredLine(ss.str());
    }

    printEmptyLine();
    printLine("1. View Cars");
    printLine("2. Convert Reservation to Rental");
    printLine("3. Return Car");
    printLine("4. View Overdue Rentals");
    printLine("5. Process Reservation Queue");
    printLine("6. Add New Car");
    printLine("7. Edit Car");
    printLine("8. View All Reservations");
    printLine("9. Pay User Debt");
    printLine("10. Logout");
    printEmptyLine();
}

void Menu::showMaintenanceMenu()
{
    printCenteredLine("MAINTENANCE MENU");
    printEmptyLine();
    printLine("1. View Cars");
    printLine("2. View Cars in Maintenance");
    printLine("3. Add Maintenance Record");
    printLine("4. Set Car to Maintenance");
    printLine("5. Set Car to Available");
    printLine("6. Logout");
    printEmptyLine();
}

void Menu::showManagerMenu()
{
    printCenteredLine("MANAGER MENU");
    printEmptyLine();
    printLine("1. View Cars");
    printLine("2. View Report");
    printLine("3. Block User");
    printLine("4. Unblock User");
    printLine("5. View Blocked Users");
    printLine("6. Export Data (Backup)");
    printLine("7. Import Data (Restore)");
    printLine("8. Configuration Settings");
    printLine("9. Advance Date");
    printLine("10. Set Date Manually");
    printLine("11. Logout");
    printEmptyLine();
}

void Menu::handleRegister()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("REGISTER");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string username, password, fullName, phone;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter username: ";
    cin >> username;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter password: ";
    cin >> password;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter full name: ";
    cin.ignore();
    getline(cin, fullName);

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter phone: ";
    cin >> phone;

    bool result = system->registerUser(username, password, fullName, phone);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Registration successful!");
        printCenteredLine("You can now login.");
    }
    else
    {
        printCenteredLine("Registration failed!");
        printCenteredLine("Username already exists.");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleLogin()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("LOGIN");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string username, password;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter username: ";
    cin >> username;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter password: ";
    cin >> password;

    User* user = system->loginUser(username, password);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (user != nullptr)
    {
        string msg = "Welcome, " + user->getFullName() + "!";
        printCenteredLine("Login successful!");
        printCenteredLine(msg);

        if (user->getIsBlocked())
        {
            printEmptyLine();
            printCenteredLine("!! YOUR ACCOUNT IS BLOCKED !!");

            if (user->getTotalDebt() >= system->getConfig()->getDebtLimit())
            {
                stringstream ss;
                ss << "Debt: " << user->getTotalDebt() << " Toman";
                printCenteredLine(ss.str());
                printCenteredLine("Please pay your debt to unblock.");
            }
        }
    }
    else
    {
        printCenteredLine("Login failed!");
        printCenteredLine("Invalid username or password.");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewCars()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("ALL CARS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    DoublyLinkedList<Car>* cars = system->getAllCars();

    cout << endl;

    if (cars->getCount() == 0)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No cars available." << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ID   Plate        Brand        Model        Price      Status" << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ---------------------------------------------------------------" << endl;

        for (int i = 0; i < cars->getCount(); i++)
        {
            Car* car = cars->getByIndex(i);

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << car->getCarId() << "    ";
            cout << car->getPlateNumber() << "    ";
            cout << car->getBrand() << "        ";
            cout << car->getModel() << "        ";
            cout << car->getDailyPrice() << "      ";
            cout << car->getStatusString();

            if (car->getStatus() == CAR_MAINTENANCE && car->getMaintenanceEndDate() > 0)
            {
                cout << " (until " << Utils::dateToString(car->getMaintenanceEndDate()) << ")";
            }

            cout << endl;
        }
    }

    waitForEnter();
}

void Menu::handleSearchCars()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("SEARCH CARS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string brand, type;
    int minPrice, maxPrice;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter brand (Enter to skip): ";
    cin.ignore();
    getline(cin, brand);

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter type (Enter to skip): ";
    getline(cin, type);

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Min price (0 to skip): ";
    cin >> minPrice;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Max price (0 to skip): ";
    cin >> maxPrice;

    DoublyLinkedList<Car> results = system->searchCars(brand, type, minPrice, maxPrice);

    cout << endl;

    if (results.getCount() == 0)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No cars found." << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Found " << results.getCount() << " cars:" << endl << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ID   Plate        Brand        Model        Price      Status" << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ---------------------------------------------------------------" << endl;

        for (int i = 0; i < results.getCount(); i++)
        {
            Car* car = results.getByIndex(i);

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << car->getCarId() << "    ";
            cout << car->getPlateNumber() << "    ";
            cout << car->getBrand() << "        ";
            cout << car->getModel() << "        ";
            cout << car->getDailyPrice() << "      ";
            cout << car->getStatusString() << endl;
        }
    }

    waitForEnter();
}

void Menu::handleViewCarDetails()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CAR DETAILS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int carId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter car ID: ";
    cin >> carId;

    Car* car = system->getCarById(carId);

    cout << endl;

    if (car == nullptr)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Car not found!" << endl;
    }
    else
    {
        printTopBorder();
        printEmptyLine();

        stringstream ss;
        ss << "Car ID: " << car->getCarId();
        printLine(ss.str());

        printLine("Plate: " + car->getPlateNumber());
        printLine("Brand: " + car->getBrand());
        printLine("Model: " + car->getModel());
        printLine("Type: " + car->getCarType());

        stringstream ss2;
        ss2 << "Year: " << car->getYear();
        printLine(ss2.str());

        printLine("Color: " + car->getColor());

        stringstream ss3;
        ss3 << "Daily Price: " << car->getDailyPrice() << " Toman";
        printLine(ss3.str());

        printLine("Status: " + car->getStatusString());

        if (car->getStatus() == CAR_RENTED)
        {
            Rental* rental = system->getActiveRentalByCarId(carId);
            if (rental != nullptr)
            {
                string retDate = "Expected Return: " + Utils::dateToString(rental->getExpectedReturnDate());
                printLine(retDate);

                int today = Utils::getCurrentDate();
                if (today > rental->getExpectedReturnDate())
                {
                    int daysLate = Utils::daysBetween(rental->getExpectedReturnDate(), today);
                    stringstream ss4;
                    ss4 << "** OVERDUE by " << daysLate << " days! **";
                    printLine(ss4.str());
                }
            }
        }

        if (car->getStatus() == CAR_MAINTENANCE && car->getMaintenanceEndDate() > 0)
        {
            string maintEnd = "Maintenance ends: " + Utils::dateToString(car->getMaintenanceEndDate());
            printLine(maintEnd);
        }

        printEmptyLine();
        printBottomBorder();
    }

    waitForEnter();
}

void Menu::handleCreateReservation()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CREATE RESERVATION");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    User* currentUser = system->getCurrentUser();

    if (currentUser->getIsBlocked())
    {
        cout << endl;
        printTopBorder();
        printEmptyLine();
        printCenteredLine("Your account is blocked!");

        if (currentUser->getTotalDebt() >= system->getConfig()->getDebtLimit())
        {
            printCenteredLine("Reason: High debt");
        }

        printEmptyLine();
        printBottomBorder();

        waitForEnter();

        return;
    }

    if (currentUser->getReservationCount() >= system->getConfig()->getMaxReservations())
    {
        cout << endl;
        printTopBorder();
        printEmptyLine();
        printCenteredLine("Maximum reservations reached!");
        printEmptyLine();
        printBottomBorder();

        waitForEnter();

        return;
    }

    DoublyLinkedList<Car> carsForRes = system->getCarsForReservation();

    if (carsForRes.getCount() == 0)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No cars available." << endl;

        waitForEnter();

        return;
    }

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Available Cars:" << endl << endl;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   ID   Brand        Model        Price/Day    Status" << endl;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   -----------------------------------------------------" << endl;

    for (int i = 0; i < carsForRes.getCount(); i++)
    {
        Car* car = carsForRes.getByIndex(i);

        for (int j = 0; j < marginLeft; j++)
        {
            cout << " ";
        }
        cout << "   ";
        cout << car->getCarId() << "    ";
        cout << car->getBrand() << "        ";
        cout << car->getModel() << "        ";
        cout << car->getDailyPrice() << "        ";
        cout << car->getStatusString() << endl;
    }

    cout << endl;

    int carId;
    string startStr, endStr;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter car ID: ";
    cin >> carId;

    Car* selectedCar = system->getCarById(carId);

    if (selectedCar == nullptr)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Car not found!" << endl;

        waitForEnter();

        return;
    }

    if (selectedCar->getStatus() == CAR_MAINTENANCE)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   This car is in maintenance!" << endl;

        waitForEnter();

        return;
    }

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Start date (YYYY/MM/DD): ";
    cin >> startStr;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   End date (YYYY/MM/DD): ";
    cin >> endStr;

    int startDate = Utils::stringToDate(startStr);
    int endDate = Utils::stringToDate(endStr);
    int today = Utils::getCurrentDate();

    if (startDate < today)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Start date cannot be in the past!" << endl;

        waitForEnter();

        return;
    }

    if (endDate < startDate)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   End date cannot be before start date!" << endl;

        waitForEnter();

        return;
    }

    if (system->hasOverlappingReservation(carId, startDate, endDate))
    {
        cout << endl;
        printTopBorder();
        printEmptyLine();
        printCenteredLine("Date conflict!");
        printCenteredLine("This car is not available");
        printCenteredLine("in the selected date range.");
        printEmptyLine();
        printBottomBorder();

        waitForEnter();

        return;
    }

    bool result = system->createReservation(carId, startDate, endDate);

    cout << endl;

    if (result)
    {
        int days = Utils::daysBetween(startDate, endDate) + 1;
        int totalCost = days * selectedCar->getDailyPrice();

        printTopBorder();
        printEmptyLine();
        printCenteredLine("Reservation created!");
        printEmptyLine();

        string carInfo = selectedCar->getBrand() + " " + selectedCar->getModel();
        printLine("Car: " + carInfo);

        stringstream ss;
        ss << "Duration: " << days << " days";
        printLine(ss.str());

        printLine("From: " + Utils::dateToString(startDate));
        printLine("To: " + Utils::dateToString(endDate));

        stringstream ss2;
        ss2 << "Cost: " << totalCost << " Toman";
        printLine(ss2.str());

        printEmptyLine();
        printBottomBorder();
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Failed to create reservation." << endl;
    }

    waitForEnter();
}

void Menu::handleViewMyReservations()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("MY RESERVATIONS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    User* currentUser = system->getCurrentUser();
    DoublyLinkedList<Reservation> reservations = system->getUserReservations(currentUser->getUserId());

    cout << endl;

    if (reservations.getCount() == 0)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   You have no reservations." << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ID    Car    Start        End          Status" << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ------------------------------------------------" << endl;

        for (int i = 0; i < reservations.getCount(); i++)
        {
            Reservation* res = reservations.getByIndex(i);

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << res->getReservationId() << "     ";
            cout << res->getCarId() << "      ";
            cout << Utils::dateToString(res->getStartDate()) << "   ";
            cout << Utils::dateToString(res->getEndDate()) << "   ";
            cout << res->getStatusString() << endl;
        }
    }

    waitForEnter();
}

void Menu::handleCancelReservation()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CANCEL RESERVATION");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int reservationId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter reservation ID: ";
    cin >> reservationId;

    bool result = system->cancelReservation(reservationId);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Reservation cancelled!");
    }
    else
    {
        printCenteredLine("Failed to cancel!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewMyRentals()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("MY RENTALS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();

    User* currentUser = system->getCurrentUser();

    stringstream ss;
    ss << "Your Debt: " << currentUser->getTotalDebt() << " Toman";
    printCenteredLine(ss.str());

    if (currentUser->getTotalDebt() >= system->getConfig()->getDebtLimit())
    {
        printCenteredLine("** ACCOUNT BLOCKED **");
    }

    printEmptyLine();
    printBottomBorder();

    DoublyLinkedList<Rental> rentals = system->getUserRentals(currentUser->getUserId());

    cout << endl;

    if (rentals.getCount() == 0)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   You have no rentals." << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ID   Car   Start        Expected     Cost       Status" << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   -----------------------------------------------------------" << endl;

        int today = Utils::getCurrentDate();

        for (int i = 0; i < rentals.getCount(); i++)
        {
            Rental* rental = rentals.getByIndex(i);

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << rental->getRentalId() << "    ";
            cout << rental->getCarId() << "     ";
            cout << Utils::dateToString(rental->getStartDate()) << "   ";
            cout << Utils::dateToString(rental->getExpectedReturnDate()) << "   ";
            cout << rental->getTotalCost() << "      ";
            cout << rental->getStatusString();

            if ((rental->getStatus() == RENTAL_ACTIVE || rental->getStatus() == RENTAL_OVERDUE)
                && today > rental->getExpectedReturnDate())
            {
                int daysLate = Utils::daysBetween(rental->getExpectedReturnDate(), today);
                int currentFine = daysLate * system->getConfig()->getFineRate();
                cout << " (+" << currentFine << ")";
            }

            cout << endl;
        }
    }

    waitForEnter();
}

void Menu::handleExtendRental()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("EXTEND RENTAL");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int rentalId;
    string newEndStr;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter rental ID: ";
    cin >> rentalId;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   New end date (YYYY/MM/DD): ";
    cin >> newEndStr;

    int newEndDate = Utils::stringToDate(newEndStr);

    bool result = system->extendRental(rentalId, newEndDate);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Rental extended!");
    }
    else
    {
        printCenteredLine("Failed to extend!");
        printCenteredLine("Possible reservation conflict.");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handlePayDebt()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("PAY DEBT");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();

    User* currentUser = system->getCurrentUser();

    stringstream ss;
    ss << "Current debt: " << currentUser->getTotalDebt() << " Toman";
    printCenteredLine(ss.str());

    if (currentUser->getTotalDebt() >= system->getConfig()->getDebtLimit())
    {
        printCenteredLine("** ACCOUNT BLOCKED **");

        stringstream ss2;
        ss2 << "Limit: " << system->getConfig()->getDebtLimit() << " Toman";
        printCenteredLine(ss2.str());

        int needToPay = currentUser->getTotalDebt() - system->getConfig()->getDebtLimit() + 1;
        stringstream ss3;
        ss3 << "Pay at least " << needToPay << " to unblock";
        printCenteredLine(ss3.str());
    }

    printEmptyLine();
    printBottomBorder();

    if (currentUser->getTotalDebt() == 0)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No debt to pay!" << endl;

        waitForEnter();

        return;
    }

    int amount;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter amount to pay: ";
    cin >> amount;

    bool result = system->processPayment(currentUser->getUserId(), amount);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Payment successful!");

        stringstream ss3;
        ss3 << "Remaining: " << currentUser->getTotalDebt() << " Toman";
        printCenteredLine(ss3.str());

        if (!currentUser->getIsBlocked())
        {
            printCenteredLine("Account unblocked!");
        }
        else if (currentUser->getTotalDebt() >= system->getConfig()->getDebtLimit())
        {
            int stillNeed = currentUser->getTotalDebt() - system->getConfig()->getDebtLimit() + 1;
            stringstream ss4;
            ss4 << "Pay " << stillNeed << " more to unblock";
            printCenteredLine(ss4.str());
        }
    }
    else
    {
        printCenteredLine("Payment failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleConvertToRental()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CONVERT TO RENTAL");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int reservationId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter reservation ID: ";
    cin >> reservationId;

    Reservation* res = system->getReservationById(reservationId);

    if (res != nullptr)
    {
        User* user = system->getUserById(res->getUserId());

        if (user != nullptr && user->getIsBlocked())
        {
            cout << endl;
            printTopBorder();
            printEmptyLine();
            printCenteredLine("Cannot convert!");
            printCenteredLine("Customer account is blocked.");
            printEmptyLine();
            printBottomBorder();

            waitForEnter();

            return;
        }
    }

    bool result = system->convertToRental(reservationId);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Converted successfully!");
    }
    else
    {
        printCenteredLine("Conversion failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleReturnCar()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("RETURN CAR");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int rentalId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter rental ID: ";
    cin >> rentalId;

    Rental* rental = system->getRentalById(rentalId);

    if (rental == nullptr)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Rental not found!" << endl;

        waitForEnter();

        return;
    }

    Car* car = system->getCarById(rental->getCarId());
    User* user = system->getUserById(rental->getUserId());

    cout << endl;
    printTopBorder();
    printEmptyLine();
    printCenteredLine("Rental Details");
    printEmptyLine();

    string carInfo = "Car: " + car->getBrand() + " " + car->getModel();
    printLine(carInfo);
    printLine("Customer: " + user->getFullName());
    printLine("Start: " + Utils::dateToString(rental->getStartDate()));
    printLine("Expected: " + Utils::dateToString(rental->getExpectedReturnDate()));

    stringstream ss;
    ss << "Rental Cost: " << rental->getTotalCost() << " Toman";
    printLine(ss.str());

    int fine = system->calculateFine(rentalId);

    if (fine > 0)
    {
        int daysLate = Utils::daysBetween(rental->getExpectedReturnDate(), Utils::getCurrentDate());

        printEmptyLine();
        printCenteredLine("** LATE RETURN **");

        stringstream ss2;
        ss2 << "Days late: " << daysLate;
        printLine(ss2.str());

        stringstream ss3;
        ss3 << "Fine: " << fine << " Toman";
        printLine(ss3.str());
    }

    int totalToPay = rental->getTotalCost() + fine;
    printEmptyLine();

    stringstream ss4;
    ss4 << "Total to pay: " << totalToPay << " Toman";
    printLine(ss4.str());

    printEmptyLine();
    printBottomBorder();

    char needsMaint;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Needs maintenance? (y/n): ";
    cin >> needsMaint;

    bool maintenance = (needsMaint == 'y' || needsMaint == 'Y');
    int maintEndDate = 0;

    if (maintenance)
    {
        string maintEndStr;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Maintenance end date (YYYY/MM/DD): ";
        cin >> maintEndStr;

        maintEndDate = Utils::stringToDate(maintEndStr);
    }

    bool result = system->returnCar(rentalId, maintenance, maintEndDate);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Car returned!");

        stringstream ss5;
        ss5 << "Added " << totalToPay << " to debt";
        printCenteredLine(ss5.str());

        if (user->getIsBlocked())
        {
            printCenteredLine("** Customer BLOCKED **");
        }

        if (maintenance)
        {
            string maintMsg = "Maintenance until " + Utils::dateToString(maintEndDate);
            printCenteredLine(maintMsg);
        }
    }
    else
    {
        printCenteredLine("Return failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewOverdueRentals()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("OVERDUE RENTALS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    DoublyLinkedList<Rental> overdue = system->getOverdueRentals();

    cout << endl;

    if (overdue.getCount() == 0)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No overdue rentals." << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   WARNING: " << overdue.getCount() << " overdue rental(s)!" << endl << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ID   Car   User   Expected     Late   Fine" << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   -----------------------------------------------" << endl;

        int today = Utils::getCurrentDate();

        for (int i = 0; i < overdue.getCount(); i++)
        {
            Rental* rental = overdue.getByIndex(i);

            int daysLate = Utils::daysBetween(rental->getExpectedReturnDate(), today);
            int fine = daysLate * system->getConfig()->getFineRate();

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << rental->getRentalId() << "    ";
            cout << rental->getCarId() << "     ";
            cout << rental->getUserId() << "      ";
            cout << Utils::dateToString(rental->getExpectedReturnDate()) << "   ";
            cout << daysLate << "      ";
            cout << fine << endl;
        }
    }

    waitForEnter();
}

void Menu::handleProcessReservationQueue()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("PROCESS RESERVATION QUEUE");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int carId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter car ID: ";
    cin >> carId;

    system->processReservationQueue(carId);

    cout << endl;
    printTopBorder();
    printEmptyLine();
    printCenteredLine("Queue processed!");
    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleAddCar()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("ADD NEW CAR");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string plate, brand, model, type, color;
    int year, price;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Plate number: ";
    cin >> plate;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Brand: ";
    cin >> brand;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Model: ";
    cin >> model;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Type: ";
    cin >> type;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Year: ";
    cin >> year;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Color: ";
    cin >> color;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Daily price: ";
    cin >> price;

    bool result = system->addCar(plate, brand, model, type, year, color, price);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Car added!");
    }
    else
    {
        printCenteredLine("Failed to add car!");
        printCenteredLine("Plate may already exist.");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleEditCar()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("EDIT CAR");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int carId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter car ID: ";
    cin >> carId;

    Car* car = system->getCarById(carId);

    if (car == nullptr)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Car not found!" << endl;

        waitForEnter();

        return;
    }

    cout << endl;
    printTopBorder();
    printEmptyLine();
    printCenteredLine("Current Details");
    printEmptyLine();
    printLine("Plate: " + car->getPlateNumber());
    printLine("Brand: " + car->getBrand());
    printLine("Model: " + car->getModel());
    printLine("Type: " + car->getCarType());

    stringstream ss;
    ss << "Year: " << car->getYear();
    printLine(ss.str());

    printLine("Color: " + car->getColor());

    stringstream ss2;
    ss2 << "Price: " << car->getDailyPrice();
    printLine(ss2.str());

    printEmptyLine();
    printBottomBorder();

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter new details:" << endl << endl;

    string plate, brand, model, type, color;
    int year, price;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Plate: ";
    cin >> plate;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Brand: ";
    cin >> brand;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Model: ";
    cin >> model;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Type: ";
    cin >> type;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Year: ";
    cin >> year;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Color: ";
    cin >> color;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Price: ";
    cin >> price;

    bool result = system->updateCar(carId, plate, brand, model, type, year, color, price);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Car updated!");
    }
    else
    {
        printCenteredLine("Update failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewAllReservations()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("ALL RESERVATIONS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   ID   Car   User   Start        End          Status" << endl;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   --------------------------------------------------------" << endl;

    for (int i = 1; i <= 100; i++)
    {
        Reservation* res = system->getReservationById(i);

        if (res != nullptr)
        {
            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << res->getReservationId() << "    ";
            cout << res->getCarId() << "     ";
            cout << res->getUserId() << "      ";
            cout << Utils::dateToString(res->getStartDate()) << "   ";
            cout << Utils::dateToString(res->getEndDate()) << "   ";
            cout << res->getStatusString() << endl;
        }
    }

    waitForEnter();
}

void Menu::handlePayUserDebt()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("PAY USER DEBT");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string username;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter username: ";
    cin >> username;

    User* user = system->getUserByUsername(username);

    if (user == nullptr)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   User not found!" << endl;

        waitForEnter();

        return;
    }

    cout << endl;
    printTopBorder();
    printEmptyLine();
    printLine("User: " + user->getFullName());

    stringstream ss;
    ss << "Current debt: " << user->getTotalDebt() << " Toman";
    printLine(ss.str());

    if (user->getIsBlocked())
    {
        printLine("Status: BLOCKED");
    }
    else
    {
        printLine("Status: Active");
    }

    printEmptyLine();
    printBottomBorder();

    if (user->getTotalDebt() == 0)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   This user has no debt!" << endl;

        waitForEnter();

        return;
    }

    int amount;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Enter amount to pay: ";
    cin >> amount;

    bool result = system->processPayment(user->getUserId(), amount);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Payment successful!");

        stringstream ss2;
        ss2 << "Remaining debt: " << user->getTotalDebt() << " Toman";
        printCenteredLine(ss2.str());

        if (!user->getIsBlocked())
        {
            printCenteredLine("User account unblocked!");
        }
    }
    else
    {
        printCenteredLine("Payment failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewMaintenanceCars()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CARS IN MAINTENANCE");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    DoublyLinkedList<Car>* cars = system->getAllCars();
    bool found = false;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   ID   Plate        Brand        Model        End Date" << endl;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   --------------------------------------------------------" << endl;

    for (int i = 0; i < cars->getCount(); i++)
    {
        Car* car = cars->getByIndex(i);

        if (car->getStatus() == CAR_MAINTENANCE)
        {
            found = true;

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << car->getCarId() << "    ";
            cout << car->getPlateNumber() << "    ";
            cout << car->getBrand() << "        ";
            cout << car->getModel() << "        ";

            if (car->getMaintenanceEndDate() > 0)
            {
                cout << Utils::dateToString(car->getMaintenanceEndDate());
            }
            else
            {
                cout << "Not set";
            }

            cout << endl;
        }
    }

    if (!found)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No cars in maintenance." << endl;
    }

    waitForEnter();
}

void Menu::handleAddMaintenanceRecord()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("ADD MAINTENANCE RECORD");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int carId, cost;
    string dateStr, description, endDateStr;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Car ID: ";
    cin >> carId;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Date (YYYY/MM/DD): ";
    cin >> dateStr;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Description: ";
    cin.ignore();
    getline(cin, description);

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Cost: ";
    cin >> cost;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   End date (YYYY/MM/DD): ";
    cin >> endDateStr;

    int date = Utils::stringToDate(dateStr);
    int endDate = Utils::stringToDate(endDateStr);

    bool result = system->addMaintenanceRecord(carId, date, description, cost, endDate);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Record added!");
    }
    else
    {
        printCenteredLine("Failed to add record!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleSetCarMaintenance()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("SET CAR TO MAINTENANCE");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int carId;
    string endDateStr;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Car ID: ";
    cin >> carId;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   End date (YYYY/MM/DD): ";
    cin >> endDateStr;

    int endDate = Utils::stringToDate(endDateStr);

    bool result = system->setCarMaintenance(carId, endDate);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        string msg = "Maintenance until " + Utils::dateToString(endDate);
        printCenteredLine("Car set to maintenance!");
        printCenteredLine(msg);
    }
    else
    {
        printCenteredLine("Failed!");
        printCenteredLine("Car may be rented.");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleSetCarAvailable()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("SET CAR TO AVAILABLE");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int carId;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Car ID: ";
    cin >> carId;

    bool result = system->setCarAvailable(carId);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Car is now available!");
    }
    else
    {
        printCenteredLine("Failed to update!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewReport()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("SYSTEM REPORT");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();

    stringstream ss1;
    ss1 << "Total Income: " << system->getTotalIncome() << " Toman";
    printLine(ss1.str());

    stringstream ss2;
    ss2 << "Total Fines: " << system->getTotalFines() << " Toman";
    printLine(ss2.str());

    stringstream ss3;
    ss3 << "Fleet Usage: " << system->getFleetUsageRate() << "%";
    printLine(ss3.str());

    printEmptyLine();
    printSeparator();
    printEmptyLine();

    stringstream ss4;
    ss4 << "Total Cars: " << system->getAllCars()->getCount();
    printLine(ss4.str());

    stringstream ss5;
    ss5 << "Total Users: " << system->getAllUsers()->getCount();
    printLine(ss5.str());

    DoublyLinkedList<Rental> overdue = system->getOverdueRentals();
    stringstream ss6;
    ss6 << "Overdue Rentals: " << overdue.getCount();
    printLine(ss6.str());

    SinglyLinkedList<User> blocked = system->getBlockedUsers();
    stringstream ss7;
    ss7 << "Blocked Users: " << blocked.getCount();
    printLine(ss7.str());

    printEmptyLine();
    printBottomBorder();

    char exportChoice;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Export to file? (y/n): ";
    cin >> exportChoice;

    if (exportChoice == 'y' || exportChoice == 'Y')
    {
        string filename;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Filename: ";
        cin >> filename;

        if (system->exportReport(filename))
        {
            cout << endl;
            for (int i = 0; i < marginLeft; i++)
            {
                cout << " ";
            }
            cout << "   Report exported!" << endl;
        }
        else
        {
            cout << endl;
            for (int i = 0; i < marginLeft; i++)
            {
                cout << " ";
            }
            cout << "   Export failed!" << endl;
        }
    }

    waitForEnter();
}

void Menu::handleBlockUser()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("BLOCK USER");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string username;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Username: ";
    cin >> username;

    User* user = system->getUserByUsername(username);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (user == nullptr)
    {
        printCenteredLine("User not found!");
    }
    else
    {
        bool result = system->blockUser(user->getUserId());

        if (result)
        {
            printCenteredLine("User blocked!");
        }
        else
        {
            printCenteredLine("Failed to block!");
        }
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleUnblockUser()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("UNBLOCK USER");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string username;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Username: ";
    cin >> username;

    User* user = system->getUserByUsername(username);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (user == nullptr)
    {
        printCenteredLine("User not found!");
    }
    else
    {
        if (user->getTotalDebt() >= system->getConfig()->getDebtLimit())
        {
            printCenteredLine("Cannot unblock!");

            stringstream ss;
            ss << "Debt: " << user->getTotalDebt() << " Toman";
            printCenteredLine(ss.str());

            printCenteredLine("Must pay debt first.");
        }
        else
        {
            bool result = system->unblockUser(user->getUserId());

            if (result)
            {
                printCenteredLine("User unblocked!");
            }
            else
            {
                printCenteredLine("Failed to unblock!");
            }
        }
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleViewBlockedUsers()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("BLOCKED USERS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();

    stringstream ss;
    ss << "Auto-block limit: " << system->getConfig()->getDebtLimit() << " Toman";
    printCenteredLine(ss.str());

    printEmptyLine();
    printBottomBorder();

    SinglyLinkedList<User> blocked = system->getBlockedUsers();

    cout << endl;

    if (blocked.getCount() == 0)
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   No blocked users." << endl;
    }
    else
    {
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ID   Username     Name              Debt         Reason" << endl;

        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   ---------------------------------------------------------------" << endl;

        for (int i = 0; i < blocked.getCount(); i++)
        {
            User* user = blocked.getByIndex(i);

            for (int j = 0; j < marginLeft; j++)
            {
                cout << " ";
            }
            cout << "   ";
            cout << user->getUserId() << "    ";
            cout << user->getUsername() << "       ";
            cout << user->getFullName() << "        ";
            cout << user->getTotalDebt() << "        ";

            if (user->getTotalDebt() >= system->getConfig()->getDebtLimit())
            {
                cout << "High Debt";
            }
            else
            {
                cout << "Manual";
            }

            cout << endl;
        }
    }

    waitForEnter();
}

void Menu::handleExportData()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("EXPORT DATA (BACKUP)");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string filename;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Filename: ";
    cin >> filename;

    bool result = system->exportData(filename);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Data exported!");
    }
    else
    {
        printCenteredLine("Export failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleImportData()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("IMPORT DATA (RESTORE)");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string filename;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Filename: ";
    cin >> filename;

    bool result = system->importData(filename);

    cout << endl;
    printTopBorder();
    printEmptyLine();

    if (result)
    {
        printCenteredLine("Data imported!");
    }
    else
    {
        printCenteredLine("Import failed!");
    }

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleConfigSettings()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("CONFIGURATION SETTINGS");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();

    Config* config = system->getConfig();

    stringstream ss1;
    ss1 << "1. Fine Rate: " << config->getFineRate() << " Toman/day";
    printLine(ss1.str());

    stringstream ss2;
    ss2 << "2. Max Rental Days: " << config->getMaxRentalDays();
    printLine(ss2.str());

    stringstream ss3;
    ss3 << "3. Max Reservations: " << config->getMaxReservations();
    printLine(ss3.str());

    stringstream ss4;
    ss4 << "4. Hold Days: " << config->getReservationHoldDays();
    printLine(ss4.str());

    stringstream ss5;
    ss5 << "5. Debt Limit: " << config->getDebtLimit() << " Toman";
    printLine(ss5.str());

    printEmptyLine();
    printBottomBorder();

    int choice;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Setting to change (0 to cancel): ";
    cin >> choice;

    if (choice == 0)
    {
        return;
    }

    int newValue;

    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   New value: ";
    cin >> newValue;

    switch (choice)
    {
    case 1:
        config->setFineRate(newValue);
        break;
    case 2:
        config->setMaxRentalDays(newValue);
        break;
    case 3:
        config->setMaxReservations(newValue);
        break;
    case 4:
        config->setReservationHoldDays(newValue);
        break;
    case 5:
        config->setDebtLimit(newValue);
        system->checkAndUpdateStatuses();
        break;
    }

    config->saveToFile();

    cout << endl;
    printTopBorder();
    printEmptyLine();
    printCenteredLine("Setting updated!");
    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleAdvanceDate()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("ADVANCE DATE");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    int days;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   Days to advance: ";
    cin >> days;

    if (days <= 0)
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Invalid number!" << endl;

        waitForEnter();

        return;
    }

    Utils::advanceDate(days);
    system->checkAndUpdateStatuses();

    cout << endl;
    printTopBorder();
    printEmptyLine();

    stringstream ss;
    ss << "Advanced by " << days << " days";
    printCenteredLine(ss.str());

    string newDate = "New date: " + Utils::dateToString(Utils::getCurrentDate());
    printCenteredLine(newDate);

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}

void Menu::handleSetDate()
{
    clearScreen();

    printTopBorder();
    printEmptyLine();
    printCenteredLine("SET DATE MANUALLY");
    printEmptyLine();
    printSeparator();
    displayCurrentDate();
    printBottomBorder();

    string dateStr;

    cout << endl;
    for (int i = 0; i < marginLeft; i++)
    {
        cout << " ";
    }
    cout << "   New date (YYYY/MM/DD): ";
    cin >> dateStr;

    int newDate = Utils::stringToDate(dateStr);

    if (!Utils::isValidDate(newDate))
    {
        cout << endl;
        for (int i = 0; i < marginLeft; i++)
        {
            cout << " ";
        }
        cout << "   Invalid date!" << endl;

        waitForEnter();

        return;
    }

    Utils::setCurrentDate(newDate);
    system->checkAndUpdateStatuses();

    cout << endl;
    printTopBorder();
    printEmptyLine();

    string msg = "Date set to: " + Utils::dateToString(Utils::getCurrentDate());
    printCenteredLine(msg);

    printEmptyLine();
    printBottomBorder();

    waitForEnter();
}