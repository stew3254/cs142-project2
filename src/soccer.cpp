#include "soccer.h"

using namespace std;

typedef map<string, Player> PlayerMap;

//Adds a player to the player map
PlayerMap::iterator Season::add_player(const string & name,
const int birth_year, const string & status) {
  map<string,Player>::iterator new_entry_;
  if (get_league(birth_year) != -1) {
    auto entry = players_.insert({get_key(name),
        {get_first(name), get_last(name), birth_year, paid(status)}});
    new_entry_ = entry.first;
  }
  else
    new_entry_ = players_.end();
  return new_entry_;
}

//Edits a player by deleting that player and adds a new player with the edited info
PlayerMap::iterator Season::edit_player(string new_name, int new_year, string new_paid) {
    delete_player();
    return add_player(new_name, new_year, new_paid);
}

PlayerMap::iterator Season::delete_player() {
   players_.erase(current_player_->first);
   ++current_player_;
   return current_player_;
}

//Returns a key to the player in the map
string Season::get_key(const string & name) {
  string key = "";
  for (int i = 0; i < name.length(); ++i) {
    if (name[i] == ' ') {
      ++i;
      while (i < name.length()) {
        key = key + name[i];
        ++i;
      }
      key = key + ", ";
      i = 0;
      while (name[i] != ' ') {
        key = key + name[i];
        ++i;
      }
      i = name.length();
    }
  }
  return key;
}

//Gets a player's first name
string Season::get_first(const string & name) {
  std::string first = "";
  for (int i = 0; name[i] != ' '; ++i)
    first = first + name[i];
  return first;
}

//Gets a player's last name
string Season::get_last(const string & name) {
  string last = "";
  int space = 0;
  for (int i = 0; i < name.length(); ++i) {
    if (name[i] == ' ')
      space++;
    if (space == 1)
      last = last + name[i];
  }
  return last;
}

//gets the league the player is in
int Season::get_league(const int birth_year) {
  const int age = (current_year_ - birth_year);
  if (age > 4 && age < 6)
    return 6;
  else if (age > 5 && age < 8)
    return 8;
  else if (age > 8 && age < 10)
    return 10;
  else if (age > 10 && age < 12)
    return 12;
  else if (age > 12 && age < 14)
    return 14;
  else if (age > 14 && age < 17)
    return 17;
  return -1;
}

//Opens the season file
bool Season::open(const string & file) {
  ifstream in(file);
  if (!in)
    return false;

  string first_name;
  string last_name;
  int year;
  string status;
  string temp;

  in >> current_year_;
  while (in >> first_name >> last_name >> year >> status) {
    //Could be a bit more efficient
    string name = first_name + " " + last_name;
    add_player(name, year, status);
  }
  //Initialize the current player
  current_player_ = players_.begin();
  current_player_pos_ = 1;
  return true;
}

//Passed by value because it gets changed and I'm not sure if
//the original should be changed or not
bool Season::paid(std::string status) {
  bool has_paid = false;
  //Makes status all lowercase
  std::transform(status.begin(), status.end(), status.begin(), ::tolower);
  if (status == "paid")
    has_paid = true;
  return has_paid;
}
