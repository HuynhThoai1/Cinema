#ifndef _MOVIEBUS_H_
#define _MOVIEBUS_H_

#include <string>
#include <vector>
#include "Movie.h"

using std::string;
using std::vector;

class MovieBUS {
private:
    vector<Movie> _movies;

public:
    MovieBUS() {}

    const vector<Movie>& getAll() const { return _movies; }

    void load(const string& filename);
    void save(const string& filename) const;

    bool addMovie(const Movie& movie);
    bool deleteMovie(const string& id);
    bool updateMovie(const Movie& movie);

    Movie* findById(const string& id);
    vector<Movie> findByTitle(const string& namePart) const;
};

#endif
