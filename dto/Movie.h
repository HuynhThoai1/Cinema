#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Movie {
private:
    string _id;
    string _title;
    string _genre;
    int _duration; // phút

public:
    Movie() {}
    Movie(string id, string title, string genre, int duration) 
        : _id(id), _title(title), _genre(genre), _duration(duration) {}

    string getId() const { return _id; }
    string getTitle() const { return _title; }
    string getGenre() const { return _genre; }
    int getDuration() const { return _duration; }
};

#endif