#include "FoodDAL.h"

/**
 * @brief Đọc danh sách thực phẩm từ file văn bản.
 * * Quy trình xử lý:
 * 1. Xóa dữ liệu cũ trong vector `listFood`.
 * 2. Mở file theo đường dẫn `FILE_NAME`.
 * 3. Đọc từng dòng, sử dụng `stringstream` để tách các trường dữ liệu bằng dấu phẩy (`,`).
 * 4. Chuyển đổi giá trị tiền (string sang int) và thêm vào danh sách.
 */
void FoodDAL::loadFoods() {
    listFood.clear();
    ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) return;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> data;
        
        // Tách chuỗi theo ký tự phân cách là dấu phẩy
        while (getline(ss, segment, ',')) {
            data.push_back(segment);
        }

        if (data.size() == 3) {
            try {
                // data[0]: ID, data[1]: Name, data[2]: Price
                listFood.push_back(Food(data[0], data[1], stoi(data[2])));
            } catch (...) {
                // Bỏ qua các dòng có định dạng giá không hợp lệ
            }
        }
    }
    inFile.close();
}

/**
 * @brief Ghi đè toàn bộ danh sách thực phẩm từ bộ nhớ vào file.
 * * Dữ liệu được lưu dưới dạng CSV: `ID,Tên,Giá`.
 */
void FoodDAL::saveFoods() {
    ofstream outFile(FILE_NAME);
    if (outFile.is_open()) {
        for (const auto& f : listFood) {
            outFile << f.getId() << "," << f.getName() << "," << f.getPrice() << endl;
        }
        outFile.close();
    }
}

/**
 * @brief Thêm thực phẩm mới và cập nhật ngay vào file.
 * @param food Đối tượng thực phẩm cần lưu trữ.
 */
void FoodDAL::addFood(const Food& food) {
    listFood.push_back(food);
    saveFoods(); // Đồng bộ hóa dữ liệu xuống file ngay khi thêm mới
}

/**
 * @brief Trả về danh sách thực phẩm hiện tại trong bộ nhớ.
 * @return vector<Food> Bản sao của danh sách thực phẩm.
 */
vector<Food> FoodDAL::getList() const { 
    return listFood; 
}

/**
 * @brief Tìm kiếm thực phẩm trong bộ nhớ theo mã ID.
 * @param id Mã định danh cần tìm.
 * @return Food* Địa chỉ của đối tượng trong vector nếu tìm thấy, ngược lại là nullptr.
 */
Food* FoodDAL::getFoodById(string id) {
    for (auto &f : listFood) {
        if (f.getId() == id) return &f;
    }
    return nullptr;
}