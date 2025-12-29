# CẢI TIẾN HỆ THỐNG REVENUE

## Tổng quan
Hệ thống Revenue đã được cải tiến để **tự động ghi nhận doanh thu** ngay khi khách hàng mua vé hoặc mua đồ ăn, thay vì phải nhập thủ công như trước.

## Những thay đổi chính

### 1. **Cấu trúc dữ liệu mới (Revenue DTO)**

**Trước đây:**
```
id, date, movieId, ticketRevenue, foodRevenue
```

**Bây giờ:**
```
id, timestamp, revenueType, relatedId, amount, additionalInfo
```

**Ý nghĩa các trường:**
- `id`: Mã bản ghi (R01, R02, ...)
- `timestamp`: Thời gian thực tế từ máy tính (dd/mm/yyyy HH:MM:SS)
- `revenueType`: Loại doanh thu (TICKET hoặc FOOD)
- `relatedId`: Mã phim (nếu TICKET) hoặc FOOD_ORDER (nếu FOOD)
- `amount`: Số tiền
- `additionalInfo`: Thông tin bổ sung (user, số ghế, món ăn đã mua...)

### 2. **Tự động ghi nhận doanh thu**

#### Khi mua vé (BookingFacade.cpp):
- Chỉ thêm **5 dòng code** vào cuối hàm `processBooking()`
- Tự động ghi nhận tổng tiền vé đã thanh toán
- Lưu thông tin: User ID, Showtime ID, số ghế đã đặt

```cpp
// [MỚI] GHI NHẬN DOANH THU TỰ ĐỘNG
if (totalPrice > 0) {
    string movieId = showtimePtr->getMovieId();
    string info = "User: " + userId + ", Showtime: " + showtimeId + ", Seats: " + to_string(successCount);
    revenueBus.recordRevenue("TICKET", movieId, (int)totalPrice, info);
}
```

#### Khi mua đồ ăn (FoodUI.cpp):
- Chỉ thêm **10 dòng code** vào cuối hàm `purchaseFood()`
- Tự động ghi nhận tổng tiền đồ ăn đã mua
- Lưu thông tin: Danh sách món và số lượng

```cpp
// [MỚI] GHI NHẬN DOANH THU TỰ ĐỘNG
if (total > 0) {
    std::stringstream infoStream;
    infoStream << "Items: ";
    for(size_t i = 0; i < ids.size(); i++) {
        if (i > 0) infoStream << ", ";
        infoStream << ids[i] << "x" << quantities[i];
    }
    revenueBus.recordRevenue("FOOD", "FOOD_ORDER", total, infoStream.str());
}
```

### 3. **Timestamp tự động (RevenueBUS)**

Thêm hàm `getCurrentTimestamp()` để lấy thời gian thực từ hệ thống:
```cpp
std::string RevenueBUS::getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << ltm->tm_mday << "/"
       << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << "/"
       << (1900 + ltm->tm_year) << " "
       << std::setfill('0') << std::setw(2) << ltm->tm_hour << ":"
       << std::setfill('0') << std::setw(2) << ltm->tm_min << ":"
       << std::setfill('0') << std::setw(2) << ltm->tm_sec;
    
    return ss.str();
}
```

### 4. **Giao diện hiển thị (RevenueUI)**

Giao diện đã được điều chỉnh để hiển thị:
- Timestamp đầy đủ (ngày + giờ)
- Loại doanh thu (TICKET/FOOD)
- Tổng doanh thu tích lũy

**Ví dụ hiển thị:**
```
--------------------------------------------------------
ID    THỜI GIAN           LOẠI    MÃ        SỐ TIỀN
--------------------------------------------------------
R01   28/12/2025 14:30:15 TICKET  M01       150000 VND
R02   28/12/2025 14:35:22 FOOD    FOOD_OR   45000 VND
R03   28/12/2025 15:10:45 TICKET  M02       200000 VND
--------------------------------------------------------
TỔNG DOANH THU: 395000 VND
--------------------------------------------------------
```

## Lợi ích

### ✅ Tự động hóa
- Không cần nhập doanh thu thủ công
- Giảm thiểu sai sót do con người

### ✅ Chi tiết hơn
- Timestamp chính xác đến giây
- Phân loại rõ ràng TICKET/FOOD
- Lưu thông tin bổ sung để truy vết

### ✅ Dễ mở rộng
- Có thể thêm các loại doanh thu khác (MERCHANDISE, PARKING...)
- Dễ dàng lọc và phân tích theo loại

### ✅ Tối thiểu thay đổi
- Chỉ thêm vài dòng code vào các file hiện có
- Không phá vỡ cấu trúc cũ
- Giữ nguyên giao diện người dùng

## File đã thay đổi

### Modified Files:
1. **dto/Revenue.h** & **dto/Revenue.cpp** - Cấu trúc DTO mới
2. **dal/RevenueDAL.h** & **dal/RevenueDAL.cpp** - Đọc/ghi format mới
3. **bus/RevenueBUS.h** & **bus/RevenueBUS.cpp** - Logic timestamp & ghi nhận
4. **bus/BookingFacade.h** & **bus/BookingFacade.cpp** - Tích hợp ghi doanh thu vé
5. **ui/FoodUI.h** & **ui/FoodUI.cpp** - Tích hợp ghi doanh thu đồ ăn
6. **ui/RevenueUI.cpp** - Giao diện hiển thị mới
7. **data/Revenue.txt** - Dữ liệu mới (xóa dữ liệu cũ không tương thích)

## Cách sử dụng

### Người dùng (Customer)
- **Không cần làm gì thêm!** 
- Mua vé hoặc mua đồ ăn như bình thường
- Hệ thống tự động ghi nhận doanh thu ở background

### Quản trị viên (Admin)
1. Vào menu **Quản lý Doanh thu**
2. Chọn **Xem báo cáo** để xem danh sách doanh thu
3. Các bản ghi được ghi tự động khi có giao dịch

### Format file Revenue.txt
```
R01,28/12/2025 14:30:15,TICKET,M01,150000,User: john, Showtime: ST01, Seats: 2
R02,28/12/2025 14:35:22,FOOD,FOOD_ORDER,45000,Items: F01x2, F03x1
```

## Testing

Để kiểm tra hệ thống:

1. **Build project:**
```bash
cd /workspaces/codespaces-blank/project_cinema/Cinema
g++-14 -std=c++23 ui/*.cpp dal/*.cpp bus/*.cpp -I ui -I dal -I bus -o out/cinema_app
```

2. **Chạy và test:**
   - Đăng nhập và đặt vé → Kiểm tra file `data/Revenue.txt`
   - Mua đồ ăn → Kiểm tra lại file
   - Vào menu Admin → Quản lý Doanh thu → Xem báo cáo

## Tương thích ngược

Hàm `addRevenueRecord()` cũ vẫn được giữ lại để tương thích:
```cpp
void RevenueBUS::addRevenueRecord(std::string date, std::string movieId, 
                                   int ticketAmount, int foodAmount)
```

Hàm này sẽ tự động chuyển đổi sang format mới.

## Ghi chú

- File `Revenue.txt` cũ không tương thích → Đã xóa để bắt đầu mới
- Timestamp sử dụng giờ địa phương của máy tính
- Nếu muốn filter theo ngày, dùng hàm `getByDate()` trong RevenueBUS

---

**Ngày cập nhật:** 28/12/2025  
**Phiên bản:** 2.0  
**Người thực hiện:** GitHub Copilot
