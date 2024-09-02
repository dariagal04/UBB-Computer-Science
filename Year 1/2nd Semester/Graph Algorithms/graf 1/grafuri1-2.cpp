#define INF 9999
#include <iostream>
#include <fstream>

using namespace std;

ifstream f("in.txt");

const int m = 100;
int c[m], v[m];
/*
int nod_nevizitat(int v[m], int n) {
    for (int i = 1; i <= n; i++) {
        if (v[i] == 0) {
            return i;
        }
    }
    return 0;
}

void parcurgere_latime(int graph[m][m], int n) {
    int p = 1, u = 1;
    v[1] = 1;
    c[u] = 1;
    while (p <= u) {
        for (int i = 1; i <= n; i++) {
            if (graph[c[p]][i] == 1 && v[i] == 0) {
                u++;
                c[u] = i;
                v[i] = 1;
            }
        }
        p++;
    }
}
*/

void process() {
    int graph[m][m] = { 0 };
    int n, a, b;
    f >> n;
    while (f >> a >> b) {
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    int degree_sum[m] = { 0 };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            degree_sum[i] += graph[i][j];
        }
    }

    cout << "Noduri izolate: ";
    bool has_isolated = false;
    for (int i = 1; i <= n; i++) {
        if (degree_sum[i] == 0) {
            cout << i << " ";
            has_isolated = true;
        }
    }
    if (!has_isolated) {
        cout << "Nu are " << endl;
    }
    else {
        cout << endl;
    }

    bool regular = true;
    for (int i = 2; i <= n; i++) {
        if (degree_sum[i] != degree_sum[1]) {
            regular = false;
            break;
        }
    }
    cout << "graful ";
    if (!regular) {
        cout << "nu ";
    }
    cout << "e regular." << endl;

    int dist[m][m];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] != 1 && i != j) {
                dist[i][j] = INF;
            }
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "Mtricea distantelor: " << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
    int ok = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (dist[i][j] == INF && i != j)
                ok = 0;
    if (ok == 0)
        cout << "Graful nu este conex";
    else cout << "graful este conex";
                
    /*
    if (has_isolated) {
        cout << "Graful nu este conex." << endl;
    }
    else {
        parcurgere_latime(graph, n);
        if (nod_nevizitat(v, n) != 0) {
            cout << "Graful nu este conex." << endl;
        }
        else {
            cout << "Graful este conex." << endl;
        }
    }
    */
}

int main() {
    process();
    return 0;
}
