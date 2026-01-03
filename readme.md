# ------------------- REPORT -------------------

# 📌 ĐỒ ÁN OOP – HỆ THỐNG QUẢN LÝ VÀ BÁN VÉ RẠP CHIẾU PHIM

## 1. Thông tin nhóm

- **Tên đề tài:** Hệ thống quản lý và bán vé rạp chiếu phim (Cinema Ticket Management System)
- **Môn học:** Lập trình hướng đối tượng (OOP – C++)
- **Nhóm:** Group 03

### 👥 Thành viên nhóm

| STT | Họ và tên | MSSV | Vai trò |
|---|---|---|---|
| 1 | Huỳnh Chí Thoại | 24120457 | Nhóm trưởng |
| 2 | Lương Nguyễn Hoàng Vũ | 24120493 | Thành viên |
| 3 | Đoàn Phước Đạt | 24120034 | Thành viên |
| 4 | Đoàn Ngọc Bảo | 24120168 | Thành viên |
| 5 | Mai Văn Hiển | 24120308 | Thành viên |
| 6 | Cái Hoàng Thái | 24120439 | Thành viên |

---

## 2. Mô tả đề tài

Đề tài xây dựng một **hệ thống quản lý và bán vé rạp chiếu phim** bằng ngôn ngữ **C++**, áp dụng các nguyên lý **lập trình hướng đối tượng (OOP)** như đóng gói, kế thừa, đa hình và phân tách trách nhiệm giữa các lớp.

Hệ thống cho phép:

- Quản lý phim, suất chiếu, vé, thức ăn, doanh thu dành cho Admin
- Thực hiện các chức năng xem phim, xem lịch chiếu, đặt vé và mua đồ ăn dành cho Customer.
- Phân quyền người dùng (Admin / Customer)
- Thao tác thông qua giao diện console


---

## 3. Phân công công việc

| Thành viên | Công việc đã thực hiện |
|---|---|
| Huỳnh Chí Thoại | Thiết kế kiến trúc tổng thể, menu base class, main.cpp, merge code.|
| Lương Nguyễn Hoàng Vũ | Thực hiện module Seat, Booking + hỗ trợ merge code |
| Đoàn Phước Đạt | Thực hiện module Ticket + Utils |
| Đoàn Ngọc Bảo | Thực hiện module Movie + Showtime |
| Mai Văn Hiển | Thực hiện module Auth/User |
| Cái Hoàng Thái | Thực hiện module Food + Revenue + Test thử |

---
Các thành viên thực hiện các module theo DTO → DAL → BUS → UI cơ bản

## 4. Các công việc đã thực hiện chi tiết:

### 4.1. Huỳnh Chí Thoại
Các công việc chính:

- Chuẩn bị nội dung cuộc họp, phân chia công việc, viết báo cáo.
- Viết class Diagram.
- Tạo repo GitHub, quản lý branch.
- Thiết kế thư mục, file, code mẫu.
- Merge code, kết nối các module.
- Code lại giao diện UI.
- Viết báo cáo tổng kết.

Mô tả công việc:

- Thống kê và nắm tiến độ công việc theo tuần để chuẩn bị kế hoạch.
- Giải thích cách main gọi các BUS.
- Luồng chương trình từ đăng nhập → sử dụng hệ thống.
- Triển khai các nguyên lý OOP. 
- Code lại một số logic, bug.
- Thực hiện lại Revenue được tính tự động, không cần tính thủ công.
- Thiết kế UI thống nhất giữa các module và có màu sắc.
- Xây dựng bash chạy chương trình.
- Testing và fix bug.

Khó khăn & cách giải quyết:

- Xung đột module → chia lại nhóm theo module.
- Thống nhất API giữa các nhóm.
- Đường dẫn file đến data có thể lỗi do vị trí compile → Tạo format đường dẫn FilePath cho phép đúng về đường dẫn khi compile ở bất cứ đâu.
- Hệ điều hành của người dùng có thể ảnh hưởng đến code → Sử dụng IF - ELSE để thực hiện tùy vào hệ điều hành người dùng. 

Cải tiến đề xuất:

- Áp dụng một số Design pattern như Registry cho đọc file và Decorator cho output chương trình.
- Có thể tách UI thành GUI trong tương lai.
- Thay file txt bằng database.

### 4.2. Lương Nguyễn Hoàng Vũ 

Nhiệm vụ được giao:

- Xử lý nghiệp vụ booking
- Tạo dữ liệu ghế
- Quản lý ghế
- Tạo các loại vé ( bình thường, trẻ em, sinh viên,..)
- Tạo FormatUI

