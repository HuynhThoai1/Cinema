// NormalTicket.h
#ifndef NORMAL_TICKET_H
#define NORMAL_TICKET_H

#include "Ticket.h"

// 1. Vé Người Lớn
class NormalTicket : public Ticket {
public:
    // Kế thừa constructor của cha, không làm gì thêm vì giá giữ nguyên
    using Ticket::Ticket; 
};

#endif // ADULT_TICKET_H