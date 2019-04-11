#include "Soccer.h"
using namespace std;

string Season::get_key(const string & Name)
{
    string key = "";
    for(int i = 0; i < Name.length(); ++i)
    {
        if(Name[i] == ' ')
        {
            ++i;
            while(i < Name.length())
            {
                key = key + Name[i];
                ++i;
            }
            key = key + ", ";
            i = 0;
            while(Name[i] != ' ')
            {
                key = key + Name[i];
                ++i;
            }
            i = Name.length();
        }
    }
    return key;
}
string Season::get_first(const string & Name)
{
    std::string first = "";
    int i = 0;
    while(Name[i] != ' ')
        first = first + Name[i];
    return first;
}

string Season::get_last(const string & Name)
{
    std::string last = "";
    int space = 0;
    for(int i = 0; i < Name.length(); ++i)
    {
        if(Name[i] == ' ')
            space++;
        if(space == 1)
            last = last + Name[i];
    }
    return last;
}
