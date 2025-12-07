#include "SeatDAL.h"
#include "DALUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <format>

using std::format;

vector<Seat> SeatDAL::loadSeats(const string& fileName) {
    vector<Seat> seats;
    std::ifstream file(fileName);
    string line;

    if(!DALUtils::fileManagementTest(fileName)) {
        return seats;
    }

    while(std::getline(file, line)) {
        vector<string> tokens = DALUtils::Split(line, " | ");
        if(tokens.size() < 3) {
            continue; 
        }
        Seat rowData;
        rowData._roomID = DALUtils::Trim(tokens[0]);
        rowData._rowID = DALUtils::Trim(tokens[1]);
        for(size_t i=2; i<tokens.size(); i++) {
            rowData._seatBooked.push_back(DALUtils::Trim(tokens[i]));
        }
        seats.push_back(rowData);
    }

    file.close();
    return seats;
}

bool SeatDAL::saveSeats(const string& room, const string& rowID, const vector<string>& seatBooked, const string& fileName) {
    if (!DALUtils::fileManagementTest(fileName)) {
        return false;
    }

    bool found = false;
    vector<Seat> seats = SeatDAL::loadSeats(fileName);
    for(size_t i=0; i<seats.size(); i++) {
        if(seats[i]._roomID == room && seats[i]._rowID == rowID) {
            seats[i]._seatBooked = seatBooked;
            found = true;
        }
    }

    if(!found) {
        std::cout << "find";
        Seat newSeat;
        newSeat._roomID = room;
        newSeat._rowID = rowID;
        newSeat._seatBooked = seatBooked;
        seats.push_back(newSeat);
    }

    std::ofstream file(fileName);
    string line;
    for(const Seat& seat : seats) {
        line = format("{} | {} | ", seat._roomID, seat._rowID);
        string updateSeatNumber = DALUtils::Join(seat._seatBooked, " | ");
        line += updateSeatNumber + "\n";

        file << line;
    }

    file.close();
    return true;
}

// Test

// int main() {
//     vector<Seat> seats = SeatDAL::loadSeats("../data/Seats.txt");

//     for (const Seat& seat : seats) {
//         std::cout << "Room: " << seat._roomID << ", SeatID: " << seat._rowID << ", Booked: ";
//         string seatBooked = DALUtils::Join(seat._seatBooked, ", ");
//         std::cout << seatBooked << std::endl;
//     }

//     SeatDAL::saveSeats("R01", "F", {"1", "3", "5", "7",}, "../data/Seats.txt");
//     return 0;
// }