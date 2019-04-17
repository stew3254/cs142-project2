#ifndef soccer_h_
#define soccer_h_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

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
  Season() : Season(2000) {}
  Season(const int & y) : current_year_(y) {}
  std::map<std::string,Player>::iterator add_player(const std::string & name, const int & birth_year_, const std::string & status);
  std::string get_key(const std::string & name);
  std::string get_first(const std::string & name);
  std::string get_last(const std::string & name);
  std::string get_league(const int & birth_year_);
  bool open(const std::string & file);
  bool paid(std::string status);
  int year() {return current_year_;}

private:
  int current_year_;
  std::map<std::string, Player> players_;
  std::map<std::string, Player>::iterator current_entry_;
};

#endif // soccer_h_
