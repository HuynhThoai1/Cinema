#ifndef DTO_SHOWTIME_H
#define DTO_SHOWTIME_H

#include <string>

/**
 * @class Showtime
 * @brief DTO đại diện cho một suất chiếu.
 */
class Showtime {
private:
    std::string id;
    std::string movieId;
    std::string room;
    std::string startTime;

public:
    Showtime() = default;
    Showtime(std::string id, std::string movieId, std::string room, std::string startTime);

    const std::string& getId() const;
    const std::string& getMovieId() const;
    const std::string& getRoom() const;
    const std::string& getStartTime() const;

    void setId(std::string v);
    void setMovieId(std::string v);
    void setRoom(std::string v);
    void setStartTime(std::string v);
};

#endif // DTO_SHOWTIME_H
