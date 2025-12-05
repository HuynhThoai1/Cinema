#include <iostream>
#include "dto/Movie.h"
#include "dal/MovieDAL.h"
#include "bus/MovieBUS.h"
#include "dto/Showtime.h"
#include "dal/ShowtimeDAL.h"

using std::cout;
using std::string;
using std::vector;

int main() {
    cout << "TEST MODULE PHIM\n";

    MovieBUS movieBus;

    string movieFile = "Movies.txt";

    movieBus.load(movieFile);

    movieBus.addMovie(Movie("M001", "Avengers: Endgame", 181, "Action", "2025-12-05 19:30 - Room 1"));
    movieBus.addMovie(Movie("M002", "Spirited Away", 125, "Animation", "2025-12-06 20:00 - Room 2"));

    movieBus.save(movieFile);

    for (const Movie& m : movieBus.getAll()) {
        cout << m.getId() << " | " << m.getTitle()
             << " | " << m.getGenre()
             << " | " << m.getDuration()
             << " | " << m.getShowtime() << "\n";
    }

    cout << "\nTEST SUẤT CHIẾU\n";

    vector<Showtime> list;
    list.push_back(Showtime("S001", "M001", "2025-12-30 19:30", "Room 1"));
    list.push_back(Showtime("S002", "M001", "2025-12-05 22:00", "Room 1"));

    string showFile = "Showtime.txt";

    ShowtimeDAL::saveToFile(list, showFile);

    auto loaded = ShowtimeDAL::loadFromFile(showFile);

    for (const Showtime& s : loaded) {
        cout << s.getId() << " | " << s.getMovieId()
             << " | " << s.getStartTime()
             << " | " << s.getRoom() << "\n";
    }

    return 0;
}
