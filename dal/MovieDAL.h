#ifndef MOVIEDAL_H
#define MOVIEDAL_H

#include <vector>
#include "Movie.h"

class MovieDAL {
public:
    // Giả lập đọc từ Database/File
    vector<Movie> getAll() {
        vector<Movie> list;
        // Dữ liệu mẫu (Hardcode)
        list.push_back(Movie("MOV01", "Mai", "Tam ly", 120));
        list.push_back(Movie("MOV02", "Dune: Part Two", "Vien tuong", 166));
        list.push_back(Movie("MOV03", "Kung Fu Panda 4", "Hoat hinh", 94));
        return list;
    }

    bool add(Movie m) { return true; } // Giả lập lưu thành công
};

#endif