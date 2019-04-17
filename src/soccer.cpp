#include "soccer.h"

using namespace std;


//adds a player to the player map
map<string,Player>::iterator Season::add_player(const string & name, const int & birth_year_, const string & status) {

    map<string,Player>::iterator new_entry_;
    if(get_league(birth_year_) != "fail"){
        cout << name << " has been added to the roster" << endl;
        auto entry = players_.insert({get_key(name), {get_first(name), get_last(name), birth_year_, paid(status)}});
        new_entry_ = entry.first;
    }
    else
        cout << "This player does not fit the age requirement" << endl;
    return new_entry_;
}

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
  string last = "";
  int space = 0;
  for(int i = 0; i < name.length(); ++i) {
    if(name[i] == ' ')
      space++;
    if(space == 1)
      last = last + name[i];
  }
  return last;
}

//gets the league the player is in
string Season::get_league(const int & birth_year_){
      const int age = (current_year_ - birth_year_);
      string league = "";
        if(age > 4 && age < 6)
            league = "U6";
        else if(age > 5 && age < 8)
            league = "U8";
        else if(age > 8 && age < 10)
            league = "U10";
        else if(age > 10 && age < 12)
            league = "U12";
        else if(age > 12 && age < 14)
            league = "U14";
        else if(age > 14 && age < 17)
            league = "U17";
        else if(age > 17 || age < 4)
            league = "fail";
        return league;
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
    //add_player(name, year, has_paid);
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
