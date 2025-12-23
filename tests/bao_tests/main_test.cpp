#include "../../bus/MovieBUS.h"
#include "../../bus/ShowtimeBUS.h"
#include "../../dal/MovieDAL.h"
#include "../../dal/ShowtimeDAL.h"

#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::string;

static void writeText(const string& path, const string& content) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out << content;
}

static bool expect(bool cond, const string& name) {
    cout << (cond ? "[PASS] " : "[FAIL] ") << name << "\n";
    return cond;
}

int main() {
    cout << "===== BAO EDGE-CASE TEST (Movie + Showtime) =====\n";

    const string moviesFile    = "tests/bao_tests/test_movies.txt";
    const string showtimesFile = "tests/bao_tests/test_showtimes.txt";

    // Seed data (intentionally includes both supported formats)
    // Movie formats:
    //  A) id|title|genre|duration
    //  B) id|title|duration|genre|extra...
    writeText(moviesFile,
        "M001|Movie One|Action|120\n"
        "M002|Movie Two|150|Drama|IGNORED_FIELD\n"
    );

    // Showtime format: id|movieId|startTime|room
    writeText(showtimesFile,
        "S001|M001|2025-12-23 10:30|R1\n"
    );

    MovieDAL movieDal(moviesFile);
    ShowtimeDAL showtimeDal(showtimesFile);

    MovieBUS movieBus(movieDal, showtimeDal);
    ShowtimeBUS showtimeBus(showtimeDal, movieDal);

    bool okAll = true;

    // -----------------
    // Movie edge cases
    // -----------------
    okAll &= expect(!movieBus.addMovie(Movie("", "x", "y", 100)),
                    "Movie: reject empty id");
    okAll &= expect(!movieBus.addMovie(Movie("M003", "", "y", 100)),
                    "Movie: reject empty title");
    okAll &= expect(!movieBus.addMovie(Movie("M003", "x", "", 100)),
                    "Movie: reject empty genre");
    okAll &= expect(!movieBus.addMovie(Movie("M003", "x", "y", 0)),
                    "Movie: reject duration <= 0");
    okAll &= expect(!movieBus.addMovie(Movie("M003", "x", "y", 999)),
                    "Movie: reject duration too large");

    okAll &= expect(movieBus.addMovie(Movie("M003", "Movie Three", "Comedy", 110)),
                    "Movie: add valid movie");
    okAll &= expect(!movieBus.addMovie(Movie("M003", "Dup", "Comedy", 110)),
                    "Movie: reject duplicate id");

    okAll &= expect(movieBus.updateMovie(Movie("M003", "Movie Three Updated", "Comedy", 111)),
                    "Movie: update existing");
    okAll &= expect(!movieBus.updateMovie(Movie("M999", "Not exist", "None", 100)),
                    "Movie: reject update non-existent");

    // Delete movie when it has showtime must fail (edge case you added)
    okAll &= expect(!movieBus.deleteMovie("M001"),
                    "Movie: reject delete when movie still has showtime");

    okAll &= expect(movieBus.deleteMovie("M003"),
                    "Movie: delete when no showtime");
    okAll &= expect(!movieBus.deleteMovie("M003"),
                    "Movie: reject delete non-existent (after delete)");

    // --------------------
    // Showtime edge cases
    // --------------------
    okAll &= expect(!showtimeBus.addShowtime(Showtime("S002", "M001", "R2", "bad time")),
                    "Showtime: reject invalid datetime format");

    okAll &= expect(!showtimeBus.addShowtime(Showtime("S002", "M404", "R2", "2025-12-23 11:30")),
                    "Showtime: reject non-existent movieId");

    okAll &= expect(showtimeBus.addShowtime(Showtime("S002", "M001", "R2", "2025-12-23 11:30")),
                    "Showtime: add valid showtime");

    okAll &= expect(!showtimeBus.addShowtime(Showtime("S002", "M001", "R3", "2025-12-23 12:30")),
                    "Showtime: reject duplicate showtime id");

    okAll &= expect(!showtimeBus.addShowtime(Showtime("S003", "M001", "R2", "2025-12-23 11:30")),
                    "Showtime: reject room+time clash");

    okAll &= expect(!showtimeBus.deleteShowtime("S404"),
                    "Showtime: reject delete non-existent");

    okAll &= expect(showtimeBus.deleteShowtime("S002"),
                    "Showtime: delete existing");

    // After deleting S002, M001 still has S001, so deleteMovie(M001) should still fail
    okAll &= expect(!movieBus.deleteMovie("M001"),
                    "Movie: still reject delete M001 (S001 still exists)");

    okAll &= expect(showtimeBus.deleteShowtime("S001"),
                    "Showtime: delete remaining showtime of M001");

    okAll &= expect(movieBus.deleteMovie("M001"),
                    "Movie: delete M001 after all showtimes removed");

    cout << "===============================\n";
    cout << (okAll ? "ALL TESTS PASS ✅\n" : "SOME TESTS FAILED ❌\n");
    return okAll ? 0 : 1;
}
