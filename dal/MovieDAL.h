#ifndef _MOVIEDAL_H_
#define _MOVIEDAL_H_

#include <string>
#include <vector>
#include "Movie.h"

using std::string;
using std::vector;

class MovieDAL {
public:
    static vector<Movie> loadFromFile(const string& filename);
    static void saveToFile(const vector<Movie>& list, const string& filename);
};

#endif
