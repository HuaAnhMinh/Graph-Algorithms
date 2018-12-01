// với thuật toán prim, ta sẽ kết hợp dùng hàng đợi ưu tiên nhằm giảm độ phức tạp xuống O(E * LogV).
// đồ thị sẽ được lưu dưới dạng danh sách kề như sau:
// 1 | { 2, 100 }, { 4, 25 }: có đường đi từ đỉnh 1 -> 2 với trọng số là 100, có đường đi từ đỉnh 1 -> 4 với trọng số là 25.
// 2 | { 5, 90 }

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

const int INF = INT32_MAX;

// ta sẽ dùng vector<vector<pair<int, int>>> để lưu đồ thị.
// mỗi phần tử trong mảng nằm ở vị trí thứ i sẽ là một pair<int, int> chứa cặp số là đích đến của đỉnh i và
// trọng số của đường đi đó.

// vector<vector<pair<int, int>>>, mỗi phần tử sẽ là một mảng chứa các pair<int, int>
// 1 | { 2, 100 }, { 4, 25 }, mỗi pair<int, int> (như { 2, 100 }) sẽ là có đường đi từ 1 -> 2 với trọng số là 100.
// 2 | ... 
vector<vector<pair<int, int>>> ReadGraph() {
    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<pair<int, int>>> graph(vertices);
    int u, v, w;
    for (int i = 0; i < edges; ++i) {
        cin >> u >> v >> w;
        graph[u].push_back(pair<int, int>(v, w));
        graph[v].push_back(pair<int, int>(u, w));
    }
    return graph;
}

// struct option dùng cho việc so sánh trọng số giữa 2 đường đi.
// lúc nãy ta đã quy ước rằng mỗi pair<int, int> (như { v, w }) trong đỉnh u sẽ là đỉnh v kề với u
// và w là trọng số của đường đi.
// first trong pair<int, int> (v, w) là v, và second sẽ là w.
// như vậy để so sánh trọng số giữa 2 đường đi a và b thì ta sẽ so sánh 2 phần second của 2 đường đó.
struct option {
    bool operator()(const pair<int, int> & a, const pair<int, int> & b) const {
        return a.second > b.second;
    }
};

// source: đỉnh bắt đầu.
// path: đường đi tạo nên cây khung.
// dist: khoảng cách giữa các đường.
void Prim(
    int source,
    vector<int> & path,
    vector<int> & dist,
    const vector<vector<pair<int, int>>> & graph
) {
    dist.resize(graph.size(), INF); // khoảng cách ban đầu giữa các đỉnh sẽ mặc định là INF.
    path.resize(graph.size(), -1);
    vector<bool> visisted(path.size(), false); // mảng visisted chứa các đỉnh đã thăm.
	
    priority_queue<pair<int, int>, vector<pair<int, int>>, option> priority; // cấu trúc dữ liệu hàng đợi ưu tiên.
	// cấu trúc này sẽ so sánh sự ưu tiên giữa các đường đi bằng cách so sánh trọng số giữa chúng thông qua struct option
	// mà ta đã tạo.
    priority.push(pair<int, int>(source, 0));
    dist[source] = 0;
    
    while (!priority.empty()) {
        int u = priority.top().first; // lấy ra đỉnh có độ ưu tiên cao nhất (trọng số đường đi nhỏ nhất).
        priority.pop();
        visisted[u] = false; // đánh dấu đỉnh u đã thăm.

		// duyệt qua các đỉnh kề với u.
        for (auto & i : graph[u]) {
			// lấy ra 2 thành phần là đỉnh kề với u và trọng số đường đi đó.
            int v = i.first;
            int w = i.second;
			// nếu như độ dài đường đi ngắn nhất hiện tại (không cần biết là đường nào) đến v (dist[v]) 
			// mà lớn hơn trọng số w (đường từ u -> v)
			// thì cập nhật đường đi đến v sẽ là con đường u -> v.
            if (!visisted[v] && dist[v] > w) {
                dist[v] = w;
                priority.push(pair<int, int>(v, w));
                path[v] = u;
            }
        }
    }
}

void PrintMinimumSpanningTree(
    const vector<int> & path,
    const vector<int> & dist
) {
    int ans = 0;
    for (int i = 0; i < path.size(); ++i) {
        if (path[i] == -1) {
            continue;
        }
        ans += dist[i]; // tính tổng trọng số các đường đi.
        cout << path[i] << " - " << i << ": " << dist[i] << endl;
    }
    cout << "Weight of Minimum spanning tree: " << ans << endl;
}

int main() {
    vector<vector<pair<int, int>>> graph = ReadGraph();
    vector<int> path;
    vector<int> dist;
    Prim(1, path, dist, graph);
    PrintMinimumSpanningTree(path, dist);
    return EXIT_SUCCESS;
}