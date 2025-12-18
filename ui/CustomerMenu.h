/**
 * @file CustomerMenu.h
 * @brief Menu chức năng dành cho Khách hàng.
 */
#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H

#include <iostream>
#include "../bus/MovieBUS.h"
// #include "../bus/BookingFacade.h"

class CustomerMenu {
private:
    // BookingFacade bookingFacade;
    MovieBUS movieBus;

public:
    CustomerMenu();
    void show();
};

#endif