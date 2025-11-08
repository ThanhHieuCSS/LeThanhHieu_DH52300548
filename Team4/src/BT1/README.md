I-MÔ TẢ CHƯƠNG TRÌNH
Chương trình thực hiện tìm đường đi ngắn nhất trong kho hàng (dạng lưới) bằng thuật toán BFS (Breadth-First Search).
    Mỗi ô trong bản đồ thể hiện trạng thái khác nhau của kho:
        Số 0 — Tường hoặc vật cản không thể đi qua
        Số 1 — Đường có thể đi được 
        Số 2 — Điểm xuất phát (Start)
        Số 3 — Điểm đích (End)
    Kết quả cuối cùng sẽ hiển thị đường đi ngắn nhất từ điểm bắt đầu đến điểm kết thúc, được đánh dấu bằng ký tự *.
II-CÁCH CHẠY CHƯƠNG TRÌNH
    1-Tạo file input.txt trong thư mục Team4/BT1 cùng thư mục với solution.cpp(nếu đã có file rồi thì không cần tạo thêm).
    2-Ghi dữ liệu bản đồ vào file này theo đúng định dạng này.
    ----------ĐỊNH DẠNG--------
    --  n m                  --
    --  a11 a12 a13 ... a1m  --
    --  a21 a22 a23 ... a2m  --
    --  ...                  --
    --  an1 an2 an3 ... anm  --
    ---------------------------
        Trong đó:
            - n = số hàng.
            - m = số cột.
            - Các giá trị trong ma trận là 0, 1, 2 hoặc 3.
    3-Chạy chương trình bằng một trong các cách:
        Cách 1 (PowerShell / CMD):("Vì giảng viên chấm bài trên github nên dùng cách này sẽ tối ưu hơn và em sẽ có file ppt hướng dẫn chạy trên github")
            g++ solution.cpp -o solution.exe
            ./solution.exe

        Cách 2 (VS Code):
            Nhấn Ctrl + F5 (Run without Debugging).
            Kết quả sẽ được ghi vào file output.txt.
