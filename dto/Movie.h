#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;

/**
 * @class Movie
 * @brief Đại diện cho một bộ phim trong hệ thống rạp chiếu phim
 * 
 * Lớp này lưu trữ thông tin về một bộ phim bao gồm ID, tiêu đề,
 * thời lượng, thể loại và thời gian chiếu.
 */
class Movie {
private:
    string _id;         ///< Mã định danh duy nhất cho bộ phim
    string _title;      ///< Tiêu đề của bộ phim
    int    _duration;   ///< Thời lượng phim (phút)
    string _genre;      ///< Thể loại phim
    string _showtime;   ///< Thời gian chiếu phim

public:
    /**
     * @brief Constructor mặc định
     * 
     * Khởi tạo tất cả các trường với giá trị mặc định
     */
    Movie()
        : _id(""), _title(""), _duration(0), _genre(""), _showtime("") {
    }

    /**
     * @brief Constructor có tham số
     * 
     * @param id Mã định danh duy nhất cho bộ phim
     * @param title Tiêu đề của bộ phim
     * @param duration Thời lượng phim (phút)
     * @param genre Thể loại phim
     * @param showtime Thời gian chiếu phim
     */
    Movie(const string& id,
          const string& title,
          int duration,
          const string& genre,
          const string& showtime)
        : _id(id),
          _title(title),
          _duration(duration),
          _genre(genre),
          _showtime(showtime) {
    }

    /**
     * @brief Lấy ID của phim
     * @return const string& Tham chiếu đến ID phim
     */
    const string& getId() const { return _id; }
    
    /**
     * @brief Đặt ID cho phim
     * @param id ID phim mới
     */
    void setId(const string& id) { _id = id; }

    /**
     * @brief Lấy tiêu đề phim
     * @return const string& Tham chiếu đến tiêu đề phim
     */
    const string& getTitle() const { return _title; }
    
    /**
     * @brief Đặt tiêu đề cho phim
     * @param title Tiêu đề phim mới
     */
    void setTitle(const string& title) { _title = title; }

    /**
     * @brief Lấy thời lượng phim
     * @return int Thời lượng phim (phút)
     */
    int getDuration() const { return _duration; }
    
    /**
     * @brief Đặt thời lượng cho phim
     * @param duration Thời lượng phim mới (phút)
     */
    void setDuration(int duration) { _duration = duration; }

    /**
     * @brief Lấy thể loại phim
     * @return const string& Tham chiếu đến thể loại phim
     */
    const string& getGenre() const { return _genre; }
    
    /**
     * @brief Đặt thể loại cho phim
     * @param genre Thể loại phim mới
     */
    void setGenre(const string& genre) { _genre = genre; }

    /**
     * @brief Lấy thời gian chiếu
     * @return const string& Tham chiếu đến thời gian chiếu
     */
    const string& getShowtime() const { return _showtime; }
    
    /**
     * @brief Đặt thời gian chiếu
     * @param showtime Thời gian chiếu mới
     */
    void setShowtime(const string& showtime) { _showtime = showtime; }

    /**
     * @brief Chuyển đổi đối tượng phim thành chuỗi
     * 
     * Chuyển đổi dữ liệu phim thành định dạng chuỗi phân tách bằng dấu gạch đứng
     * 
     * @return string Chuỗi đã được chuyển đổi theo định dạng: id|title|duration|genre|showtime
     */
    string serialize() const {
        std::ostringstream oss;
        oss << _id << "|" << _title << "|" << _duration
            << "|" << _genre << "|" << _showtime;
        return oss.str();
    }

    /**
     * @brief Chuyển đổi chuỗi thành đối tượng Movie
     * 
     * Phân tích chuỗi phân tách bằng dấu gạch đứng và tạo đối tượng Movie
     * 
     * @param line Chuỗi phim đã được chuyển đổi theo định dạng: id|title|duration|genre|showtime
     * @return Movie Đối tượng phim đã được chuyển đổi
     * @throws std::runtime_error Nếu định dạng dòng không hợp lệ, thiếu các trường bắt buộc hoặc thời lượng không hợp lệ
     */
    static Movie deserialize(const string& line) {
        std::istringstream iss(line);
        string id, title, durationStr, genre, showtime;

        if (!std::getline(iss, id, '|')) throw std::runtime_error("Invalid line - missing id");
        if (!std::getline(iss, title, '|')) throw std::runtime_error("Invalid line - missing title");
        if (!std::getline(iss, durationStr, '|')) throw std::runtime_error("Invalid line - missing duration");
        if (!std::getline(iss, genre, '|')) throw std::runtime_error("Invalid line - missing genre");
        std::getline(iss, showtime);

        int duration = 0;
        try { duration = std::stoi(durationStr); }
        catch (...) { throw std::runtime_error("Invalid duration number"); }

        return Movie(id, title, duration, genre, showtime);
    }
};

#endif
