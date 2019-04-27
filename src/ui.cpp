#include "ui.h"

using namespace std;

void UI::display() {
  //system("clear || cls");
  cout << season_.year() << " Season: ";
  if(isBrowsing_)
    cout << "Browsing View" << endl;
  else
    cout << "Search View" << endl;

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

bool UI::check_paid(const string & input, bool & paid) {
  bool good = false;
    if(input == "y" || input == "yes") {
      paid = true;
      good = true;
    }
    else if(input == "n" || input == "no") {
      paid = false;
      good = true;
    }
  return good;
}

//Helper function to get player details for add and edit to recycle code
void UI::get_player_details(string & name, int & year, bool & paid) {
  string temp;
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

  good = false;
  do {
    cout << "Paid? (Y/n) ";
    getline(cin, temp);
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    if (check_paid(temp, paid))
      good = true;
    else
      cout << "Please enter yes or no" << endl;
  } while(!good);
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

void UI::search() {
  string first;
  string last;
  //Used to tell if the year is supposed to be blank
  int year = season_.year();
  string league;
  bool paid;

  string temp;
  stringstream ss;
  bool good = false;

  cout << "Input any search parameters you wish to fill. Leave them blank to ignore them" << endl;
  cout << "First Name: ";
  getline(cin, first);
  cout << "Last Name: ";
  getline(cin, last);
  do {
    cout << "Year: ";
    getline(cin, temp);
    if (temp.length() == 0) {
      year = season_.year();
      good = true;
    }
    else {
      ss >> year;
      if (!ss) {
        cout << "Please enter a valid year" << endl;
      }
      else if (season_.year() - year < 4 || season_.year() > 17) {
        cout << "Please enter a year between " << season_.year() - 4 << " and " << season_.year() - 17 << endl;
      }
      else {
        good = true;
      }
    }
  } while (!good);

  do {
    cout << "League (ex. U6): ";
    getline(cin, league);
    if (league.length() == 0) {
      good = true;
    }
    else if (league.length() < 2 || (league[0] != 'U' && league[0] != 'u') || !isdigit(league[1]) ) {
      cout << "League must be in the form 'U6' or u12" << endl;
    }
    else {
      good = true;
    }
  } while (!good);

  good = false;
  do {
    cout << "Paid? (Y/n) ";
    getline(cin, temp);
    if (temp.length() == 0) {
      good = true;
    }
    else {
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
      if (check_paid(temp, paid))
        good = true;
      else
        cout << "Please enter yes or no" << endl;
    }
  } while(!good);
}

bool UI::exec_command(const string & command, bool & done) {
  if (command == "help") {
    cout << "Commands:" << endl;
    cout << "\t* next - displays the next player" << endl;
    cout << "\t* previous - displays the previous player" << endl;
    cout << "\t* add - adds a player" << endl;
    cout << "\t* edit - edits the current player" << endl;
    cout << "\t* delete - deletes the current player" << endl;
    cout << "\t* search - searches for a player" << endl;
    if (isBrowsing_) {
      cout << "\t* new - starts a new season" << endl;
      cout << "\t* stats - display season statistics" << endl;
    }
    else {
      //cout << "\t* print - prints the players to a file" << endl;
      cout << "\t* exit - exits the search view" << endl;
    }
    cout << "\t* save - saves the program" << endl;
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
  else if (command == "new" && isBrowsing_) {
    new_season();
    display();
  }
  else if (command == "stats" && isBrowsing_) {
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
  else if (command == "search") {
    isBrowsing_ = false;
    search();
    display();
  }
  else if (command == "exit" && !isBrowsing_) {
    isBrowsing_ = true;
    display();
  }
  else if (command == "save") {
    season_.save();
    display();
  }
  else if (command == "stop") {
    done = true;
    season_.save();
  }
  else {
    return false;
  }
  return true;
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
    cout << "No previous seasons exist." << endl;
    cout << "Would you like to start a new season? (y/n): ";
    //Get input, make it all lowercase and then see if the user input yes or no
    do {
      getline(cin, input);
      transform(input.begin(), input.end(), input.begin(), ::tolower);
      if (input == "y" || input == "yes") {
        bool temp = true;
        if (exec_command("new", temp)) {
          waiting = false;
          run();
        }
      }
      else if (input == "n" || input == "no") {
          waiting = false;
      }
      else {
        cout << "Please input either yes or no: ";
      }
    } while (waiting);
  }
}

//Run the UI
void UI::run() {
  string input;
  bool done = false;
  cout << ">> ";
  while (!done && getline(cin, input)) {
    if (!exec_command(input, done))
      cout << "Failed to run command: " + input << endl;
    if (!done)
      cout << ">> ";
  }
}
