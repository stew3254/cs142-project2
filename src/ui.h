#ifndef _ui_h_
#define _ui_h_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include "soccer.h"

class UI {
public:
  UI() : isBrowsing_(true) {}

  bool exec_command(const std::string & command, bool & done);
  void display();
  void start();
  void run();

private:
  void get_player_details(std::string & name, int & year, bool & paid);
  void search();
  void new_season();
  Season season_;
  bool isBrowsing_;
};

#endif
