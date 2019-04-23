#include "ui.h"

using namespace std;

bool UI::exec_command(const string & command, bool & done) {
  if (command == "help") {
    cout << "Commands:" << endl;
    cout << "\t* next - displays the next player" << endl;
    cout << "\t* previous - displays the previous player" << endl;
    cout << "\t* add - adds a player" << endl;
    cout << "\t* edit - edits the current player" << endl;
    cout << "\t* delete - deletes the current player" << endl;
    cout << "\t* new - starts a new season" << endl;
    //cout << "\t* stats - display season statistics" << endl;
    //cout << "\t* print - prints the players to a file" << endl;
    //cout << "\t* search - searches for a player" << endl;
    //cout << "\t* exit - exits the search view" << endl;
    cout << "\t* stop - stops the program" << endl;
  }
  else if (command == "next") {
    season_.next_player();
    display();
  }
  else if (command == "previous") {
    season_.previous_player();
    display();
  }
  else if (command == "add") {
    string name;
    int year;
    string has_paid;
    cout << "Name: ";
    getline(cin, name);
    cout << "Birth Year: ";
    cin >> year;
    cout << "Paid? ";
    cin >> has_paid;
    season_.add_player(name, year, has_paid);
    display();
  }
  else if (command == "edit") {
    string name;
    int year;
    string has_paid;
    cout << "New name: ";
    getline(cin, name);
    cout << "New birth year: ";
    cin >> year;
    cout << "Paid? ";
    cin >> has_paid;
    season_.edit_player(name, year, has_paid);
    display();
  }
  else if (command == "delete") {
    season_.delete_player();
    display();
  }
  else if (command == "new") {
    int year;
    cout << "New Season Year: ";
    cin >> year;
    season_.new_season(year);
    display();
  }
  else if (command == "stop") {
    done = true;
  }
  else {
    return false;
  }
  return true;
}

void UI::display() {
  //system("clear || cls");
  cout << season_.year() << " Season" << endl;

  for (int i = 0; i < 35; ++i) {
    cout << "-";
  }
  cout << endl;
  cout << "Player (" << season_.get_current_pos() << "/" << season_.get_player_count() << "):" << endl;
  cout << "\tName: " << endl;
  cout << "\tBirth Year: " << endl;
  cout << "\tLeague: " << endl;
  cout << "\tPaid: " << endl;

  season_.display();

  for (int i = 0; i < 35; ++i) {
    cout << "-";
  }
  
  cout << endl;
  cout << "Type 'help' for a list of commands" << endl;
  cout << ">> ";
}

void UI::start() {
  if (season_.open("season.txt")) {
    run();
  }
  else {
    //Waiting for input
    bool waiting = true;
    string input;
    cout << "Would you like to start a new season? (y/n): ";
    //Get input, make it all lowercase and then see if the user input yes or no
    do {
      getline(cin, input);
      transform(input.begin(), input.end(), input.begin(), ::tolower);
      if (input == "y" || input == "yes") {
        if (!exec_command("new"))
          waiting = false;
        else if (!run())
          waiting = false;
          cout << "Failed to run" << endl;
      }
      else if (input != "n" || input != "no") {
        cout << "Please input either yes or no: ";
      }
    } while (waiting);
  }
}

//Run the UI
bool UI::run() {
  string input;
  bool done = false;
  display();
  while (!done && getline(cin, input)) {
    if (!exec_command(input, done))
      cout << "Failed to run command: " + input << endl;
  }
  return true;
}
