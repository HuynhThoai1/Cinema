Test hoạt động Seat  
```Bash
$ g++ -std=c++23 main.cpp ../../bus/SeatBUS.cpp ../../dal/SeatDAL.cpp ../../dal/DALUtils.cpp -o ../../out/vu_test
$ ../../out/vu_test
```  
Test TicketUI  
```Bash
$ g++ -std=c++23 main.cpp TicketUI.cpp ../bus/BookingFacade.cpp ../bus/SeatBUS.cpp ../bus/TicketBUS.cpp ../bus/ShowtimeBUS.cpp ../bus/MovieBUS.cpp ../dal/SeatDAL.cpp ../dal/TicketDAL.cpp ../dal/ShowtimeDAL.cpp ../dal/MovieDAL.cpp ../dal/DALUtils.cpp ../dto/Ticket.cpp ../dto/Seat.cpp ../dto/TicketFactory.cpp -o ../out/TicketUI_test
$ ../out/TicketUI_test
