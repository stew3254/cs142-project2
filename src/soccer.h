#ifndef soccer_h_
#define soccer_h_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

struct Player {
  Player() : Player("No ", "Name", 2000, false) {}
  Player(const std::string & f, const std::string & l, const int & b, const bool & p) :
      first(f), last(l), year(b), paid(p) {}
  std::string first;
  std::string last;
  int year;
  bool paid;
};

struct Stat {
  Stat(const std::string & key) : Stat(key, 0, 0, 0) {}
  Stat(const std::string & key, const int & number, const int & yes, const int & no) : league(key), players(number), paid(yes), not_paid(no) {}

  std::string league;
  int players;
  int paid;
  int not_paid;
};

class Season {
public:
  typedef std::map<std::string, Player> PlayerMap;
  typedef std::map<std::string, Stat> StatMap;

  Season() : Season(2000) {}
  Season(const int & y) : current_year_(y), file_("season.txt") {}

  void print_players(const std::string & FileName);

  void update_stats();

  void add_player(const std::string & name, const int birth_year, const bool & status);
  void edit_player(std::string new_name, int new_year, bool new_paid);
  void delete_player();

  bool empty() {return players_.empty();}

  void new_season(const int new_year);

  std::string display_name();
  std::string display_year();
  std::string display_league();
  std::string display_status();

  StatMap::iterator get_end_stat(){return stats_.end();}
  StatMap::iterator get_stats(){return stats_.begin();}
  PlayerMap::iterator get_current_player() {return current_player_;}
  size_t get_current_pos() {return current_player_pos_;}
  size_t get_player_count() {return players_.size();}

  void next_player();
  void previous_player();

  bool open();
  bool save();

  void search(const std::string & first, const std::string & last, const int year, const bool search_paid, const bool paid);
  int year() {return current_year_;}

private:
  std::string get_key_(const std::string & name);
  std::string get_first_(const std::string & name);
  std::string get_last_(const std::string & name);
  int get_league_(const int birth_year);

  void add_stat(std::string, bool status);

  int current_year_;
  std::string file_;

  StatMap stats_;

  PlayerMap search_players_;
  PlayerMap::iterator current_search_player_;

  PlayerMap players_;
  PlayerMap::iterator current_player_;
  
  size_t current_player_pos_;
};

inline void Season::next_player() {
  if (players_.size() != 0) {
    if (current_player_ != --(players_.end())) {
      ++current_player_;
      ++current_player_pos_;
    }
    else {
      current_player_ = players_.begin();
      current_player_pos_ = 1;
    }
  }
}

inline void Season::previous_player() {
  if (players_.size() != 0) {
    if (current_player_ != players_.begin()) {
      --current_player_;
      --current_player_pos_;
    }
    else {
      current_player_ = --(players_.end());
      current_player_pos_ = players_.size();
    }
  }
}

#endif // soccer_h_
