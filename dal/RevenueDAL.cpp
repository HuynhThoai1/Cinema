#include "RevenueDAL.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using namespace std;

void RevenueDAL::loadRevenues() {
    listRevenue.clear();
    listRevenue.push_back(Revenue("R01", "05/12/2025", "M01", 2000000, 500000));
    listRevenue.push_back(Revenue("R02", "05/12/2025", "M02", 1500000, 300000));
}

void RevenueDAL::addRevenue(const Revenue& rev) {
    listRevenue.push_back(rev);
}

vector<Revenue> RevenueDAL::getList() const {
    return listRevenue;
}

// Implementation Revenue DTO
Revenue::Revenue() {}
Revenue::Revenue(string id, string date, string movieId, int tRev, int fRev) 
    : id(id), date(date), movieId(movieId), ticketRevenue(tRev), foodRevenue(fRev) {}
string Revenue::getDate() const { return date; }
string Revenue::getMovieId() const { return movieId; }
int Revenue::getTotalRevenue() const { return ticketRevenue + foodRevenue; }
void Revenue::display() const {
    cout << left << setw(10) << id << setw(12) << date << setw(10) << movieId 
         << " Total: " << getTotalRevenue() << endl;
}