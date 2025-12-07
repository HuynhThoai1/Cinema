#ifndef SHOWTIME_H
#define SHOWTIME_H

#include <string>
using namespace std;

class Showtime {
private:
    string _id;
    string _movieId; // Khóa ngoại tham chiếu đến Movie
    string _room;
    string _startTime;
    string _date;

public:
    Showtime() : _id("") {} // Constructor mặc định (rỗng)
    Showtime(string id, string mId, string room, string time, string date)
        : _id(id), _movieId(mId), _room(room), _startTime(time), _date(date) {}

    string getId() const { return _id; }
    string getMovieId() const { return _movieId; }
    string getRoom() const { return _room; }
    string getStartTime() const { return _startTime; }
    string getDate() const { return _date; }
};

#endif