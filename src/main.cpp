#include <iostream>
#include "ui.h"

using namespace std;

int main() {

    cout << "Hello" << endl;
    Season new_s;
    new_s.add_player("Elias Besculides", 2008, true);
    cout << "WHY" << endl;
    new_s.get_player();
    cout << "World" << endl;
    cin.get();

    UI ui;
    ui.start();
    return 0;
}
