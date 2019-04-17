#include "soccer.h"

using namespace std;

//Returns a key to the player in the map
string Season::get_key(const string & name) {
  string key = "";
  for(int i = 0; i < name.length(); ++i) {
    if(name[i] == ' ') {
      ++i;
      while(i < name.length()) {
        key = key + name[i];
        ++i;
      }
      key = key + ", ";
      i = 0;
      while(name[i] != ' ') {
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
  int i = 0;
  while(name[i] != ' ')
    first = first + name[i];
  return first;
}

//Gets a player's last name
string Season::get_last(const string & name) {
  std::string last = "";
  int space = 0;
  for(int i = 0; i < name.length(); ++i) {
    if(name[i] == ' ')
      space++;
    if(space == 1)
      last = last + name[i];
  }
  return last;
}

//Opens the season file
bool Season::open(const string & file) {
  ifstream in(file);
  if (!in)
    return false;
  
  string first_name;
  string last_name;
  int year;
  bool has_paid;
  stringstream ss;
  string temp;

  //Not tested yet
  in >> current_year_;
  while (getline(in, temp)) {
    ss.str(temp);
    ss >> first_name >> last_name >> year >> boolalpha >> has_paid;
    //Could be a bit more efficient
    string name = first_name + " " + last_name;
    add_player(name, year, has_paid);
  }
  return true;
}

//Passed by value because it gets changed and I'm not sure if
//the original should be changed or not
bool Season::paid(std::string status) {
  bool has_paid = false;
  //Makes status all lowercase
  std::transform(status.begin(), status.end(), status.begin(), ::tolower);
  if(status == "paid")
    has_paid = true;
  return has_paid;
}
