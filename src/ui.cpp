#include "ui.h"

using namespace std;

void UI::display() {
  cout << season_.year() << endl;
  cout << "----" << endl << endl;
  for (int i = 0; i < 50; ++i) {
    cout << "-";
  }
  cout << endl;
}

void UI::start() {
  if (season_.open("season.txt")) {
    run();
  }
  else {
    bool waiting = true;
    string input;
    cout << "Would you like to start a new season? (y/n): ";
    //Get input, make it all lowercase and then see if the user input yes or no
    do {
      getline(cin, input);
      transform(input.begin(), input.end(), input.begin(), ::tolower);
      if (input == "y" || input == "yes") {
        cout << "Okay" << endl;
        waiting = false;
        if (!run())
          cout << "Failed to run" << endl;
      }
      else if (input == "n" || input == "no") {
        cout << "Bye" << endl;
      }
      else {
        cout << "Please input either yes or no: ";
      }
    } while (waiting);
  }
}

bool UI::run() {
  display();
  return true;
}
