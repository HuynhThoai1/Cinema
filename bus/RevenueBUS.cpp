#include "RevenueBUS.h"


void RevenueBUS::addTicketRevenue(string date, int amount) {
    
    
    bool found = false;
    vector<Revenue> list = revenueDal.getList(); 
    
    for (auto& r : list) {
        if (r.getDate() == date) {
            found = true;
            break;
        }
    }

    if (!found) {
        Revenue newRev("", date, "", amount, 0); 
        revenueDal.addRevenue(newRev);
    }
}

void RevenueBUS::addFoodRevenue(string date, int amount) {
    bool found = false;
    vector<Revenue> list = revenueDal.getList();

    for (auto& r : list) {
        if (r.getDate() == date) {
            found = true;
            break;
        }
    }

    if (!found) {
        Revenue newRev("", date, "", 0, amount);
        revenueDal.addRevenue(newRev);
    }
}

Revenue RevenueBUS::getRevenueByDate(string date) {
    for (const auto& r : revenueDal.getList()) {
        if (r.getDate() == date) {
            return r; 
        }
    }
    
    
    return Revenue(); 
}

vector<Revenue> RevenueBUS::getRevenueByMovie(string movieId) {
    vector<Revenue> result;
    
    for (const auto& r : revenueDal.getList()) {
        if (r.getMovieId() == movieId) {
            result.push_back(r);
        }
    }
    
    return result; 
}