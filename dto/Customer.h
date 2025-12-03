#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include "User.h"
#include <iostream>

using std::cout;

class Customer: public User {
public:
    // 1. Construct
    Customer();
    Customer(string id, string username, string password);
    
    // 2. Destructor
    ~Customer();

    // 3. Method
    void viewMovies();
    void viewShowtimes();
    void bookTicket();
};

#endif