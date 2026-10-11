#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<vector<int>> bfs(int start_x, int start_y, const vector<vector<int>>& grid, int m, int n) {
    vector<vector<int>> dist(m, vector<int>(n, -1));
    queue<Point> q;
    
    dist[start_x][start_y] = 0;
    q.push(Point(start_x, start_y));
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
    
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> grid(m, vector<int>(n));
    Point start(-1, -1), home(-1, -1);
    vector<Point> umbrellas;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = Point(i, j);
            } else if (grid[i][j] == 3) {
                home = Point(i, j);
            } else if (grid[i][j] == 4) {
                umbrellas.push_back(Point(i, j));
            }
        }
    }
    
    if (start.x == -1 || home.x == -1) {
        cout << -1 << endl;
        return 0;
    }
    
    // BFS from start and from home
    vector<vector<int>> dist_from_start = bfs(start.x, start.y, grid, m, n);
    vector<vector<int>> dist_from_home = bfs(home.x, home.y, grid, m, n);
    
    int min_path = numeric_limits<int>::max();
    
    // Check paths through each umbrella shop
    for (const Point& umbrella : umbrellas) {
        int dist_start_umbrella = dist_from_start[umbrella.x][umbrella.y];
        int dist_umbrella_home = dist_from_home[umbrella.x][umbrella.y];
        
        if (dist_start_umbrella != -1 && dist_umbrella_home != -1) {
            int total_dist = dist_start_umbrella + dist_umbrella_home;
            min_path = min(min_path, total_dist);
        }
    }
    
    // If there are no umbrella shops, we can take direct path
    if (umbrellas.empty()) {
        int dist_start_home = dist_from_start[home.x][home.y];
        if (dist_start_home != -1) {
            min_path = dist_start_home;
        }
    }
    
    if (min_path == numeric_limits<int>::max()) {
        cout << -1 << endl;
    } else {
        cout << min_path << endl;
    }
    
    return 0;
}