#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;

class Movie {
private:
    string _id;
    string _title;
    int    _duration;
    string _genre;
    string _showtime;

public:
    Movie()
        : _id(""), _title(""), _duration(0), _genre(""), _showtime("") {
    }

    Movie(const string& id,
          const string& title,
          int duration,
          const string& genre,
          const string& showtime)
        : _id(id),
          _title(title),
          _duration(duration),
          _genre(genre),
          _showtime(showtime) {
    }

    const string& getId() const { return _id; }
    void setId(const string& id) { _id = id; }

    const string& getTitle() const { return _title; }
    void setTitle(const string& title) { _title = title; }

    int getDuration() const { return _duration; }
    void setDuration(int duration) { _duration = duration; }

    const string& getGenre() const { return _genre; }
    void setGenre(const string& genre) { _genre = genre; }

    const string& getShowtime() const { return _showtime; }
    void setShowtime(const string& showtime) { _showtime = showtime; }

    // format: id|title|duration|genre|showtime
    string serialize() const {
        std::ostringstream oss;
        oss << _id << "|" << _title << "|" << _duration
            << "|" << _genre << "|" << _showtime;
        return oss.str();
    }

    static Movie deserialize(const string& line) {
        std::istringstream iss(line);
        string id, title, durationStr, genre, showtime;

        if (!std::getline(iss, id, '|')) throw std::runtime_error("Invalid line - missing id");
        if (!std::getline(iss, title, '|')) throw std::runtime_error("Invalid line - missing title");
        if (!std::getline(iss, durationStr, '|')) throw std::runtime_error("Invalid line - missing duration");
        if (!std::getline(iss, genre, '|')) throw std::runtime_error("Invalid line - missing genre");
        std::getline(iss, showtime);

        int duration = 0;
        try { duration = std::stoi(durationStr); }
        catch (...) { throw std::runtime_error("Invalid duration number"); }

        return Movie(id, title, duration, genre, showtime);
    }
};

#endif
