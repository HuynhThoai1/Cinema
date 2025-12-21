#include "MovieBUS.h"
#include <algorithm>

MovieBUS::MovieBUS(MovieDAL movieDal) : movieDal(std::move(movieDal)) {}

std::vector<Movie> MovieBUS::getAll() {
    return movieDal.loadMovies();
}

bool MovieBUS::addMovie(const Movie& movie) {
    auto movies = movieDal.loadMovies();
    auto it = std::find_if(movies.begin(), movies.end(),
                           [&](const Movie& m) { return m.getId() == movie.getId(); });
    if (it != movies.end()) return false;

    movies.push_back(movie);
    movieDal.saveMovies(movies);
    return true;
}

bool MovieBUS::updateMovie(const Movie& movie) {
    auto movies = movieDal.loadMovies();
    auto it = std::find_if(movies.begin(), movies.end(),
                           [&](const Movie& m) { return m.getId() == movie.getId(); });
    if (it == movies.end()) return false;

    *it = movie;
    movieDal.saveMovies(movies);
    return true;
}

bool MovieBUS::deleteMovie(const std::string& id) {
    auto movies = movieDal.loadMovies();
    auto before = movies.size();
    movies.erase(std::remove_if(movies.begin(), movies.end(),
                               [&](const Movie& m) { return m.getId() == id; }),
                 movies.end());
    if (movies.size() == before) return false;

    movieDal.saveMovies(movies);
    return true;
}
