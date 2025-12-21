#ifndef BUS_MOVIEBUS_H
#define BUS_MOVIEBUS_H

#include <string>
#include <vector>

#include "../dal/MovieDAL.h"

/**
 * @class MovieBUS
 * @brief Business Layer quản lý phim.
 */
class MovieBUS {
private:
    MovieDAL movieDal;

public:
    explicit MovieBUS(MovieDAL movieDal = MovieDAL());

    std::vector<Movie> getAll();
    bool addMovie(const Movie& movie);
    bool updateMovie(const Movie& movie);
    bool deleteMovie(const std::string& id);
};

#endif // BUS_MOVIEBUS_H