Các file đã thực hiện:

- DTO/NormalTicket.h
- DTO/StudentTicket.h
- DTO/ChildTicket.h
- DTO/Seat.h/.cpp
- DAL/SeatDAL.h / .cpp
- BUS/SeatBUS.h / .cpp
- BUS/BookingFacade.h / .cpp
- UI/TicketUI.h / .cpp 
- Data/Seats.txt
- Data/Tickets.txt
- Utils/FormatUI.h /.cpp

Mô tả chi tiết:

- Áp dụng nguyên lý Kế thừa (Inheritance) và Đa hình (Polymorphism) trong lập trình hướng đối tượng để tạo quản lý các loại vé:
Cấu trúc lớp: Có một lớp cơ sở trừu tượng (Base Class) là Ticket chứa các thuộc tính chung (như ticketId, showtimeId, seatId, price). Từ đó sử dụng kế thừa tạo ra các loại vé cụ thể như NormalTicket (Vé người lớn), StudentTicket (Vé sinh viên), ChildTicket (Vé trẻ em) sẽ kế thừa từ lớp này.
Lợi ích: Việc này giúp chuẩn hóa dữ liệu đầu vào, dễ dàng mở rộng thêm các loại vé mới (ví dụ: VIPTicket, MemberTicket) mà không làm ảnh hưởng đến cấu trúc hiện tại. Đồng thời, hệ thống có thể quản lý danh sách vé thông qua con trỏ lớp cha (Ticket*), giúp tối ưu hóa việc xử lý logic chung.
- Tạo ra module Seat tuân theo cấu trúc 3 lớp để thực hiện được việc quản lí danh sách ghế ở các phòng khi người dùng thực hiện đặt vé hoặc hủy vé 
- Dữ liệu ghế được lưu trong Seat.txt với cấu trúc:  
 Suất chiếu | Tên phòng | tên hàng ghế | giá tiền | các số ghế đã đặt  
- Tầng Nghiệp vụ (BUS - Business Logic Layer): Đây là trung tâm xử lý logic của hệ thống, áp dụng mẫu thiết kế Facade Pattern để đơn giản hóa quy trình tương tác với UI:
BookingFacade: Đây là thành phần quan trọng nhất, đóng vai trò là "mặt tiền" (Facade) che giấu sự phức tạp của hệ thống bên dưới.
Tầng UI chỉ cần gọi một hàm duy nhất (ví dụ: processBooking), BookingFacade sẽ tự động điều phối các nghiệp vụ con: kiểm tra trạng thái ghế từ SeatBUS, tính toán giá tiền từ TicketBUS, và cập nhật doanh thu.
Cơ chế này giúp giảm sự phụ thuộc (Decoupling) giữa giao diện người dùng (UI) và logic xử lý (BUS).
SeatBUS: Chứa các quy tắc nghiệp vụ cốt lõi (Domain Logic): kiểm tra tính hợp lệ của ghế, trạng thái đặt chỗ (Available/Booked) lấy giá tiền cụ thể của vé đã được lưu trong Seat.txt.

Design Pattern áp dụng:

- Facade Pattern (BookingFacade)
Quy trình đặt vé rất phức tạp, bao gồm nhiều bước nhỏ: Kiểm tra ghế trống -> Khóa ghế -> Tính tiền -> Tạo vé -> Lưu vé -> Cập nhật trạng thái ghế. Nếu để UI gọi từng bước này, code sẽ rất rối và khó quản lý.
Facade pattern giải quyết vấn đề này, xử lí các bước đặt vé thông qua class BookingFacade.

Nguyên lý OOP cơ bản:

- Inheritance: NormalTicket, ChildTicket, StudentTicket kế thừa từ Ticket
- Encapsulation: Muốn xem hay sửa dữ liệu từ các class Seat và Ticket cần phải thông qua getter/setter

Cải tiến:

- Chống double booking:
Ngay khi một ghế được đặt thành công thì trạng thái ghế trong Seats.txt cần phải cập nhật ngay lập tức thành trước khi tiến hành thanh toán
Nếu hai người cùng chọn một ghế, người đến sau sẽ nhận được thông báo lỗi "Ghế vừa được đặt bởi người khác" do trạng thái đã thay đổi ở tầng DAL.
- Thêm đổi ghế:
Thực hiện việc đổi ghế, nếu thành công thì thực hiện lại đặt vé mới, còn không thì khôi phục lại vé cũ
- Thêm tự tạo Room khi tạo suất chiếu mới


### 4.3. Đoàn Phước Đạt

