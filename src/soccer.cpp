
#include "soccer.h"

using namespace std;

typedef map<string, Player> PlayerMap;
typedef map<string, Stat> StatMap;


void Season::print_players(const string & FileName) {

    update_stats();
    vector<Player> players_U6;
    vector<Player> players_U8;
    vector<Player> players_U10;
    vector<Player> players_U12;
    vector<Player> players_U14;
    vector<Player> players_U17;
    //cout << "GOT HERE" << endl;
    auto league_itr = stats_.begin();
    auto itr = players_.begin();
    for(itr; league_itr != stats_.end(); ++itr)
    {
        if(("U" + to_string(get_league_(itr -> second.year))) == league_itr -> first)
        {
            if(league_itr -> first == "U6")
                players_U6.push_back(itr -> second);
            else if(league_itr -> first == "U8")
                players_U8.push_back(itr -> second);
            else if(league_itr -> first == "U10")
                players_U10.push_back(itr -> second);
            else if(league_itr -> first == "U12")
                players_U12.push_back(itr -> second);
            else if(league_itr -> first == "U14")
                players_U14.push_back(itr -> second);
            else if(league_itr -> first == "U17")
                players_U17.push_back(itr -> second);
        }
        if(itr == players_.end())
        {
            itr = players_.begin();
            ++league_itr;
        }
    }
    //cout << "And now Here" << endl;
    league_itr = stats_.begin();
    ++league_itr;
    ofstream OutData;
    OutData.open(FileName);
    OutData << "Format: Name, Year of Birth, Paid Status" << endl;
    while(league_itr != stats_.end()){
        if(league_itr -> first == "U6") {
            OutData << "League: U6" << endl;
            auto itr = players_U6.begin();
            while(itr != players_U6.end()) {
                OutData << itr -> first << itr -> last << " " << itr -> year << " " << itr -> paid << endl;
                ++itr;
            }
            ++league_itr;
        }
        else if(league_itr -> first == "U8"){
            OutData << "League: U8" << endl;
            auto itr = players_U8.begin();
            while(itr != players_U8.end()) {
                OutData << itr -> first << itr -> last << " " << itr -> year << " " << itr -> paid << endl;
                ++itr;
            }
            ++league_itr;
        }
        else if(league_itr -> first == "U10") {
            OutData << "League: U10" << endl;
            auto itr = players_U10.begin();
            while(itr != players_U10.end()) {
                OutData << itr -> first << itr -> last << " " << itr -> year << " " << itr -> paid << endl;
                ++itr;
            }
            ++league_itr;
        }
        else if(league_itr -> first == "U12") {
            OutData << "League: U12" << endl;
            auto itr = players_U12.begin();
            while(itr != players_U12.end()) {
                OutData << itr -> first << itr -> last << " " << itr -> year << " " << itr -> paid << endl;
                ++itr;
            }
            ++league_itr;
        }
        else if(league_itr -> first == "U14") {
            OutData << "League: U14" << endl;
            auto itr = players_U14.begin();
            while(itr != players_U14.end()) {
                OutData << itr -> first << itr -> last << " " << itr -> year << " " << itr -> paid << endl;
                ++itr;
            }
            ++league_itr;
        }
        else if(league_itr -> first == "U17") {
            OutData << "League: U17" << endl;
            auto itr = players_U17.begin();
            while(itr != players_U17.end()) {
                OutData << itr -> first << itr -> last << " " << itr -> year << " " << itr -> paid << endl;
                ++itr;
            }
            ++league_itr;
        }
    }
    cout << "Finished Printing" << endl;
}

string Season::display_name() {
    return (current_player_ -> second.first) + (current_player_ -> second.last);

 }
string Season::display_year() {
    return  to_string(current_player_ -> second.year);
}
string Season::display_league() {
    return ("U" + to_string(get_league_(current_player_ -> second.year)));
}
string Season::display_status() {
    string status;
    if(current_player_ -> second.paid)
        status = "Paid";
    else
        status = "Not Paid";
    return status;
}


void Season::update_stats() {

    stats_.clear();
    stats_.insert({"Total", {"Total"}});
    for(auto itr = players_.begin(); itr != players_.end(); ++itr)
    {
        string league = "U" + to_string(get_league_(itr -> second.year));
        if(stats_.find(league) != stats_.end())
        {
            add_stat(league, (itr -> second.paid));
        }
        else
        {
            stats_.insert({league, {league}});
            add_stat(league, (itr -> second.paid));
        }
    }
}

void Season::add_stat(std::string key, bool status) {

    auto itr = stats_.find(key);
    auto total = stats_.find("Total");
    if(status == true)
    {
        ++(itr -> second.players);
        ++(itr -> second.paid);
        ++(total -> second.players);
        ++(total -> second.paid);
    }
    else
    {
        ++(itr -> second.players);
        ++(itr -> second.not_paid);
        ++(total -> second.players);
        ++(total -> second.not_paid);
    }
}

//starts a new season
void Season::new_season(const int new_year)
{
  current_year_ = new_year;
  players_.clear();
  current_player_ = players_.end();
  current_player_pos_ = 0;
}

//Adds a player to the player map
void Season::add_player(const string & name, const int birth_year, const bool & status) {

  if (get_league_(birth_year) != -1) {
    auto entry = players_.insert({get_key_(name), {get_first_(name), get_last_(name), birth_year, status}});
    current_player_ = entry.first;
  }
}

//Edits a player by deleting that player and adds a new player with the edited info

void Season::edit_player(string new_name, int new_year, bool new_paid) {
    delete_player();
    add_player(new_name, new_year, new_paid);
}

void Season::delete_player() {
    players_.erase(current_player_->first);
    next_player();
}

//Returns a key to the player in the map
string Season::get_key_(const string & name) {
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
string Season::get_first_(const string & name) {
  std::string first = "";
  for (int i = 0; name[i] != ' '; ++i)
    first = first + name[i];
  return first;
}

//Gets a player's last name
string Season::get_last_(const string & name) {
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

//Gets the league the player is in
int Season::get_league_(const int birth_year) {
  const int age = (current_year_ - birth_year);
  if (age >= 4 && age < 6)
    return 6;
  else if (age >= 6 && age < 8)
    return 8;
  else if (age >= 8 && age < 10)
    return 10;
  else if (age >= 10 && age < 12)
    return 12;
  else if (age >= 12 && age < 14)
    return 14;
  else if (age >= 14 && age < 17)
    return 17;
  return -1;
}

//Opens the season file
bool Season::open() {
  ifstream in(file_);
  if (!in)
    return false;

  string first_name;
  string last_name;
  int year;
  bool status;
  stringstream year_stream;
  string temp;

  //Use a string stream to santize input
  getline(in, temp);
  year_stream.str(temp);
  temp = "";

  //If stream state is invalid fail to open the file
  if (!year_stream)
    return false;

  year_stream >> current_year_;
  while (getline(in, temp)) {
    stringstream ss(temp);
    ss >> first_name >> last_name >> year >> status;
    if (ss) {
      //Could be a bit more efficient
      string name = first_name + " " + last_name;
      add_player(name, year, status);
    }
  }
  //Initialize the current player
  current_player_ = players_.begin();
  current_player_pos_ = 1;
  return true;
}

bool Season::save() {
  ofstream out(file_);
  if (!out)
    return false;

  out << current_year_ << endl;

  for (auto e: players_) {
    out << e.second.first << ' ' << e.second.last << ' ';
    out << e.second.year << ' ' << e.second.paid << endl;
  }
  out.close();

  return true;
}

void Season::search(const string & first, const string & last, const int year,
                    const bool search_paid, const bool paid) {
}
