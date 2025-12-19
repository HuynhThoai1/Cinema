#ifndef DTO_MOVIE_H
#define DTO_MOVIE_H

#include <string>

/**
 * @class Movie
 * @brief DTO đại diện cho một bộ phim.
 */
class Movie {
protected:
    std::string id;
    std::string title;
    std::string genre;
    int duration{}; // minutes

public:
    Movie() = default;
    Movie(std::string id, std::string title, std::string genre, int duration);

    // Getters (hỗ trợ BUS/DAL/UI)
    const std::string& getId() const;
    const std::string& getTitle() const;
    const std::string& getGenre() const;
    int getDuration() const;

    // Setters
    void setId(std::string v);
    void setTitle(std::string v);
    void setGenre(std::string v);
    void setDuration(int v);
};

#endif // DTO_MOVIE_H
