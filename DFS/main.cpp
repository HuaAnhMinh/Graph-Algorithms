#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// đọc đồ thị vô hướng bằng danh sách kề (sử dụng mảng)
// Nếu đồ thị có V đỉnh thì ta sẽ tạo mảng có V phần tử, mỗi phần tử i sẽ là một mảng khác
// chứa danh sách đỉnh kề với đỉnh i.
// ví dụ:
// 1 | 2 3 4: phần tử 1 là mảng với 3 phần tử { 2, 3, 4 } <=> { 1, 2 }, { 1, 3 }, { 1, 4 }
// 2 | 1 3
// 3 | 1 2
// 4 | 1
vector<vector<int>> ReadGraph() {
    int vertices, edges;
    cin >> vertices >> edges;

    vector<vector<int>> graph(vertices + 1);
    int u, v;
    for (int i = 0; i < edges; ++i) {
        cin >> u >> v;
		// do đồ thị là vô hướng nên mỗi khi nhập vào cạnh u -> v thì ta cũng phải nhập cạnh v -> u
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

// ta sẽ có các biến sau:
// visisted: đánh dấu các đỉnh đã thăm (đã duyệt qua), nếu đã thăm thì đánh dấu là true, chưa thăm sẽ là false.
// path: chứa đường đi đã duyệt theo dạng sau:
// 5 | 4: đỉnh 4 có đường đi đến đỉnh 5
// 4 | 2: đỉnh 2 có đường đi đến đỉnh 4
// 3 | 2
// 2 | 1
// stack traversal: duyệt.
// source: đỉnh bắt đầu duyệt.
vector<int> DFS_usingStack(int source, const vector<vector<int>> & graph) {
    vector<bool> visisted(graph.size(), false); // ban đầu khởi tạo visisted toàn bộ là false.
    vector<int> path(graph.size(), -1); // ban đầu khởi tạo path toàn bộ là -1.

    visisted[source] = true; // đánh dấu đỉnh bắt đầu duyệt là đã thăm.
    path[source] = -1;
    stack<int> traversal;
    traversal.push(source); // đưa đỉnh bắt đầu duyệt vào stack.

	// thực hiện vòng lặp khi stack vẫn còn chưa rỗng vì khi stack chưa rỗng
	// thì tức là vẫn có đỉnh chưa được duyệt.
    while (!traversal.empty()) {
		// lấy đỉnh trên đầu stack traversal.
        int u = traversal.top();
        traversal.pop();
		
		// duyệt qua tất cả những đỉnh kề với đỉnh u trên đầu stack traversal.
		// khi đọc đồ thị thì ta đã đọc theo danh sách kề nên phần tử graph[u] trong mảng
		// sẽ chứa một mảng khác là danh sách những đỉnh kề với đỉnh u nên ta thực hiện duyệt qua graph[u].
        for (auto & v : graph[u]) {
			// chỉ thực hiện nếu chưa đỉnh v chưa được duyệt qua bao giờ.
            if (!visisted[v]) {
                visisted[v] = true; // đánh dấu là đã thăm đỉnh v.
                traversal.push(v); // đưa v vào stack traversal.
                path[v] = u; // đánh dấu là có đường đi từ u tới v.
            }
        }
    }

    return path; // trả ra mảng chứa đường đi.
}

// in ra đường đi từ đỉnh source đến đỉnh destination.
void PrintPath_noRecursion(
    int source,
    int destination,
    const vector<int> & path
) {
	// nếu đỉnh bắt đầu cũng là đỉnh kết thúc thì in ra chính nó.
    if (source == destination) {
        cout << source << endl;
        return;
    }
	// nếu không có đường đi nào đến đỉnh destination thì xuất ra "No path".
    if (path[destination] == -1) {
        cout << "No path" << endl;
        return;
    }
	// dò ngược lại đường đi theo quy tắc sau:
	// path[a] = b thì tức là có đường từ b đến a.
	// path[b] = c thì có đường từ c đến b.
	// nếu c là source hoặc path[c] = -1 thì dừng.
	// vậy đường đi xuất ra là a <- b <- c <- NULL.
    while (destination != -1) {
        cout << destination << " <- ";
        destination = path[destination];
    }
    cout << "NULL" << endl;
}

// đổi với cách cài đặt bắt cách dùng đệ quy thì ta phải truyền mảng visited và path vào khi gọi hàm.
void DFS_usingRecursion(
    int source,
    const vector<vector<int>> & graph,
    vector<bool> & visited,
    vector<int> & path
) {
	// đánh dấu đỉnh source là đã thăm.
    visited[source] = true;
	
	// duyệt qua tất cả các đỉnh kề với source.
    for (auto & destination : graph[source]) {
		// nếu chưa thăm...
        if (!visited[destination]) {
            path[destination] = source; // đánh dấu là có đường đi từ source đến destination.
            DFS_usingRecursion(destination, graph, visited, path); // gọi đệ quy cho destination.
        }
    }
}

void PrintPath_withRecursion(
    int source,
    int destination,
    const vector<int> & path
) {
    if (source == destination) {
        cout << destination << endl;
    }
    else {
        if (path[destination] == -1) {
            cout << destination << " -> ";
        }
        else {
            PrintPath_withRecursion(destination, path[destination], path);
            cout << destination << " -> ";
        }
    }
}

int main() {
    vector<vector<int>> graph = ReadGraph();
    vector<int> path = DFS_usingStack(1, graph);
    PrintPath_noRecursion(1, 5, path);

    path.resize(graph.size(), -1);  
    vector<bool> visisted(graph.size(), false);
    DFS_usingRecursion(1, graph, visisted, path);
    PrintPath_withRecursion(1, 5, path);
    return EXIT_SUCCESS;
}