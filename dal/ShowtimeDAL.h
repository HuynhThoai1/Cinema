#ifndef _SHOWTIMEDAL_H_
#define _SHOWTIMEDAL_H_

#include <string>
#include <vector>
#include "Showtime.h"

using std::string;
using std::vector;

class ShowtimeDAL {
public:
    static vector<Showtime> loadFromFile(const string& filename);
    static void saveToFile(const vector<Showtime>& list, const string& filename);
};

#endif
