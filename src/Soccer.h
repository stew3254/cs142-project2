#ifndef SOCCER_H_INCLUDED
#define SOCCER_H_INCLUDED

#include <iostream>
#include <map>
#include <string>

struct Player
{
    Player() : Player("No ", "Name", 2000, false) {}
    Player(const std::string & F, const std::string & L, const int & B, const bool & P) : First_(F), Last_(L), Birth_(B), Paid_(P) {}

    std::string First_;
    std::string Last_;
    int Birth_;
    bool Paid_;
};

class Season
{
public:
    Season() : Season(2000){}
    Season(const int & y) : Current_Year_(y){}

    void add_player(const std::string & Name, const int & Birth, const std::string & Status);

    std::string get_first(const std::string & Name);

    std::string get_key(const std::string & Name);

    std::string get_last(const std::string & Name);

    bool paid(const std::string & Status);

    int year(){return Current_Year_;}


private:
    int Current_Year_;
    std::map<std::string, Player> Players_;
    std::map<std::string, Player>::iterator Current_Entry_;
};

inline void Season::add_player(const std::string & Name, const int & Birth, const std::string & Status)
{
    Players_.insert({get_key(Name), {get_first(Name), get_last(Name), Birth, paid(Status)}});
}

inline bool Season::paid(const std::string & Status)
{
    bool paid = false;
    if(Status == "Paid" || Status == "paid")
        paid = true;
    return paid;
}

#endif // SOCCER_H_INCLUDED
