#ifndef REVENUE_DAL_H
#define REVENUE_DAL_H

#include <vector>
#include <fstream>
#include <sstream>
#include "../dto/Revenue.h"

/**
 * @class RevenueDAL
 * @brief Lớp truy cập dữ liệu (Data Access Layer) cho doanh thu.
 * * Lớp này chịu trách nhiệm thực hiện các thao tác Đọc/Ghi dữ liệu doanh thu
 * từ tệp tin văn bản (Revenue.txt) và duy trì danh sách bản ghi trong bộ nhớ.
 */
class RevenueDAL {
private:
    /** @brief Danh sách lưu trữ tạm thời các bản ghi doanh thu trong bộ nhớ (RAM). */
    vector<Revenue> listRevenue;

    /** @brief Đường dẫn cố định tới tệp tin lưu trữ dữ liệu doanh thu. */
    const string FILE_NAME = "data/Revenue.txt";

public:
    /**
     * @brief Đọc dữ liệu từ tệp tin và nạp vào danh sách `listRevenue`.
     * * Phương thức này sẽ mở tệp tin, phân tích cú pháp từng dòng và chuyển đổi
     * chúng thành các đối tượng Revenue.
     */
    void loadRevenues();

    /**
     * @brief Ghi toàn bộ danh sách doanh thu hiện tại vào tệp tin.
     * * Quá trình này sẽ ghi đè nội dung cũ của tệp tin để đảm bảo tính đồng bộ
     * với dữ liệu mới nhất trong bộ nhớ.
     */
    void saveRevenues();

    /**
     * @brief Thêm một bản ghi doanh thu mới vào danh sách bộ nhớ.
     * @param rev Đối tượng Revenue chứa thông tin doanh thu cần lưu.
     */
    void addRevenue(const Revenue& rev);

    /**
     * @brief Trả về toàn bộ danh sách doanh thu hiện có.
     * @return vector<Revenue> Danh sách các đối tượng doanh thu.
     */
    vector<Revenue> getList() const;
};

#endif