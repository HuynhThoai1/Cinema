#ifndef MOVIEBUS_H
#define MOVIEBUS_H

#include "../dal/MovieDAL.h"
#include <vector>

class MovieBUS {
private:
    MovieDAL _dal;
    vector<Movie> _list;
public:
    MovieBUS() { _list = _dal.getAll(); }

    string getMovieNameById(string id) {
        for (const auto& m : _list) {
            if (m.getId() == id) return m.getTitle();
        }
        return "Unknown Movie";
    }
    vector<Movie> getAllMovies() {
        return _list;
    }
    void getallMovies() {
        for (const auto& m : _list) {
            std::cout << "ID: " << m.getId() << " | Title: " << m.getTitle() << " | Genre: " << m.getGenre() << " | Duration: " << m.getDuration() << " mins\n";
        }
    }
};

#endif