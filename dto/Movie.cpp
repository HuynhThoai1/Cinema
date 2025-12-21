#include "Movie.h"

Movie::Movie(std::string id, std::string title, std::string genre, int duration)
    : id(std::move(id)), title(std::move(title)), genre(std::move(genre)), duration(duration) {}

const std::string& Movie::getId() const { return id; }
const std::string& Movie::getTitle() const { return title; }
const std::string& Movie::getGenre() const { return genre; }
int Movie::getDuration() const { return duration; }

void Movie::setId(std::string v) { id = std::move(v); }
void Movie::setTitle(std::string v) { title = std::move(v); }
void Movie::setGenre(std::string v) { genre = std::move(v); }
void Movie::setDuration(int v) { duration = v; }
