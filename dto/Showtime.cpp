#include "Showtime.h"

Showtime::Showtime(std::string id, std::string movieId, std::string room, std::string startTime)
    : id(std::move(id)), movieId(std::move(movieId)), room(std::move(room)), startTime(std::move(startTime)) {}

const std::string& Showtime::getId() const { return id; }
const std::string& Showtime::getMovieId() const { return movieId; }
const std::string& Showtime::getRoom() const { return room; }
const std::string& Showtime::getStartTime() const { return startTime; }

void Showtime::setId(std::string v) { id = std::move(v); }
void Showtime::setMovieId(std::string v) { movieId = std::move(v); }
void Showtime::setRoom(std::string v) { room = std::move(v); }
void Showtime::setStartTime(std::string v) { startTime = std::move(v); }
