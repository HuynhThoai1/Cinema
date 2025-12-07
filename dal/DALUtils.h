/**
 * @file DALUtils.h
 * @brief Tệp tiêu đề chứa các hàm tiện ích dùng chung (Helper/Utility).
 * @details Cung cấp các công cụ xử lý chuỗi (String Manipulation), chuyển đổi dữ liệu và kiểm tra file
 * giúp các lớp DAL khác (TicketDAL, SeatDAL) hoạt động gọn gàng hơn.
 */

#ifndef _DALUTILS_H_
#define _DALUTILS_H_

#include <string>
#include <vector>

using std::vector, std::string;

/**
 * @class DALUtils
 * @brief Lớp tiện ích chứa các phương thức tĩnh (Static methods).
 * @details Không cần khởi tạo đối tượng DALUtils, có thể gọi trực tiếp qua tên lớp (VD: DALUtils::Trim(...)).
 */
class DALUtils {
public:
    /**
     * @brief Xóa khoảng trắng thừa ở 2 đầu chuỗi.
     * @details Loại bỏ dấu cách (space), tab (\t), xuống dòng (\n) ở đầu và cuối chuỗi. 
     * Không tác động đến khoảng trắng ở giữa chuỗi.
     * @param str Chuỗi gốc cần xử lý.
     * @return string Chuỗi kết quả sau khi đã cắt gọn.
     */
    static string Trim(const string& str);

    /**
     * @brief Tách chuỗi thành danh sách các chuỗi con dựa trên ký tự phân cách.
     * @details Thường dùng để tách dòng dữ liệu file (VD: "R01|A|1") thành các phần nhỏ.
     * @param str Chuỗi gốc cần tách.
     * @param delimiter Chuỗi dùng làm dấu phân cách (VD: "|" hoặc ", ").
     * @return vector<string> Danh sách các chuỗi con (Tokens).
     */
    static vector<string> Split(const string& str, const string& delimiter);

    /**
     * @brief Gộp danh sách chuỗi thành một chuỗi duy nhất.
     * @details Ngược lại với hàm Split. Nối các phần tử lại và chèn delimiter vào giữa.
     * @param list Danh sách các chuỗi con cần nối.
     * @param delimiter Dấu phân cách muốn chèn vào giữa các phần tử.
     * @return string Chuỗi kết quả sau khi gộp.
     */
    static string Join(const vector<string>& list, const string& delimiter);

    /**
     * @brief Chuyển đổi chuỗi sang số nguyên (Integer) an toàn.
     * @details Xử lý các trường hợp chuỗi chứa ký tự lạ hoặc khoảng trắng để tránh crash chương trình.
     * @param str Chuỗi chứa số (VD: "123", "  45 ").
     * @return int Giá trị số nguyên. Trả về 0 (hoặc giá trị mặc định) nếu chuỗi lỗi.
     */
    static int parseInt(const string& str);

    /**
     * @brief Kiểm tra sự tồn tại và khả năng truy cập của file.
     * @details Dùng để đảm bảo file có thể mở được trước khi thực hiện Đọc/Ghi, tránh lỗi runtime.
     * @param filename Đường dẫn đến file cần kiểm tra.
     * @return true Nếu file tồn tại và có thể mở được.
     * @return false Nếu file không tồn tại hoặc bị khóa quyền truy cập.
     */
    static bool fileManagementTest(const string& filename);
};

#endif