#ifndef SHOWTIMEBUS_H
#define SHOWTIMEBUS_H

#include "ShowtimeDAL.h"
#include <vector>

class ShowtimeBUS {
private:
    ShowtimeDAL _dal;
    vector<Showtime> _list;
public:
    ShowtimeBUS() { _list = _dal.getAll(); }

    Showtime getShowtimeById(string id) {
        for (const auto& s : _list) {
            if (s.getId() == id) return s;
        }
        return Showtime(); // Trả về object rỗng nếu không thấy
    }
    vector<Showtime> getByMovie(string movieId) {
        vector<Showtime> result;
        for (const auto& s : _list) {
            if (s.getMovieId() == movieId) {
                result.push_back(s);
            }
        }
        return result;
    }
    void printByMovie(string movieId) {
        for (const auto& s : _list) {
            if (s.getMovieId() == movieId) {
                std::cout << "Showtime ID: " << s.getId() << " | Room: " << s.getRoom() 
                          << " | Start Time: " << s.getStartTime() << " | Date: " << s.getDate() << "\n";
            }
        }
    }
};

#endif