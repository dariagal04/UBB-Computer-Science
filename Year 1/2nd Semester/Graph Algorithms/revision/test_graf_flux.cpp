#include <fstream>
#include <queue>
#include <cstring>
#include<iostream>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int s, t, n, m, x, y, graf[1005][1005], grafRezidual[1005][1005], flow, maxFlow;
bool bfs(int grafRez[1005][1005], int sursa, int destinatie, int parent[])
{
    int viz[1005];
    queue<int>q;

    q.push(sursa);
    memset(viz, 0, sizeof(viz));
    parent[sursa] = -1;
    viz[sursa] = 1;
    while (!q.empty())
    {
        int nod = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (grafRez[nod][i] != 0 && !viz[i])
            {
                if (i == destinatie)
                {
                    parent[destinatie] = nod;
                    return true;
                }

                parent[i] = nod;
                viz[i] = 1;
                q.push(i);
            }
        }
    }
    return false;
}
void fluxMaxFord()
{
    fin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        fin >> x >> y >> flow;
        graf[x][y] = flow;
        grafRezidual[x][y] = flow;
    }

    s = 0;
    t = n - 1;
    //vectroul de tati
    int parent[1005];
    while (bfs(grafRezidual, s, t, parent))
    {
        //capacitatea minima
        int cap = INT_MAX;
        for (int i = t; i != s; i = parent[i])
        {
            int tata = parent[i];
            if (grafRezidual[tata][i] < cap)
                cap = grafRezidual[tata][i];
        }

        //muchiile din grafRezidual -> adaug la flux
        for (int i = t; i != s; i = parent[i])
        {
            int tata = parent[i];
            grafRezidual[tata][i] = grafRezidual[tata][i] - cap;
            grafRezidual[i][tata] = grafRezidual[tata][i] + cap;
        }
        maxFlow = maxFlow + cap;
    }
    fout << maxFlow;
}

int main() {
    fluxMaxFord();
    return 0;
}