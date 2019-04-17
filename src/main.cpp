#include <iostream>
#include "ui.h"

using namespace std;

int main()
{

    Season futbol(2019);
    futbol.add_player("Elias Besculides", 1999, "paid");
    futbol.add_player("Chase Beckmann", 2008, "paid");

    UserInterface ui;
    ui.start();
    return 0;
}
