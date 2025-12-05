#ifndef _SHOWTIME_H_
#define _SHOWTIME_H_

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;

class Showtime {
private:
    string _id;
    string _movieId;
    string _startTime;
    string _room;

public:
    Showtime()
        : _id(""), _movieId(""), _startTime(""), _room("") {
    }

    Showtime(const string& id,
             const string& movieId,
             const string& startTime,
             const string& room)
        : _id(id),
          _movieId(movieId),
          _startTime(startTime),
          _room(room) {
    }

    const string& getId() const { return _id; }
    void setId(const string& id) { _id = id; }

    const string& getMovieId() const { return _movieId; }
    void setMovieId(const string& movieId) { _movieId = movieId; }

    const string& getStartTime() const { return _startTime; }
    void setStartTime(const string& startTime) { _startTime = startTime; }

    const string& getRoom() const { return _room; }
    void setRoom(const string& room) { _room = room; }

    // format: id|movieId|startTime|room
    string serialize() const {
        std::ostringstream oss;
        oss << _id << "|" << _movieId << "|" << _startTime << "|" << _room;
        return oss.str();
    }

    static Showtime deserialize(const string& line) {
        std::istringstream iss(line);
        string id, movieId, startTime, room;

        if (!std::getline(iss, id, '|')) throw std::runtime_error("Invalid line - missing id");
        if (!std::getline(iss, movieId, '|')) throw std::runtime_error("Invalid line - missing movieId");
        if (!std::getline(iss, startTime, '|')) throw std::runtime_error("Invalid line - missing startTime");
        std::getline(iss, room);

        return Showtime(id, movieId, startTime, room);
    }
};

#endif
