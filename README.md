#Hướng dẫn cài đặt
* Bước 1.Cài dặt thư trình biên dịch (nếu bạn đã cài đặt Mingw64 thì có thể bỏ qua bước này):
    * Tải mingw64 từ link này: [mingw64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z/download)
    * Giải nén thư mục vừa tải về.
    * Tạo một thư mục bất kỳ tại ổ C hoặc D rồi copy thư mục mingw64 vừa giải nén được vào thư mục vừa tạo.
    8 Chuột phải vào "This Pc"-> Chọn Properties -> Chọn "Advanced system settings" trong mục "Related Settings"-> Chọn "Environment variable"-> Double click vào "Path" trong phần "System Variable"-> Click vào New-> Browse và chọn tới thư mục bin nằm trong thư mục mingw64 rồi nhấn "OK".
* Bước 2. Giải nén file zip vừa tải về.
* Bước 3. Mở thư mục "Space Shooter" và chọn vào thanh địa chỉ của thư mục.
* Bước 4. Gõ vào thanh địa chỉ "cmd" rồi nhấn enter, cửa sổ cmd.exe sẽ hiện ra. Lúc này, gõ lệnh "mingw32-make" vào trong cửa sổ cmd.exe rồi chờ đợi khoảng 30 giây.
* Bước 5. Trong thư mục "Space Shooter" đã có file "spaceshooter.exe", chạy game bằng cách mở file này. 
#Mô tả chung
Một game bắn máy bay theo chiều dọc lấy khung cảnh ngoài vũ trụ, sử dụng chuột di chuyển máy bay né đạn và tiêu diệt các kẻ địch xuất hiện trên màn hình, hãy cố gắng tiêu diệt thật nhiều kẻ địch để đạt điểm cao.
#Các chức năng đã cài đặt
Video demo game: [Truy cập](https://youtu.be/zUWZ2j17m_Y)
* Game Menu.
* Tạm dừng game
* Restart game
* Các vật phẩm hỗ trợ:
    * Nâng cấp đạn
    * Thêm mạng
    * Khiên
* Lưu trữ highscore vào file.
* Âm thanh game
* Hiển thị điểm
#Các kỹ thuật lập trình được sử dụng
* Lập trình hướng đối tượng
* Mảng
* Con trỏ, cấp phát động, thu hồi bộ nhớ
* Vector
* Lớp
* Đọc, ghi file
* Xử lý va chạm
* Xử lý sự kiện từ chuột và bàn phím
* Các kỹ thuật đồ họa liên quan đến thư viện SDL2
#Kết luận
* Hướng phát triển: Sẽ thêm những đợt quái mới, các loại boss mới, phát triển thêm tính năng chọn độ khó cho game, thêm những loại đạn khác nhau, tạo thêm hai tàu nhỏ ở bên cạnh tàu chính để hỗ trợ tàu chính tiêu diệt kẻ địch dễ dàng hơn.
* Qua thời gian làm game, em đã học thêm nhiều điều như biết đến lập trình hướng đối tượng, học thêm được kỹ năng tra cứu và xử lý thông tin, hiểu rõ hơn về con trỏ trong ngôn ngữ lập trình C++, biết cách cài đặt một thư viện ngoài cho chương trình, hiểu về những câu lệnh để tự cài đặt chương trình từ source code. Không những vậy, việc tự phát triển một dự án còn giúp em có những kỹ năng về cách tự tổ chức một chương trình, học thêm về clean code - một kỹ năng giúp ích rất nhiều cho lập trình viên trong sự nghiệp lập trình.
#Credit
Dự án này có sự tham khảo từ anh Nguyễn Minh Đức, sinh viên K65, CN8: [Project của anh Nguyễn Minh Đức](https://github.com/minhduc1122002/BulletHeaven)



