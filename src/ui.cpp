#include "ui.h"

using namespace std;

bool UI::exec_command(string command) {
  if (command == "help") {
    cout << "Commands:" << endl;
    cout << "\t* next - displays the next player" << endl;
    cout << "\t* previous - displays the previous player" << endl;
  }
  else if (command == "next") {
    season_.next_player();
    display();
  }
  else if (command == "previous") {
    season_.previous_player();
    display();
  }
  else {
    return false;
  }
  return true;
}

void UI::display() {
  system("clear || cls");
  cout << season_.year() << " Season" << endl;

  for (int i = 0; i < 35; ++i) {
    cout << "-";
  }
  cout << endl;

  season_.display();

  for (int i = 0; i < 35; ++i) {
    cout << "-";
  }
  
  cout << endl;
  cout << "Type 'help' for a list of commands" << endl;
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
  string input;
  bool exit = false;
  display();
  cout << ">> ";
  while (!exit && cin >> input) {
    if (input == "exit")
      exit = true;
    else if (!exec_command(input))
      cout << "Failed to run command: " + input << endl;
    if (!exit)
      cout << ">> ";
  }
  return true;
}
