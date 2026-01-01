#include "DALUtils.h"
#include <iostream>
#include <sstream>
#include <fstream>

using std::stringstream, std::cout;

string DALUtils::Trim(string str) {
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

string DALUtils::Join(vector<string> list, string delimiter) {
    string res;

    for(string item : list) {
        if (!res.empty()) {
            res += delimiter;
        }

        res += item;
    }

    return res;
}

vector<string> DALUtils::Split(string str, string delimiter) {  
    vector<string> list;
    int delimiterPos = 0;
    string token;
    int head = 0;

    while((delimiterPos = str.find(delimiter, head)) != string::npos) {
        token = str.substr(head, delimiterPos-head);
        list.push_back(token);
        head = delimiterPos + delimiter.length();
    }

    list.push_back(str.substr(head));

    return list;
}

int DALUtils::parseInt(string str) {
    return std::stoi(str);
}

bool DALUtils::fileManagementTest(string filename) {
    std::ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open file " << filename << "\n";
        return false;
    }

    return true;
}