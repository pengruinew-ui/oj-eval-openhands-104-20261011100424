#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

vector<vector<int> > bfs(int start_x, int start_y, const vector<vector<int> >& grid, int m, int n) {
    vector<vector<int> > dist(m, vector<int>(n, -1));
    queue<pair<int, int> > q;
    
    dist[start_x][start_y] = 0;
    q.push(make_pair(start_x, start_y));
    
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = curr.first + dx[i];
            int ny = curr.second + dy[i];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                grid[nx][ny] != 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[curr.first][curr.second] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    
    return dist;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    vector<vector<int> > grid(m, vector<int>(n));
    int start_x = -1, start_y = -1, home_x = -1, home_y = -1;
    vector<pair<int, int> > umbrellas;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 2) {
                start_x = i; start_y = j;
            } else if (grid[i][j] == 3) {
                home_x = i; home_y = j;
            } else if (grid[i][j] == 4) {
                umbrellas.push_back(make_pair(i, j));
            }
        }
    }
    
    if (start_x == -1 || home_x == -1) {
        printf("-1\n");
        return 0;
    }
    
    // BFS from start and from home
    vector<vector<int> > dist_from_start = bfs(start_x, start_y, grid, m, n);
    vector<vector<int> > dist_from_home = bfs(home_x, home_y, grid, m, n);
    
    int min_path = 2000000000; // Large number as infinity
    
    // Check paths through each umbrella shop
    for (int i = 0; i < umbrellas.size(); i++) {
        int ux = umbrellas[i].first;
        int uy = umbrellas[i].second;
        int dist_start_umbrella = dist_from_start[ux][uy];
        int dist_umbrella_home = dist_from_home[ux][uy];
        
        if (dist_start_umbrella != -1 && dist_umbrella_home != -1) {
            int total_dist = dist_start_umbrella + dist_umbrella_home;
            min_path = min(min_path, total_dist);
        }
    }
    
    // If there are no umbrella shops, we can take direct path
    if (umbrellas.empty()) {
        int dist_start_home = dist_from_start[home_x][home_y];
        if (dist_start_home != -1) {
            min_path = dist_start_home;
        }
    }
    
    if (min_path == 2000000000) {
        printf("-1\n");
    } else {
        printf("%d\n", min_path);
    }
    
    return 0;
}