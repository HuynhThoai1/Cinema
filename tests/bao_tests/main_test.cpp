#include <iostream>
#include <string>
#include <vector>

#include "../../dto/Movie.h"
#include "../../dto/Showtime.h"
#include "../../bus/MovieBUS.h"
#include "../../bus/ShowtimeBUS.h"
#include "../../dal/MovieDAL.h"
#include "../../dal/ShowtimeDAL.h"

using std::cout;
using std::string;

int main() {
    cout << "MOVIE MODULE\n";

    // chạy test từ thư mục root (Cinema/) => data/...
    const string movieFile = "data/Movies.txt";
    MovieBUS movieBus{MovieDAL(movieFile)};

    // add movies
    bool m1 = movieBus.addMovie(Movie("M001", "Avengers: Endgame", "Action", 181));
    bool m2 = movieBus.addMovie(Movie("M002", "Spirited Away", "Animation", 125));

    cout << "addMovie(M001): " << (m1 ? "OK" : "SKIP (exists)") << "\n";
    cout << "addMovie(M002): " << (m2 ? "OK" : "SKIP (exists)") << "\n";

    auto movies = movieBus.getAll();
    cout << "Total movies: " << movies.size() << "\n";
    for (const auto& m : movies) {
        cout << m.getId() << " | " << m.getTitle()
             << " | " << m.getGenre()
             << " | " << m.getDuration() << "\n";
    }

    cout << "\nSHOWTIME MODULE \n";

    const string showFile = "data/Showtime.txt";
    ShowtimeBUS showBus{ShowtimeDAL(showFile)};

    // Showtime ctor: (id, movieId, room, startTime)
    bool s1 = showBus.addShowtime(Showtime("S001", "M001", "Room 1", "2025-12-30 19:30"));
    bool s2 = showBus.addShowtime(Showtime("S002", "M001", "Room 1", "2025-12-05 22:00"));

    cout << "addShowtime(S001): " << (s1 ? "OK" : "SKIP (exists)") << "\n";
    cout << "addShowtime(S002): " << (s2 ? "OK" : "SKIP (exists)") << "\n";

    auto showtimes = showBus.getByMovie("M001");
    cout << "Showtimes for M001: " << showtimes.size() << "\n";
    for (const auto& s : showtimes) {
        cout << s.getId() << " | " << s.getMovieId()
             << " | " << s.getRoom()
             << " | " << s.getStartTime() << "\n";
    }

    cout << "\n===== [BAO TEST] DONE =====\n";
    return 0;
}
