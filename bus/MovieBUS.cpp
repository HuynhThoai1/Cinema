#include "MovieBUS.h"
#include "MovieDAL.h"
#include <algorithm>

void MovieBUS::load(const string& filename) {
    _movies = MovieDAL::loadFromFile(filename);
}

void MovieBUS::save(const string& filename) const {
    MovieDAL::saveToFile(_movies, filename);
}

bool MovieBUS::addMovie(const Movie& movie) {
    for (size_t i = 0; i < _movies.size(); i++) {
        if (_movies[i].getId() == movie.getId()) return false;
    }
    _movies.push_back(movie);
    return true;
}

bool MovieBUS::deleteMovie(const string& id) {
    for (size_t i = 0; i < _movies.size(); i++) {
        if (_movies[i].getId() == id) {
            _movies.erase(_movies.begin() + i);
            return true;
        }
    }
    return false;
}

bool MovieBUS::updateMovie(const Movie& movie) {
    for (size_t i = 0; i < _movies.size(); i++) {
        if (_movies[i].getId() == movie.getId()) {
            _movies[i] = movie;
            return true;
        }
    }
    return false;
}

Movie* MovieBUS::findById(const string& id) {
    for (size_t i = 0; i < _movies.size(); i++) {
        if (_movies[i].getId() == id) return &_movies[i];
    }
    return nullptr;
}

vector<Movie> MovieBUS::findByTitle(const string& namePart) const {
    vector<Movie> result;
    for (size_t i = 0; i < _movies.size(); i++) {
        if (_movies[i].getTitle().find(namePart) != string::npos) {
            result.push_back(_movies[i]);
        }
    }
    return result;
}
