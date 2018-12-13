#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

const int MAX = 100;
const int INF = INT32_MAX;

vector<vector<pair<int, int>>> graph;
vector<int> dist(MAX, INF);
vector<int> path(MAX);

struct option {
    bool operator()(const pair<int, int> & a, const pair<int, int> & b) const {
        return a.second > b.second;
    }
};

void Dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, option> priority;
    priority.push(make_pair(s, 0));
    dist[s] = 0;
    while (!priority.empty()) {
        pair<int, int> top = priority.top();
        priority.pop();
        int u = top.first;
        int w = top.second;
        for (int i = 0; i < graph[u].size(); ++i) {
            pair<int, int> neighbor = graph[u][i];
            if (w + neighbor.second < dist[neighbor.first]) {
                dist[neighbor.first] = w + neighbor.second;
                priority.push(pair<int, int>(neighbor.first, dist[neighbor.first]));
                path[neighbor.first] = u;
            }
        }
    }
}

int main() {
    dist = vector<int>(MAX, INF);
    graph = vector<vector<pair<int, int>>>(MAX + 5, vector<pair<int, int>>());
    return EXIT_SUCCESS;
}