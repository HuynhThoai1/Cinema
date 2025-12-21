#ifndef FOOD_DAL_H
#define FOOD_DAL_H

#include <vector>
#include <fstream>
#include <sstream>
#include "../dto/Food.h"

/**
 * @class FoodDAL
 * @brief Lớp truy cập dữ liệu (Data Access Layer) cho thực phẩm.
 * * Lớp này quản lý việc đọc và ghi danh sách thực phẩm vào file vật lý (Food.txt),
 * đồng thời duy trì một danh sách tạm thời trong bộ nhớ để tối ưu hóa tốc độ truy xuất.
 */
class FoodDAL {
private:
    /** @brief Danh sách các đối tượng Food được lưu trữ trong bộ nhớ tạm (cache). */
    vector<Food> listFood;
    
    /** @brief Đường dẫn hằng số đến file lưu trữ dữ liệu thực phẩm. */
    const string FILE_NAME = "data/Food.txt"; 

public:
    /**
     * @brief Nạp dữ liệu từ file Food.txt vào vector listFood.
     * * Phương thức này thực hiện mở file, đọc từng dòng, phân tách dữ liệu 
     * và chuyển đổi thành các đối tượng Food.
     */
    void loadFoods();

    /**
     * @brief Lưu toàn bộ danh sách thực phẩm hiện có trong bộ nhớ vào file.
     * * Thường được gọi sau khi danh sách trong bộ nhớ có sự thay đổi (thêm, sửa, xóa).
     */
    void saveFoods();

    /**
     * @brief Thêm một đối tượng Food mới vào danh sách.
     * @param food Đối tượng thực phẩm cần thêm (truyền tham chiếu hằng để tối ưu).
     */
    void addFood(const Food& food);

    /**
     * @brief Lấy bản sao của danh sách thực phẩm hiện có.
     * @return vector<Food> Danh sách thực phẩm đang được quản lý.
     */
    vector<Food> getList() const;

    /**
     * @brief Tìm kiếm một món ăn cụ thể theo mã định danh (ID).
     * @param id Mã ID của thực phẩm cần tìm.
     * @return Food* Con trỏ trỏ đến đối tượng Food trong danh sách nếu tìm thấy, 
     * ngược lại trả về nullptr.
     */
    Food* getFoodById(string id);
};

#endif