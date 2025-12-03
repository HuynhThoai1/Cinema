#ifndef _ADMIN_H_
#define _ADMIN_H_
#include "User.h"
#include <iostream>

using std::cout;

class Admin: public User {
public:
    // 1. Construct
    Admin();
    Admin(string id, string username, string password);
    
    // 2. Destructor
    ~Admin();

    // 3. Method
    void manageMovies();
    void manageShowtimes();
    void viewRevenue();
};

#endif