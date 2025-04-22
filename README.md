# minesweeperSDL2-BTL-UET
# Giới thiệu về trò chơi
 - Dựa trên game Minesweeper của Microsoft, trò chơi được làm bằng ngôn ngữ C++ và thư viện đồ hoạ SDL2.
 - Mọi thông tin về thư viện SDL2, các cú pháp thường sử dụng tham khảo tại: https://www.libsdl.org/
 - Cách tải, liên kết thư viện SDL2 với project và tutorial SDL2, tham khảo tại: https://lazyfoo.net/tutorials/SDL/index.php
 - Trò chơi có sử dụng hình ảnh tại: https://www.flaticon.com/
 - Sau khi tải code về dưới dạng zip, có thể giải nén và vào thư mục exe, chạy file Game.exe để có thể chơi game. Nếu muốn tham khảo code, vào thư mục code, mở các file .h hoặc .cpp bằng notepad để xem code.
 - Mọi hình ảnh, âm thanh và font chữ được sử dụng trong trò chơi được lưu trong thư mục res.
 - Video demo tại đây
# Cách chơi
- Giống như trò dò mìn truyền thống, bạn phải mở các ô trên bảng sao cho không mở phải ô chứa mìn. Mỗi số ở các ô biểu thị cho số lượng mìn ở xung quanh ô đó. Nếu mở phải ô chứa mìn, bạn sẽ thua. Nếu mở được tất cả các ô không có mìn, bạn sẽ thắng. Nếu bạn muốn chơi lại, hãy nhấn vào biểu tượng mặt cười ở trên cửa sổ game.
- Có 4 chế độ có thể lựa chọn:
  + Dễ: gồm 9 hàng, 9 cột và 10 mìn.
  + Trung bình: gồm 16 hàng, 16 cột và 40 mìn.
  + Khó: gồm 30 hàng, 16 cột và 99 mìn.
- Tự chọn: Bạn có thể nhập số hàng, số cột và số mìn mà bạn muốn vào các ô tương ứng trên cửa sổ.
Sau mỗi lần chiến thắng, thời gian mà bạn hoàn thành sẽ được lưu vào file txt trong thư mục score. Với chế độ tự chọn, trò chơi sẽ tự tạo file txt tương ứng với số liệu mà bạn nhập vào.
