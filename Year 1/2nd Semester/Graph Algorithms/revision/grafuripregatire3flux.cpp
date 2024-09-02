#include <fstream>
#include <queue>
#include <cstring>
#include<iostream>

using namespace std;
ifstream f1("input.txt");
ofstream g1("output.txt");

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
                //actualizam tatal, marcam vizita si il adaugam in coada
                parent[i] = nod;
                viz[i] = 1;
                q.push(i);
            }
        }
    }
    return false;
}
void fluxMax()
{
    f1 >> n >> m;
    //citesc graful si initializez graful rezidual
    for (int i = 1; i <= m; i++)
    {
        f1 >> x >> y >> flow;
        graf[x][y] = flow;
        grafRezidual[x][y] = flow;
    }

    s = 0;
    t = n - 1;
    //vectroul de tati
    int parent[1005];
    while (bfs(grafRezidual, s, t, parent))
    {
        //am obtinut vectroul de tati din bfs
        //calculez acum capacitatea minima
        int cap = INT_MAX;
        for (int i = t; i != s; i = parent[i])
        {
            int tata = parent[i];
            if (grafRezidual[tata][i] < cap)
                cap = grafRezidual[tata][i];
        }

        //actualizez muchiile din graful rezidual si adaug la flux
        for (int i = t; i != s; i = parent[i])
        {
            int tata = parent[i];
            grafRezidual[tata][i] -= cap;
            grafRezidual[i][tata] += cap;
        }
        maxFlow += cap;
    }
    g1 << maxFlow;
}

int main() {
    fluxMax();
    return 0;
}