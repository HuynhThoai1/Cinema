#ifndef _MOVIEDAL_H_
#define _MOVIEDAL_H_

#include <string>
#include <vector>
#include "Movie.h"

using std::string;
using std::vector;

/**
 * @class MovieDAL
 * @brief Lớp truy cập dữ liệu cho phim (Data Access Layer)
 * 
 * Lớp này cung cấp các phương thức để đọc và ghi dữ liệu phim
 * từ/vào file văn bản.
 */
class MovieDAL {
public:
    /**
     * @brief Tải danh sách phim từ file
     * 
     * Đọc file văn bản và chuyển đổi từng dòng thành đối tượng Movie.
     * Các dòng không hợp lệ sẽ bị bỏ qua và ghi log lỗi.
     * 
     * @param filename Đường dẫn đến file chứa dữ liệu phim
     * @return vector<Movie> Danh sách các đối tượng phim đã tải
     * @note Trả về vector rỗng nếu file không tồn tại hoặc không mở được
     */
    static vector<Movie> loadFromFile(const string& filename);
    
    /**
     * @brief Lưu danh sách phim vào file
     * 
     * Ghi đè toàn bộ nội dung file bằng danh sách phim mới.
     * Mỗi phim được ghi trên một dòng riêng biệt.
     * 
     * @param list Danh sách các đối tượng phim cần lưu
     * @param filename Đường dẫn đến file đích
     * @note Nếu file không mở được, phương thức sẽ không thực hiện gì
     */
    static void saveToFile(const vector<Movie>& list, const string& filename);
};

#endif
