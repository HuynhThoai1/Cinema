#ifndef SHOWTIMEDAL_H
#define SHOWTIMEDAL_H

#include <vector>
#include "Showtime.h"

class ShowtimeDAL {
public:
    vector<Showtime> getAll() {
        vector<Showtime> list;
        // Dữ liệu mẫu khớp với MovieDAL ở trên
        // ST01 chiếu phim MOV01 (Mai)
        list.push_back(Showtime("ST01", "MOV01", "Room A", "18:00", "05/12/2025"));
        // ST02 chiếu phim MOV02 (Dune 2)
        list.push_back(Showtime("ST02", "MOV02", "Room B", "20:30", "05/12/2025"));
        return list;
    }

    bool add(Showtime s) { return true; }
};

#endif