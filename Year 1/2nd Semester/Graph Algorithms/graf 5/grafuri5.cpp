#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int, int>>> residualGraph;
vector<bool> visited;
vector<int> parent;
int n, e, source, sink, pathFlow, maxFlow = 0;

void BFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (auto& edge : residualGraph[current]) {
            int neighbor = edge.first;
            int capacity = edge.second;
            if (!visited[neighbor] && capacity > 0) {
                parent[neighbor] = current;
                visited[neighbor] = true;
                q.push(neighbor);
                if (neighbor == sink) return;
            }
        }
    }
}

void findPathFlow(int node) {
    if (parent[node] != -1) {
        int prev = parent[node];
        for (auto& edge : residualGraph[prev]) {
            if (edge.first == node) {
                pathFlow = min(pathFlow, edge.second);
                findPathFlow(prev);
                return;
            }
        }
    }
}

void updateResidualGraph(int node) {
    if (parent[node] != -1) {
        int prev = parent[node];
        for (auto& edge : residualGraph[prev]) {
            if (edge.first == node) {
                edge.second -= pathFlow;
                if (edge.second == 0) {
                    edge = residualGraph[prev].back();
                    residualGraph[prev].pop_back();
                }
                break;
            }
        }
        bool reverseEdgeFound = false;
        for (auto& edge : residualGraph[node]) {
            if (edge.first == prev) {
                edge.second += pathFlow;
                reverseEdgeFound = true;
                break;
            }
        }
        if (!reverseEdgeFound) {
            residualGraph[node].emplace_back(prev, pathFlow);
        }
        updateResidualGraph(prev);
    }
}

int main(int argc, char** argv) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n >> e;
    residualGraph.resize(n);
    visited.resize(n);
    parent.resize(n);

    for (int i = 0; i < e; i++) {
        int x, y, c;
        fin >> x >> y >> c;
        residualGraph[x].emplace_back(y, c);
    }

    source = 0;
    sink = n - 1;

    while (true) {
        fill(visited.begin(), visited.end(), false);
        fill(parent.begin(), parent.end(), -1);
        BFS(source);
        if (!visited[sink]) break;

        pathFlow = INT_MAX;
        findPathFlow(sink);
        maxFlow += pathFlow;
        updateResidualGraph(sink);
    }

    fout << maxFlow;
    return 0;
}
