#include "ui.h"

using namespace std;

//Helper function to get player details for add and edit to recycle code
void UI::get_player_details(string & name, int & year, bool & paid) {
  string temp;
  string has_paid;
  cout << "Name: ";
  getline(cin, name);
  bool good = false;
  //Get a birth year
  do {
    cout << "Birth Year: ";
    getline(cin, temp);
    stringstream ss(temp);
    ss >> year;
    if (ss) {
      if (season_.year() - year < 4)
        cout << "Player must be older than 3" << endl;
      else if (season_.year() - year > 17)
        cout << "Player must be younger than 17" << endl;
      else
        good = true;
    }
    else {
      cout << "Please enter a valid year" << endl;
    }
  } while (!good);
  cout << "Paid? (Y/n) ";
  good = false;
  do {
  getline(cin, has_paid);
  std::transform(has_paid.begin(), has_paid.end(), has_paid.begin(), ::tolower);
  if(has_paid == "y" || has_paid == "yes") {
    paid = true;
    good = true;
  }
  else if(has_paid == "n" || has_paid == "no") {
    paid = false;
    good = true;
  }
  else
    cout << "Please enter yes or no" << endl;
  } while (!good);
}

//Create a new season
void UI::new_season() {
    int year;
    string temp;
    bool good = false;
    do {
      cout << "New Season Year: ";
      getline(cin, temp);
      stringstream ss(temp);
      ss >> year;
      if (ss) {
        season_.new_season(year);
        good = true;
      }
      else {
        cout << "Please enter a valid year" << endl;
      }
    } while (!good);
}

bool UI::exec_command(const string & command, bool & done) {
  if (command == "help") {
    cout << "Commands:" << endl;
    cout << "\t* next - displays the next player" << endl;
    cout << "\t* previous - displays the previous player" << endl;
    cout << "\t* add - adds a player" << endl;
    cout << "\t* edit - edits the current player" << endl;
    cout << "\t* delete - deletes the current player" << endl;
    cout << "\t* new - starts a new season" << endl;
    cout << "\t* stats - display season statistics" << endl;
    cout << "\t* print - prints the players to a file" << endl;
    //cout << "\t* search - searches for a player" << endl;
    //cout << "\t* exit - exits the search view" << endl;
    cout << "\t* save - saves any changes made" << endl;
    cout << "\t* stop - stops the program" << endl;
  }
  else if (command == "next") {
    season_.next_player();
    display();
  }
  else if (command == "previous" || command == "prev") {
    season_.previous_player();
    display();
  }
  else if (command == "add") {
    string name;
    int year;
    bool paid;
    get_player_details(name, year, paid);
    season_.add_player(name, year, paid);
    display();
  }
  else if (command == "edit") {
    string name;
    int year;
    bool paid;
    get_player_details(name, year, paid);
    season_.edit_player(name, year, paid);
    display();
  }
  else if (command == "delete") {
    season_.delete_player();
    display();
  }
  else if (command == "new") {
    new_season();
    display();
  }
  else if (command == "stop") {
    done = true;
    season_.save();
  }
  else if (command == "save") {
    season_.save();
    display();
  }
  else if (command == "stats") {
    season_.update_stats();
    auto itr = season_.get_stats();
    auto end_itr = season_.get_end_stat();
    for(itr; itr != end_itr; ++itr)
    {
        cout << itr -> first << " Players: " << itr -> second.players << endl;
        cout << itr -> first << " Paid: " << itr -> second.paid << endl;
        cout << itr -> first << " Not Paid: " << itr -> second.not_paid << endl;
        cout << endl;
    }
    display();
  }
  else if (command == "print") {
    cout << "Please input a file name to read to" << endl;
    string FileName;
    cin >> FileName;
    season_.print_players(FileName);
    display();
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
  if (season_.empty()) {
    cout << "No players to display" << endl;
  }
  else {
    cout << "Player (" << season_.get_current_pos() << "/" << season_.get_player_count() << "):" << endl;
    cout << "\tName: " << season_.display_name() << endl;
    cout << "\tBirth Year: " << season_.display_year() << endl;
    cout << "\tLeague: " << season_.display_league() << endl;
    cout << "\tPaid: " << season_.display_status() << endl;
  }

  for (int i = 0; i < 35; ++i) {
    cout << "-";
  }

  cout << endl;
  cout << "Type 'help' for a list of commands" << endl;
}

void UI::start() {
  if (season_.open()) {
    display();
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
        bool temp = true;
        if (!exec_command("new", temp))
          waiting = false;
        else if (!run()) {
          waiting = false;
          cout << "Failed to run" << endl;
        }
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
  cout << ">> ";
  while (!done && getline(cin, input)) {
    if (!exec_command(input, done))
      cout << "Failed to run command: " + input << endl;
    if (!done)
      cout << ">> ";
  }
  return true;
}
