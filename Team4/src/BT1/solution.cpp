#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

// ===== Cấu trúc lưu 1 điểm (tọa độ trong kho) =====
struct Point {
    int x, y;
};

// ===== 4 hướng di chuyển: lên, xuống, trái, phải =====
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// ===== Kiểm tra ô hợp lệ =====
bool isValid(int x, int y, int n, int m, vector<vector<int>>& a, vector<vector<bool>>& visited) {
    return (x >= 0 && y >= 0 && x < n && y < m && a[x][y] != 0 && !visited[x][y]);
}

// ===== Hàm chính =====
int main() {
    // Đọc dữ liệu từ file input.txt và ghi ra file output.txt
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m; // Nhập kích thước ma trận (n hàng, m cột)

    vector<vector<int>> a(n, vector<int>(m));             // Bản đồ kho hàng
    vector<vector<bool>> visited(n, vector<bool>(m, false)); // Mảng đánh dấu đã đi qua
    vector<vector<Point>> parent(n, vector<Point>(m, {-1, -1})); // Ghi nhớ ô cha để truy vết đường đi

    Point start, end;

    // ===== Đọc ma trận và tìm điểm bắt đầu / kết thúc =====
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 2) start = {i, j};
            if (a[i][j] == 3) end = {i, j};
        }
    }

    // ===== BFS tìm đường ngắn nhất =====
    queue<Point> q;     // Hàng đợi lưu các ô cần xét
    q.push(start);      // Đưa ô bắt đầu (Start) vào hàng đợi
    visited[start.x][start.y] = true; // Đánh dấu ô bắt đầu đã được thăm

    bool found = false; // Biến cờ kiểm tra xem có tìm được đường đi đến đích hay không

    // ===== Bắt đầu vòng lặp BFS =====
    while (!q.empty()) {                    // Khi hàng đợi vẫn còn phần tử
        Point cur = q.front();              // Lấy phần tử đầu tiên trong hàng đợi (ô hiện tại)
        q.pop();                            // Xóa nó khỏi hàng đợi sau khi lấy ra

        // Nếu đến được điểm đích thì dừng lại-> tìm thấy đường đi, thoát vòng lặp
        if (cur.x == end.x && cur.y == end.y) {
            found = true;                   // Đặt cờ "đã tìm thấy"
            break;                          // Dừng thuật toán
        }

        // Duyệt 4 hướng
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];         // Tính hàng của ô kế tiếp
            int ny = cur.y + dy[i];         // Tính cột của ô kế tiếp

            // Nếu ô mới hợp lệ (trong bản đồ, không phải tường, chưa thăm)
            if (isValid(nx, ny, n, m, a, visited)) {
                visited[nx][ny] = true;// Đánh dấu ô này đã được thăm
                parent[nx][ny] = cur; // Ghi nhớ đường đi
                q.push({nx, ny});   // Thêm ô này vào hàng đợi để duyệt tiếp
            }
        }
    }

    // ===== Nếu không tìm được đường =====
    if (!found) {
        cout << "Không có đường đi!" << endl;
        return 0;
    }

    // ===== Truy vết lại đường đi =====
    vector<vector<char>> result(n, vector<char>(m, ' '));  //Ngay khi bạn tạo ma trận result, toàn bộ các ô trong ma trận đều sẽ có giá trị ' ' (khoảng trắng).
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            //result[i][j] = (a[i][j] == 0 ? '#' : '.'); // # = tường, . = ô trống (hàm ss ngắn gọn)            
            if (a[i][j] == 0)
                result[i][j] = '#'; // gán thay ' ' (khoảng trắng) thành '#' (Tường)
            else
                result[i][j] = '.'; // gán thay ' ' (khoảng trắng) thành '.' (Đường trống/có thể đi)

    // Đi ngược từ End về Start để đánh dấu '*'
    Point cur = end;                                    // Bắt đầu từ điểm đích (End)
    // Duyệt ngược lại từ End về Start, dựa vào mảng "parent"
    // Mỗi ô trong "parent" chứa tọa độ của ô cha (nơi ta đi đến từ đó)
    while (!(cur.x == start.x && cur.y == start.y)) {
        result[cur.x][cur.y] = '*';     // Đánh dấu ô này là một phần của đường đi
        cur = parent[cur.x][cur.y];     // Lùi lại 1 bước về ô cha
    }
    // Sau khi vòng while kết thúc, "cur" đang ở vị trí Start
    // Gán ký tự đặc biệt cho điểm bắt đầu và điểm kết thúc
    result[start.x][start.y] = 'S';
    result[end.x][end.y] = 'E';

    // ===== In bản đồ kết quả =====
    cout << "Đường đi ngắn nhất (đánh dấu *):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << result[i][j] << " ";
        cout << endl;
    }

    return 0;
}
