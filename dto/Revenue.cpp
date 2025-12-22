#include "Revenue.h"

Revenue::Revenue() : id(""), date(""), movieId(""), ticketRevenue(0), foodRevenue(0) {}

Revenue::Revenue(std::string id, std::string date, std::string movieId, int tRev, int fRev) 
    : id(id), date(date), movieId(movieId), ticketRevenue(tRev), foodRevenue(fRev) {}

std::string Revenue::getId() const { return this->id; }
std::string Revenue::getDate() const { return this->date; }
std::string Revenue::getMovieId() const { return this->movieId; }
int Revenue::getTicketRevenue() const { return this->ticketRevenue; }
int Revenue::getFoodRevenue() const { return this->foodRevenue; }

int Revenue::getTotalRevenue() const {
    return this->ticketRevenue + this->foodRevenue;
}

void Revenue::display() const {
    std::cout << std::left << std::setw(10) << id 
              << std::setw(15) << date 
              << std::setw(10) << movieId 
              << " Vé: " << std::setw(10) << ticketRevenue
              << " Đồ ăn: " << std::setw(10) << foodRevenue
              << " => Tổng: " << getTotalRevenue() << std::endl;
}