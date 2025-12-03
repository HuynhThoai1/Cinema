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
    UserDAL userDal;        // Đối tượng để gọi xuống tầng dữ liệu
    vector<User*> users;    // Danh sách user đang hoạt động (Cache)
    User* currentUser;      // Lưu người đang đăng nhập hiện tại
public:
    UserBUS();
    ~UserBUS();

    void loadData();
    User* login(string username, string password);
    bool registerUser(string username, string password);
    User* getCurrentUser();
    void logout();
    bool changePassword(string id, string oldPw, string newPw);
};

#endif