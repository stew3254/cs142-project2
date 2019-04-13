#include "ui.h"

using namespace std;

void UserInterface::start() {
  bool waiting = true;
  string input;
  cout << "Would you like to start a new season? (y/n): ";
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

bool UserInterface::run() {
  return true;
}
