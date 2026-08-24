#include <iostream>
#include "CarRentalSystem.h"
#include "Menu.h"

using namespace std;

int main()
{
    CarRentalSystem system;
    Menu menu(&system);
    menu.initializeDate();
    menu.run();
    return 0;
}
