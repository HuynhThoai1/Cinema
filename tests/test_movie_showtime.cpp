#include <cassert>
#include <iostream>

#include "bus/MovieBUS.h"
#include "bus/ShowtimeBUS.h"

int main() {
    MovieBUS movieBus;
    ShowtimeBUS showBus;

    // Basic add/find
    assert(movieBus.addMovie(Movie("M001", "Test Movie", 120, "Action", "")));
    assert(!movieBus.addMovie(Movie("M001", "Duplicate", 90, "Comedy", "")));
    assert(movieBus.findById("M001") != nullptr);

    assert(showBus.addShowtime(Showtime("S001", "M001", "2025-12-30 19:30", "Room 1")));
    assert(showBus.findById("S001") != nullptr);

    auto byMovie = showBus.findByMovieId("M001");
    assert(byMovie.size() == 1);

    std::cout << "[OK] Movie/Showtime basic tests passed.\n";
    return 0;
}