Nhiệm vụ được giao:

- Tạo vé, hủy vé
- Tạo các tiện ích Utils hỗ trợ cho tầng DAL và BUS
- Tạo dữ liệu Ticket

Các file đã thực hiện:

- DTO/Ticket.h / .cpp
- DTO/TicketFactory.h / .cpp
- DAL/TicketDAL.h / .cpp
- DAL/DALUtils.h/.cpp
- BUS/TicketBUS.h / .cpp
- BUS/BUSUtils.h/.cpp
- Data/Ticket.txt

Mô tả chi tiết:

- Xây dựng một lớp cơ sở trừu tượng (Base Class) là Ticket chứa các thuộc tính chung (như ticketId, showtimeId, seatId, price). 
Lợi ích: Việc này giúp chuẩn hóa dữ liệu đầu vào.
- Ở tầng DTO, Class Ticket đại diện cho trạng thái của một chiếc vé đã được khởi tạo trong hệ thống.
Lớp chứa đầy đủ các thuộc tính định danh và mô tả vé bao gồm: _ticketID (Mã vé), _showtimeID (Mã suất chiếu), _seatID (Mã ghế), _price (Giá vé), _customerName (Tên khách hàng)
- Ở tầng DAL, DALUtils có nhiệm vụ cung cấp các hàm để hỗ trợ thao tác với dữ liệu. TicketDAL thao tác trực tiếp với dữ liệu qua loadTickets, saveTickets 
- Tầng Nghiệp vụ (BUS - Business Logic Layer): Đây là trung tâm xử lý logic của hệ thống,
TicketBUS: Chứa các quy tắc nghiệp vụ cốt lõi (Domain Logic): Quản lý danh sách vé, tính toán tổng tiền dựa trên loại vé và các chính sách giảm giá. Các hàm này được BookingFacade gọi để hoàn tất quy trình giao dịch.
BUSUtils: Cung cấp các hàm hỗ trợ tính toán nghiệp vụ dùng chung 

Design Pattern áp dụng:

- Factory Pattern (TicketFactory)	
Mỗi lần tạo vé cần có các ID khác nhau để quản lý vé dễ dàng hơn. 
Thay vì tạo ID thủ công, gọi hàm tạo ID riêng cho vé và trả về Ticket

Nguyên lý OOP cơ bản:

- Encapsulation:
Muốn xem hay sửa dữ liệu từ các class Seat và Ticket cần phải thông qua getter/setter 

Cải tiến:

- Thêm các loại phòng chiếu: Thêm lựa chọn đa dạng hơn trong việc mua vé.
- Nâng cấp cơ sở dữ liệu: thay vì lưu dữ liệu ở file txt, có thể sử dụng MySQL hoặc PostgreSQL để chuyên nghiệp hơn

### 4.4. Đoàn Ngọc Bảo
Công được phân công:
- Quản lý phim và suất chiếu  

Các file đã thực hiện:
- DTO/Movie.h
- DTO/Showtime.h
- DAL/MovieDAL.h / .cpp
- DAL/ShowtimeDAL.h / .cpp
- BUS/MovieBUS.h / .cpp
- BUS/ShowtimeBUS.h / .cpp
- Data/Movies.txt
- Data/Showtimes.txt

Mô tả chi tiết:

- Module Movie – Cách lưu trữ và xử lý dữ liệu: Dữ liệu phim được lưu dưới dạng text file Movies.txt, mỗi dòng tương ứng một phim với cấu trúc MovieID|Title|Genre|Duration|Status, MovieDAL sử dụng ifstream đọc từng dòng, tách chuỗi bằng dấu | và khởi tạo đối tượng Movie đưa vào vector<Movie>, khi có thao tác thêm, sửa, xóa thì ghi lại toàn bộ danh sách bằng ofstream để đảm bảo đồng bộ dữ liệu.
- Module Movie – Xử lý nghiệp vụ: MovieBUS chịu trách nhiệm xử lý logic như kiểm tra trùng ID khi thêm phim, không cho xóa phim đang có suất chiếu, chỉ cho phép hiển thị phim có trạng thái hợp lệ, UI chỉ gọi các hàm public của MovieBUS và không thao tác trực tiếp với file.
- Module Showtime – Cách lưu trữ và xử lý dữ liệu: Dữ liệu suất chiếu được lưu trong file Showtimes.txt, mỗi dòng có cấu trúc ShowtimeID|MovieID|Room|Date|Time, ShowtimeDAL đọc file bằng ifstream, tách dữ liệu bằng dấu |, khởi tạo đối tượng Showtime và lưu vào vector<Showtime>, mọi thay đổi đều được ghi lại toàn bộ file để đảm bảo tính nhất quán.
- Module Showtime – Xử lý nghiệp vụ: ShowtimeBUS kiểm tra sự tồn tại của MovieID trước khi tạo suất chiếu, ngăn trùng phòng – trùng thời gian, không cho xóa suất chiếu đã có vé đặt, đảm bảo tính toàn vẹn dữ liệu và logic nghiệp vụ của hệ thống.
- Phân quyền Admin / User trong Movie & Showtime: Sau khi đăng nhập, hệ thống kiểm tra role người dùng, Admin được phép thêm, sửa, xóa phim và suất chiếu thông qua AdminMenu, Customer chỉ được xem danh sách phim và suất chiếu thông qua CustomerMenu, toàn bộ quyền được kiểm soát tại tầng UI và BUS.

