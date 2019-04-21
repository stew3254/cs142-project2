#ifndef soccer_h_
#define soccer_h_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

struct Player {
  Player() : Player("No ", "Name", 2000, false) {}
  Player(const std::string & f, const std::string & l, const int & b,
         const bool & p) : first(f), last(l), year(b), paid(p) {}

  std::string first;
  std::string last;
  int year;
  bool paid;
};

class Season {
public:
  typedef std::map<std::string, Player> PlayerMap;
  Season() : Season(2000) {}
  Season(const int & y) : current_year_(y) {}

  std::map<std::string, Player>::iterator add_player(const std::string & name, const int birth_year, const std::string & status);
  std::map<std::string, Player>::iterator edit_player();
  std::map<std::string, Player>::iterator delete_player();


  void display();
  std::string get_key(const std::string & name);
  std::string get_first(const std::string & name);
  std::string get_last(const std::string & name);
  int get_league(const int birth_year);
  void next_player();
  void previous_player();
  bool open(const std::string & file);
  bool paid(std::string status);
  int year() {return current_year_;}

private:
  int current_year_;
  PlayerMap players_;
  PlayerMap::iterator current_player_;
};

inline void Season::display() {
  std::cout << current_player_->second.first << ' ' << current_player_->second.last << std::endl;
}

inline void Season::next_player() {
  if (current_player_ != --(players_.end()))
    ++current_player_;
  else
    current_player_ = players_.begin();
}

inline void Season::previous_player() {
  if (current_player_ != players_.begin())
    --current_player_;
  else
    current_player_ = --(players_.end());
}

#endif // soccer_h_
