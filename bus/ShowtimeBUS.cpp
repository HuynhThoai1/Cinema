#include "ShowtimeBUS.h"

void ShowtimeBUS::load(const string& filename) {
    _showtimes = ShowtimeDAL::loadFromFile(filename);
}

void ShowtimeBUS::save(const string& filename) const {
    ShowtimeDAL::saveToFile(_showtimes, filename);
}

vector<Showtime> ShowtimeBUS::getAll() const {
    return _showtimes; // copy, an toàn cho caller
}

bool ShowtimeBUS::addShowtime(const Showtime& s) {
    // Không cho trùng id
    for (size_t i = 0; i < _showtimes.size(); ++i) {
        if (_showtimes[i].getId() == s.getId()) {
            return false;
        }
    }
    _showtimes.push_back(s);
    return true;
}

bool ShowtimeBUS::deleteShowtime(const string& id) {
    for (size_t i = 0; i < _showtimes.size(); ++i) {
        if (_showtimes[i].getId() == id) {
            _showtimes.erase(_showtimes.begin() + i);
            return true;
        }
    }
    return false;
}

bool ShowtimeBUS::updateShowtime(const Showtime& s) {
    for (size_t i = 0; i < _showtimes.size(); ++i) {
        if (_showtimes[i].getId() == s.getId()) {
            _showtimes[i] = s;
            return true;
        }
    }
    return false;
}

Showtime* ShowtimeBUS::findById(const string& id) {
    for (size_t i = 0; i < _showtimes.size(); ++i) {
        if (_showtimes[i].getId() == id) {
            return &_showtimes[i];
        }
    }
    return nullptr;
}

vector<Showtime> ShowtimeBUS::getByMovieId(const string& movieId) const {
    vector<Showtime> result;
    for (size_t i = 0; i < _showtimes.size(); ++i) {
        if (_showtimes[i].getMovieId() == movieId) {
            result.push_back(_showtimes[i]);
        }
    }
    return result;
}