Nguyên lý OOP áp dụng:

- Áp dụng Encapsulation khi các thuộc tính của Movie và Showtime được đặt ở private và truy cập thông qua getter/setter, áp dụng phân lớp rõ ràng DTO–DAL–BUS–UI để tách biệt dữ liệu, xử lý file, nghiệp vụ và giao diện, đồng thời sử dụng quan hệ Association khi Showtime liên kết với Movie thông qua MovieID.


Cải tiến:

- Thêm lọc theo ngày/giờ
- Kiểm tra trùng suất chiếu


### 4.5. Mai Văn Hiển
Nhiệm vụ được giao:

- Quản lý tài khoản người dùng
- Đăng nhập, đăng ký, phân quyền

Các file đã thực hiện:

- DTO/User.h
- DTO/Admin.h
- DAL/UserDAL.h / .cpp
- BUS/UserBUS.h / .cpp
- BUS/AdminBUS.h / .cpp
- Data/Users.txt  

Mô tả chi tiết:

- Cách lưu user trong file:
Định dạng: Dữ liệu được lưu dưới dạng văn bản thuần (Text file), mỗi dòng đại diện cho một người dùng.
Cấu trúc dòng: ID|Username|Password|Role. Sử dụng dấu gạch đứng để tách các trường thông tin.
Quy trình: Class UserDAL sử dụng ifstream để đọc từng dòng, dùng hàm split để cắt chuỗi dựa trên dấu “|”, sau đó khởi tạo đối tượng Admin hoặc Customer tương ứng vào vector<User*>.
- Cách kiểm tra đăng nhập: Gọi loadData() để cập nhật danh sách mới nhất từ file (đảm bảo tính thời gian thực). Vòng lặp for duyệt qua vector<User*>. Kiểm tra nếu username và password nhập vào trùng khớp với dữ liệu trong vector. Nếu thông tin đúng, hệ thống kiểm tra tiếp Role. Nếu Role == “Locked” thì chặn đăng nhập và thông báo lỗi, ngược lại thì cho phép đăng nhập. Cuối cùng trả về con trỏ User* chứa thông tin người dùng để UI xử lý.
- Phân quyền admin / user dựa theo cơ chế Role-based Access Control:
Tầng dữ liệu: thuộc tính role trong class User lưu giá trị “Admin” hoặc “Customer”.
Tầng giao diện: Sau khi đăng nhập thành công, hệ thống kiểm tra user->getRole(). Nếu là Admin thì khởi tạo và hiển thị AdminMenu(). Nếu là Customer thì khỏi tạo và hiển thị CustomerMenu().
Bảo mật: Các chức năng nhạy cảm (Khóa tài khoản, Xem danh thu) được đóng gói trong AdminBUS, User thường không có cách nào gọi được các hàm này.

Nguyên lý OOP áp dụng:

- Kế thừa (Inheritance): Class cha (User) chứa các thuộc tính chung mà ai cũng có: id, username, password, role. Class con (Admin, Customer) kế thừa các thuộc tính này từ class cha (User). Việc áp dụng nguyên lý này giúp tái sử dụng code và dễ dàng mở rộng nếu sau này có thêm Manager hay Staff.
- Đa hình (Polymorphism): Sử dụng vector<User*> để quản lý chung cả Admin và Customer trong cùng một danh sách. Sử dụng virtual ~User() (Destructor ảo) để đảm bảo hủy đúng đối tượng khi delete con trỏ, tránh rò rỉ bộ nhớ.
- Đóng gói (Encapsulation): Các thuộc tính (id, username,...) được đặt là protected để ngăn chặn truy cập trực tiếp từ bên ngoài. Dữ liệu chỉ được truy xuất hoặc thay đổi thông qua các phương thức công khai (Public methods như getId(), setPassword()). Giúp bảo vệ tính toàn vẹn của dữ liệu.

