#include "RevenueDAL.h"
using namespace std;
/**
 * @brief Nạp dữ liệu doanh thu từ file văn bản vào bộ nhớ.
 * * **Quy trình thực hiện:**
 * 1. Làm trống danh sách hiện tại để nạp mới.
 * 2. Đọc file theo từng dòng, phân tách dữ liệu bằng dấu phẩy (CSV).
 * 3. Chuyển đổi các cột số tiền (vé và đồ ăn) từ chuỗi sang số nguyên.
 * 4. Chỉ thêm bản ghi vào danh sách nếu đủ 5 trường dữ liệu hợp lệ.
 */
void RevenueDAL::loadRevenues() {
    listRevenue.clear();
    ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) return;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> data;
        while (getline(ss, segment, ',')) data.push_back(segment);

        // Định dạng kỳ vọng: ID, Date, MovieID, Ticket, Food (5 trường)
        if (data.size() == 5) {
            try {
                Revenue r(data[0], data[1], data[2], stoi(data[3]), stoi(data[4]));
                listRevenue.push_back(r);
            } catch (...) {
                // Xử lý ngoại lệ nếu stoi thất bại do dữ liệu file lỗi
            }
        }
    }
    inFile.close();
}

/**
 * @brief Ghi lại toàn bộ danh sách doanh thu hiện tại vào file.
 * * Sử dụng chế độ ghi đè (ofstream mặc định) để cập nhật trạng thái mới nhất 
 * của danh sách vào file `data/Revenue.txt`.
 */
void RevenueDAL::saveRevenues() {
    ofstream outFile(FILE_NAME);
    if (outFile.is_open()) {
        for (const auto& r : listRevenue) {
            outFile << r.getId() << "," << r.getDate() << "," << r.getMovieId() << ","
                    << r.getTicketRevenue() << "," << r.getFoodRevenue() << endl;
        }
        outFile.close();
    }
}

/**
 * @brief Lưu trữ một bản ghi doanh thu mới.
 * * Sau khi đẩy bản ghi vào vector trong bộ nhớ, hàm sẽ gọi `saveRevenues()` 
 * để đảm bảo dữ liệu được cập nhật tức thì xuống ổ đĩa.
 * @param rev Đối tượng Revenue chứa thông tin doanh thu cần thêm.
 */
void RevenueDAL::addRevenue(const Revenue& rev) {
    listRevenue.push_back(rev);
    saveRevenues();
}

/**
 * @brief Cung cấp danh sách doanh thu đang quản lý.
 * @return vector<Revenue> Danh sách các bản ghi doanh thu.
 */
vector<Revenue> RevenueDAL::getList() const { 
    return listRevenue; 
}