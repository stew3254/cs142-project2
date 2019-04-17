#ifndef _ui_h_
#define _ui_h_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include "soccer.h"

class UI {
public:
  void display();
  void start();
  bool run();

private:
  Season season_;
};

#endif
