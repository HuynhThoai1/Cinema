#include "DALUtils.h"
#include <iostream>
#include <sstream>
#include <fstream>

using std::stringstream, std::cout;

string DALUtils::Trim(const string& str) {
    stringstream ss(str);
    string letter, newstr;

    while(ss >> letter) {
        if(!newstr.empty()) {
            newstr += " "; 
        }
        newstr += letter;
    }
    
    return newstr;
}

string DALUtils::Join(const vector<string>& list, const string& delimiter) {
    string res;

    for(const string& item : list) {
        if (!res.empty()) {
            res += delimiter;
        }

        res += item;
    }

    return res;
}

vector<string> DALUtils::Split(const string& str, const string& delimiter) {  
    vector<string> list;
    size_t delimiterPos = 0;
    string token;
    size_t head = 0;

    while((delimiterPos = str.find(delimiter, head)) != string::npos) {
        token = str.substr(head, delimiterPos-head);
        list.push_back(token);
        head = delimiterPos + delimiter.length();
    }

    list.push_back(str.substr(head));

    return list;
}

int DALUtils::parseInt(const string& str) {
    try {
        return std::stoi(str);
    } catch (const std::invalid_argument& e) {
        cout << "Error: invalid argument passed to parseInt: '" << str << "'\n";
        return 0;
    } catch (const std::out_of_range& e) {
        cout << "Error: out of range value passed to parseInt: '" << str << "'\n";
        return 0;
    }
}

bool DALUtils::fileManagementTest(const string& filename) {
    std::ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open file " << filename << "\n";
        return false;
    }

    return true;
}