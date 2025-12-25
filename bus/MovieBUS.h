#ifndef BUS_MOVIEBUS_H
#define BUS_MOVIEBUS_H

#include <string>
#include <vector>
#include <optional>

using std::string;
using std::vector;
using std::optional;

#include "../dto/Movie.h"
#include "../dal/MovieDAL.h"
#include "../dal/ShowtimeDAL.h"

/**
 * @class MovieBUS
 * @brief Business Layer quản lý phim.
 */
class MovieBUS {
private:
    MovieDAL movieDal;
    ShowtimeDAL showtimeDal;
    vector<Movie> _movies;

public:
    explicit MovieBUS(
        MovieDAL movieDal = MovieDAL(),
        ShowtimeDAL showtimeDal = ShowtimeDAL()
    );

    std::vector<Movie> getAll();

    // Edge cases:
    // - chặn id rỗng / field rỗng / duration invalid
    // - chặn trùng id
    bool addMovie(const Movie& movie);

    // Edge cases:
    // - không tồn tại -> false
    // - validate dữ liệu trước khi lưu
    bool updateMovie(const Movie& movie);

    // Edge cases:
    // - không tồn tại -> false
    // - nếu movie còn showtime -> false (không cho xóa)
    bool deleteMovie(const std::string& id);
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
     * @brief Tìm phim theo ID
     * 
     * @param id ID của phim cần tìm
     * @return Movie* Con trỏ đến đối tượng phim nếu tìm thấy
     * @return nullptr Nếu không tìm thấy phim với ID tương ứng
     */
    optional<Movie> findById(const string& id);
    
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

#endif // BUS_MOVIEBUS_H
