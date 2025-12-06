## Biên dịch & chạy TicketDAL
```Bash
$ g++ -std=c++23 TicketDAL.cpp DALUtils.cpp -o run
```
```Bash
$ ./run
```

## Biên dịch & chạy SeatDAL
```Bash
$ g++ -std=c++23 SeatDAL.cpp DALUtils.cpp -o run
```
```Bash
$ ./run 
```

# file Seats.txt được ghi theo định dạng:
`roomID | rowID | seat1 | seat2 | ... | seatN Booked`

# file Tickets.txt được ghi theo định dạng:
`ticketID | movie | roomID | seatID | customerID | price | showTime | date`

# file FoodandDrink.txt được ghi theo định dạng:
`foodID | foodName | price`

# file Logs.txt được ghi theo định dạng:
`date | time | employeeID | action | actionDetails`

# file Revenues.txt được ghi theo định dạng:
`date | ticketRevenue | foodAndDrinkRevenue | totalRevenue`
