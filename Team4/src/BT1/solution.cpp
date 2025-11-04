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
    queue<Point> q;
    q.push(start);
    visited[start.x][start.y] = true;

    bool found = false;

    while (!q.empty()) {
        Point cur = q.front(); q.pop();

        // Nếu đến được điểm đích thì dừng lại
        if (cur.x == end.x && cur.y == end.y) {
            found = true;
            break;
        }

        // Duyệt 4 hướng
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (isValid(nx, ny, n, m, a, visited)) {
                visited[nx][ny] = true;
                parent[nx][ny] = cur; // Ghi nhớ đường đi
                q.push({nx, ny});
            }
        }
    }

    // ===== Nếu không tìm được đường =====
    if (!found) {
        cout << "Không có đường đi!" << endl;
        return 0;
    }

    // ===== Truy vết lại đường đi =====
    vector<vector<char>> result(n, vector<char>(m, ' '));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[i][j] = (a[i][j] == 0 ? '#' : '.'); // # = tường, . = ô trống

    // Đi ngược từ End về Start để đánh dấu '*'
    Point cur = end;
    while (!(cur.x == start.x && cur.y == start.y)) {
        result[cur.x][cur.y] = '*';
        cur = parent[cur.x][cur.y];
    }
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
