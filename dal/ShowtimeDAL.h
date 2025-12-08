#ifndef _SHOWTIMEDAL_H_
#define _SHOWTIMEDAL_H_

#include <string>
#include <vector>
#include "../dto/Showtime.h"

using std::string;
using std::vector;

/**
 * @class ShowtimeDAL
 * @brief Lớp truy cập dữ liệu cho suất chiếu phim (Data Access Layer)
 * 
 * Lớp này cung cấp các phương thức để đọc và ghi dữ liệu suất chiếu
 * từ/vào file văn bản.
 */
class ShowtimeDAL {
public:
    /**
     * @brief Tải danh sách suất chiếu từ file
     * 
     * Đọc file văn bản và chuyển đổi từng dòng thành đối tượng Showtime.
     * Các dòng không hợp lệ sẽ bị bỏ qua và ghi log lỗi.
     * 
     * @param filename Đường dẫn đến file chứa dữ liệu suất chiếu
     * @return vector<Showtime> Danh sách các đối tượng suất chiếu đã tải
     * @note Trả về vector rỗng nếu file không tồn tại hoặc không mở được
     */
    static vector<Showtime> loadFromFile(const string& filename);
    
    /**
     * @brief Lưu danh sách suất chiếu vào file
     * 
     * Ghi đè toàn bộ nội dung file bằng danh sách suất chiếu mới.
     * Mỗi suất chiếu được ghi trên một dòng riêng biệt.
     * 
     * @param list Danh sách các đối tượng suất chiếu cần lưu
     * @param filename Đường dẫn đến file đích
     * @note Nếu file không mở được, phương thức sẽ không thực hiện gì
     */
    static void saveToFile(const vector<Showtime>& list, const string& filename);
};

#endif
