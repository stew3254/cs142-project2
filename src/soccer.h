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


  void add_player(const std::string & name, const int birth_year, const bool & status);
  void edit_player(std::string new_name, int new_year, bool new_paid);
  void delete_player();


  void new_season(int new_year);
  void display();
  std::string get_key(const std::string & name);
  std::string get_first(const std::string & name);
  std::string get_last(const std::string & name);
  size_t get_current_pos() {return current_player_pos_;}
  size_t get_player_count() {return players_.size();}
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
  size_t current_player_pos_;
};

inline void Season::display() {
  std::cout << current_player_->second.first << ' ' << current_player_->second.last << std::endl;
}

inline void Season::next_player() {
  if (current_player_ != --(players_.end())) {
    ++current_player_;
    ++current_player_pos_;
  }
  else {
    current_player_ = players_.begin();
    current_player_pos_ = 1;
  }
}

inline void Season::previous_player() {
  if (current_player_ != players_.begin()) {
    --current_player_;
    --current_player_pos_;
  }
  else {
    current_player_ = --(players_.end());
    current_player_pos_ = players_.size();
  }
}

#endif // soccer_h_
