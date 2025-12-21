$ g++ -std=c++23 main.cpp \
../bus/FoodBUS.cpp ../bus/RevenueBUS.cpp \
../bus/TicketBUS.cpp ../bus/SeatBUS.cpp \
../dal/FoodDAL.cpp ../dal/RevenueDAL.cpp \
../dal/TicketDAL.cpp ../dal/SeatDAL.cpp ../dal/DALUtils.cpp \
../dto/Food.cpp ../dto/Ticket.cpp ../dto/Seat.cpp \
-o ../out/thai_test


$ ../out/thai_test