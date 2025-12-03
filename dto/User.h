#ifndef _USER_H_
#define _USER_H_
#include <string>

using std::string;

class User {
private:
    string _id;
    string _username;
    string _password;
    string _role; // Ví dụ: "Admin" hoặc "Customer"
public:
    // 1. Construct
    User();
    User(string id, string username, string password, string role);

    // 2. Destructor
    //  Virtual để hỗ trợ đa hình cho Admin/Customer
    virtual ~User();

    // 3. Getters
    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getRole() const;

    // 4. Setters
    void setId(string id);
    void setUsername(string username);
    void setPassword(string password);
    void setRole(string role);

    //5. Method (Nghiệp vụ cơ bản của Class)
    bool checkPassword(string inputPw) const;
};
#endif