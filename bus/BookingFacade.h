#ifndef BOOKING_FACADE_H
#define BOOKING_FACADE_H

#include <string>
#include <iostream>

// Include các BUS thành phần
#include "TicketBUS.h"
#include "SeatBUS.h"
#include "ShowtimeBUS.h"
#include "MovieBUS.h"

using std::string;

class BookingFacade {
private:
    // Các đối tượng BUS con (Composition)
    TicketBUS ticketBus;
    SeatBUS seatBus;
    ShowtimeBUS showtimeBus;
    MovieBUS movieBus;

public:
    // Constructor
    BookingFacade();

    // Phương thức xử lý chính (API cho UI gọi)
    bool processBooking(string userId, string showtimeId, string seatId);
};

#endif // BOOKING_FACADE_H