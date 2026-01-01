#include "User.h"

// --- 1. Construct ---
User::User() {
    this->_id = "";
    this->_username = "";
    this->_password = "";
    this->_role = "guest";
}

User::User(string id, string username, string password, string role) {
    this->_id = id;
    this->_username = username;
    this->_password = password;
    this->_role = role;
}

// --- 2. Destructor ---
User::~User() {
    // Do nothing
}

// --- 3. Getters ---
string User::getId() const {
    return this->_id;
}

string User::getUsername() const {
    return this->_username;
}

string User::getPassword() const {
    return this->_password;
}

string User::getRole() const {
    return this->_role;
}

// --- 4. Setters ---
void User::setId(string id) {
    this->_id = id;
}

void User::setUsername(string username) {
    this->_username = username;
}

void User::setPassword(string password) {
    this->_password = password;
}

void User::setRole(string role) {
    this->_role = role;
}

// --- 5. Method ---
bool User::checkPassword(string inputPw) const {
    return this->_password == inputPw;
}