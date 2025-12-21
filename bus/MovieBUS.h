#ifndef _MOVIEBUS_H_
#define _MOVIEBUS_H_

#include <string>
#include <vector>
#include "../dto/Movie.h"
#include "../dal/MovieDAL.h"

using std::string;
using std::vector;

/**
 * @class MovieBUS
 * @brief Lớp nghiệp vụ quản lý phim (Business Logic Layer)
 * 
 * Lớp này cung cấp các chức năng nghiệp vụ để quản lý danh sách phim
 * bao gồm thêm, xóa, sửa, tìm kiếm và lưu trữ dữ liệu.
 */
class MovieBUS {
private:
    vector<Movie> _movies;  ///< Danh sách các phim được quản lý

public:
    /**
     * @brief Constructor mặc định
     * 
     * Khởi tạo đối tượng MovieBUS với danh sách phim rỗng
     */
    MovieBUS() {}

    /**
     * @brief Lấy toàn bộ danh sách phim
     * 
     * @return const vector<Movie>& Tham chiếu đến danh sách phim
     */
    const vector<Movie>& getAll() const { return _movies; }

    /**
     * @brief Tải danh sách phim từ file
     * 
     * @param filename Đường dẫn đến file chứa dữ liệu phim
     */
    void load(const string& filename);
    
    /**
     * @brief Lưu danh sách phim vào file
     * 
     * @param filename Đường dẫn đến file đích
     */
    void save(const string& filename) const;

    /**
     * @brief Thêm một phim mới vào danh sách
     * 
     * Kiểm tra xem ID phim đã tồn tại chưa trước khi thêm.
     * 
     * @param movie Đối tượng phim cần thêm
     * @return true Nếu thêm phim thành công
     * @return false Nếu ID phim đã tồn tại trong danh sách
     */
    bool addMovie(const Movie& movie);
    
    /**
     * @brief Xóa một phim khỏi danh sách theo ID
     * 
     * @param id ID của phim cần xóa
     * @return true Nếu tìm thấy và xóa phim thành công
     * @return false Nếu không tìm thấy phim với ID tương ứng
     */
    bool deleteMovie(const string& id);
    
    /**
     * @brief Cập nhật thông tin phim
     * 
     * Tìm phim theo ID và cập nhật thông tin mới.
     * 
     * @param movie Đối tượng phim với thông tin mới (ID phải trùng với phim cần cập nhật)
     * @return true Nếu tìm thấy và cập nhật phim thành công
     * @return false Nếu không tìm thấy phim với ID tương ứng
     */
    bool updateMovie(const Movie& movie);

    /**
     * @brief Tìm phim theo ID
     * 
     * @param id ID của phim cần tìm
     * @return Movie* Con trỏ đến đối tượng phim nếu tìm thấy
     * @return nullptr Nếu không tìm thấy phim với ID tương ứng
     */
    Movie* findById(const string& id);
    
    /**
     * @brief Tìm các phim theo một phần tiêu đề
     * 
     * Tìm kiếm tất cả các phim có tiêu đề chứa chuỗi tìm kiếm.
     * 
     * @param namePart Chuỗi con cần tìm trong tiêu đề phim
     * @return vector<Movie> Danh sách các phim có tiêu đề chứa chuỗi tìm kiếm
     */
    vector<Movie> findByTitle(const string& namePart) const;
};

#endif
