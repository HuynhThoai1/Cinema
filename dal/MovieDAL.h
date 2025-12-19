#ifndef DAL_MOVIEDAL_H
#define DAL_MOVIEDAL_H

#include <string>
#include <vector>

#include "dto/Movie.h"

/**
 * @class MovieDAL
 * @brief Data Access Layer cho Movie (đọc/ghi Movies.txt).
 */
class MovieDAL {
private:
    std::string filePath;

public:
    explicit MovieDAL(std::string filePath = "Movies.txt");

    std::vector<Movie> loadMovies();
    void saveMovies(const std::vector<Movie>& movies);
};

#endif // DAL_MOVIEDAL_H
