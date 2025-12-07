#ifndef _SHOWTIME_H_
#define _SHOWTIME_H_

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;

/**
 * @class Showtime
 * @brief Đại diện cho một suất chiếu phim trong hệ thống rạp chiếu phim
 * 
 * Lớp này lưu trữ thông tin về một suất chiếu cụ thể bao gồm
 * ID suất chiếu, ID phim, thời gian bắt đầu và số phòng chiếu.
 */
class Showtime {
private:
    string _id;         ///< Mã định danh duy nhất cho suất chiếu
    string _movieId;    ///< ID của bộ phim được chiếu
    string _startTime;  ///< Thời gian bắt đầu của suất chiếu
    string _room;       ///< Phòng chiếu nơi phim được chiếu

public:
    /**
     * @brief Constructor mặc định
     * 
     * Khởi tạo tất cả các trường với chuỗi rỗng
     */
    Showtime()
        : _id(""), _movieId(""), _startTime(""), _room("") {
    }

    /**
     * @brief Constructor có tham số
     * 
     * @param id Mã định danh duy nhất cho suất chiếu
     * @param movieId ID của bộ phim được chiếu
     * @param startTime Thời gian bắt đầu của suất chiếu
     * @param room Phòng chiếu nơi phim được chiếu
     */
    Showtime(const string& id,
             const string& movieId,
             const string& startTime,
             const string& room)
        : _id(id),
          _movieId(movieId),
          _startTime(startTime),
          _room(room) {
    }

    /**
     * @brief Lấy ID của suất chiếu
     * @return const string& Tham chiếu đến ID suất chiếu
     */
    const string& getId() const { return _id; }
    
    /**
     * @brief Đặt ID cho suất chiếu
     * @param id ID suất chiếu mới
     */
    void setId(const string& id) { _id = id; }

    /**
     * @brief Lấy ID của phim
     * @return const string& Tham chiếu đến ID phim
     */
    const string& getMovieId() const { return _movieId; }
    
    /**
     * @brief Đặt ID cho phim
     * @param movieId ID phim mới
     */
    void setMovieId(const string& movieId) { _movieId = movieId; }

    /**
     * @brief Lấy thời gian bắt đầu
     * @return const string& Tham chiếu đến thời gian bắt đầu
     */
    const string& getStartTime() const { return _startTime; }
    
    /**
     * @brief Đặt thời gian bắt đầu
     * @param startTime Thời gian bắt đầu mới
     */
    void setStartTime(const string& startTime) { _startTime = startTime; }

    /**
     * @brief Lấy số phòng chiếu
     * @return const string& Tham chiếu đến số phòng
     */
    const string& getRoom() const { return _room; }
    
    /**
     * @brief Đặt số phòng chiếu
     * @param room Số phòng mới
     */
    void setRoom(const string& room) { _room = room; }

    /**
     * @brief Chuyển đổi đối tượng suất chiếu thành chuỗi
     * 
     * Chuyển đổi dữ liệu suất chiếu thành định dạng chuỗi phân tách bằng dấu gạch đứng
     * 
     * @return string Chuỗi đã được chuyển đổi theo định dạng: id|movieId|startTime|room
     */
    string serialize() const {
        std::ostringstream oss;
        oss << _id << "|" << _movieId << "|" << _startTime << "|" << _room;
        return oss.str();
    }

    /**
     * @brief Chuyển đổi chuỗi thành đối tượng Showtime
     * 
     * Phân tích chuỗi phân tách bằng dấu gạch đứng và tạo đối tượng Showtime
     * 
     * @param line Chuỗi suất chiếu đã được chuyển đổi theo định dạng: id|movieId|startTime|room
     * @return Showtime Đối tượng suất chiếu đã được chuyển đổi
     * @throws std::runtime_error Nếu định dạng dòng không hợp lệ hoặc thiếu các trường bắt buộc
     */
    static Showtime deserialize(const string& line) {
        std::istringstream iss(line);
        string id, movieId, startTime, room;

        if (!std::getline(iss, id, '|')) throw std::runtime_error("Invalid line - missing id");
        if (!std::getline(iss, movieId, '|')) throw std::runtime_error("Invalid line - missing movieId");
        if (!std::getline(iss, startTime, '|')) throw std::runtime_error("Invalid line - missing startTime");
        std::getline(iss, room);

        return Showtime(id, movieId, startTime, room);
    }
};

#endif
