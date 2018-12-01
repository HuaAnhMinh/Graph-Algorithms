#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> ReadGraph() {
    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<int>> graph(vertices + 1);
    int u, v;
    for (int i = 0; i < edges; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

// tương tự như DFS nhưng dùng stack thay thế.
vector<int> BFS(int source, const vector<vector<int>> & graph) {
    vector<bool> visited(graph.size(), false);
    vector<int> path(graph.size(), -1);
    queue<int> traversal;

    visited[source] = true;
    traversal.push(source);
    
    while (!traversal.empty()) {
        int u = traversal.front();
        traversal.pop();

        for (auto & v : graph[u]) {
            if (!visited[v]) {
                traversal.push(v);
                visited[v] = true;
                path[v] = u;
            }
        }
    }
    return path;
}

int main() {
    vector<vector<int>> graph = ReadGraph();
    vector<int> path = BFS(1, graph);
    return EXIT_SUCCESS;
}