Cải tiến:

- Mã hóa mật khẩu
- Thêm reset password


### 4.6. Cái Hoàng Thái

Nhiệm vụ được giao:

- Thiết kế mua đồ ăn
- Thống kê doanh thu
- Quay video demo

Các file đã thực hiện:

- DTO/Food.h
- DTO/Revenue.h
- DAL/FoodDAL.h / .cpp
- DAL/RevenueDAL.h / .cpp
- BUS/FoodBUS.h / .cpp
- BUS/RevenueBUS.h / .cpp
- Data/FoodandDrink.txt
- Data/Revenues.txt

Mô tả:
- Ghi doanh thu từ vé & đồ ăn: Khi một giao dịch hoàn tất (gồm vé và đồ ăn), hệ thống sẽ bóc tách và ghi nhận đồng thời cả hai nguồn thu vào file quản lý.
- Thống kê:
Theo ngày: Truy vấn dữ liệu doanh thu trong một khoảng thời gian cụ thể.
Theo phim:  Liên kết dữ liệu từ lịch chiếu và vé để tính toán phim nào mang lại lợi nhuận cao nhất.

Nguyên lý OOP áp dụng:

- Encapsulation (Đóng gói): Toàn bộ thuộc tính của Food và Revenue được để private. Các lớp BUS muốn truy cập phải thông qua Getter/Setter, giúp kiểm soát tính chính xác của dữ liệu tài chính (ví dụ: giá đồ ăn không được âm).
- Separation of Concerns: Tách biệt hoàn toàn việc quản lý danh mục đồ ăn (FoodDAL/BUS) và việc quản lý dòng tiền (RevenueDAL/BUS), giúp dễ dàng bảo trì hoặc thay đổi đơn giá mà không ảnh hưởng đến lịch sử doanh thu đã lưu.

Cải tiến:

- Xuất báo cáo: hệ thống sẽ kết xuất dữ liệu doanh thu ra file văn bản (.txt hoặc .csv) theo định dạng bảng biểu đồ để có thể dễ dàng quản lý và lưu trữ lại,  giúp người quản lý có bản in báo cáo cuối ngày mà không cần mở code.
- Biểu đồ doanh thu: sử dụng đồ họa hoặc công cụ hỗ trợ vẽ biểu đồ cột doanh thu theo ngày (tháng) để giúp xem xu hướng khách hàng; từ đó lên kế hoạch để rạp phim phát triển và phục vụ một cách trực quan nhất.
- Đặt đồ ăn và đồ uống: việc đặt đồ ăn sẽ tích hợp với đặt vé để tiết kiệm thời gian hơn cho khách hàng. 



---

## 5. Tỉ lệ đóng góp của các thành viên

(Tổng = 100%)

| Thành viên | Tỉ lệ đóng góp |
|---|---|
| Huỳnh Chí Thoại | 16.67% |
| Lương Nguyễn Hoàng Vũ | 16.67% |
| Đoàn Phước Đạt | 16.67% |
| Đoàn Ngọc Bảo | 16.67% |
| Mai Văn Hiển | 16.67% |
| Cái Hoàng Thái | 16.67% |

---

## 6. Video demo chương trình

- **Thời lượng:** tối đa 5 phút  
- **Nội dung:** Demo các luồng chức năng chính của chương trình  

**Link video demo:**   https://youtu.be/0YySpvv8srg

---

## 7. Cấu trúc thư mục

```text
MSSV/
│
├── readme.md (Chứa report)
│
├── source/
│   ├── bus
│   ├── dal
│   ├── data
│   ├── dto
│   ├── out 
│   ├── ui (chứa main)
│   ├── utils 
│   └── readme.md (chứa bash chạy chương trình)
│
└── release/
    └── cinema.exe
```

## 8. Cấu trúc Diagram
https://www.mermaidchart.com/app/projects/44b6f976-db06-45c9-bd62-1b388ae7ec1b/diagrams/48c5a696-ba18-4c36-8f78-e3229a52d82d/share/invite/eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkb2N1bWVudElEIjoiNDhjNWE2OTYtYmExOC00YzM2LThmNzgtZTMyMjlhNTJkODJkIiwiYWNjZXNzIjoiVmlldyIsImlhdCI6MTc2NzQyNzE5OH0.i-mzqsDaKu_UUKxdUDyqmXWjgqE2wzMwxxVoez4DhYE