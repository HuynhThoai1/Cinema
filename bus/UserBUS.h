/**
 * @file UserBUS.h
 * @brief Tầng nghiệp vụ (Business Logic Layer) cho người dùng chung.
 */

#ifndef _USER_BUS_H_
#define _USER_BUS_H_

#include <vector>
#include <string>
#include "../dal/UserDAL.h" 
#include "../dto/User.h"
#include "../dto/Customer.h"

using std::to_string;

class UserBUS {
private: 
    UserDAL userDal;        ///< Đối tượng DAL để thao tác file
    vector<User*> users;    ///< Cache danh sách user trong RAM
    User* currentUser;      ///< Lưu pointer đến người dùng đang đăng nhập
public:
    UserBUS();
    
    /**
     * @brief Hủy đối tượng BUS và giải phóng bộ nhớ của danh sách users.
     */
    ~UserBUS();

    /**
     * @brief Tải dữ liệu từ DAL lên RAM.
     * @note Cần xóa cache cũ trước khi load để tránh leak memory.
     */
    void loadData();

    /**
     * @brief Xử lý đăng nhập.
     * @param username Tên đăng nhập.
     * @param password Mật khẩu.
     * @return User* Con trỏ đến user nếu thành công, nullptr nếu thất bại hoặc bị khóa.
     */
    User* login(string username, string password);

    /**
     * @brief Đăng ký tài khoản mới (Mặc định là Customer).
     * @param username Tên đăng nhập muốn tạo.
     * @param password Mật khẩu.
     * @return true Nếu tạo thành công.
     * @return false Nếu username đã tồn tại.
     */
    bool registerUser(string username, string password);

    /**
     * @brief Lấy thông tin người dùng hiện tại (Session).
     * @return User* Người dùng đang login.
     */
    User* getCurrentUser();

    /**
     * @brief Đăng xuất, xóa session hiện tại.
     */
    void logout();

    /**
     * @brief Đổi mật khẩu người dùng.
     * @param id ID người dùng.
     * @param oldPw Mật khẩu cũ.
     * @param newPw Mật khẩu mới.
     * @return true nếu đổi thành công, false nếu sai mật khẩu cũ.
     */
    bool changePassword(string id, string oldPw, string newPw);
};

#endif