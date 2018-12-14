#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100;
const int INF = INT32_MAX;

struct Edge {
    int source;       // u
    int destination;  // v
    int weight;       // w
};

vector<int> dist(MAX, INF);
vector<Edge> graph;
int vertices, edges;
int path[MAX];

bool BellmanFord(int s) {
    int u, v, w;
    dist[s] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < edges; ++j) {
            u = graph[j].source;
            v = graph[j].destination;
            w = graph[j].weight;
            
            if (dist[u] != INF && (dist[u] + w < dist[v])) {
                dist[v] = dist[u] + w;
                path[v] = u;
            }
        }
    }

    for (int j = 0; j < edges; ++j) {
        u = graph[j].source;
        v = graph[j].destination;
        w = graph[j].weight;

        if (dist[u] != INF && (dist[u] + w < dist[v])) {
            return false;
        }
    }

    return true;
}

int main() {
    return 0;
}
