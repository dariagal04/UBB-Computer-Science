#include <iostream>
#include <fstream>
#include <climits>

#define MAX_NODURI 100    // Numărul maxim de noduri
#define MAX_MUCHII 1000   // Numărul maxim de muchii
#define INF INT_MAX       // Valoare infinită pentru costuri
#define MAXN 100
#define MAXM 1000 

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct Muchie
{
    int u, v;
    int cost;
};

int gasesteCONEX(int u, int parent[])
{
    if (u != parent[u])
        parent[u] = gasesteCONEX(parent[u], parent);
    return parent[u];
}

void uneste(int u, int v, int parent[], int rang[]) {
    int radacinaU = gasesteCONEX(u, parent);
    int radacinaV = gasesteCONEX(v, parent);
    if (radacinaU != radacinaV)
    {
        if (rang[radacinaU] < rang[radacinaV])
            parent[radacinaU] = radacinaV;
        else if (rang[radacinaU] > rang[radacinaV])
            parent[radacinaV] = radacinaU;
        else {
            parent[radacinaV] = radacinaU;
            rang[radacinaU]++;
        }
    }
}

void sortare(Muchie muchii[], int m)
{
    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++)
            if (muchii[i].cost > muchii[j].cost)
            {
                Muchie aux = muchii[i];
                muchii[i] = muchii[j];
                muchii[j] = aux;
            }
}

int main()
{
    int n, m;
    fin >> n >> m;
    Muchie muchii[MAXM];
    for (int i = 0; i < m; i++)
        fin >> muchii[i].u >> muchii[i].v >> muchii[i].cost;
    sortare(muchii, m);
    int parent[MAXN + 1];
    int rang[MAXN + 1] = { 0 };
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    Muchie arbore[MAXN];
    int costTotal = 0;
    int index = 0;
    for (int i = 0; i < m; i++) {
        if (gasesteCONEX(muchii[i].u, parent) != gasesteCONEX(muchii[i].v, parent))
        {
            uneste(muchii[i].u, muchii[i].v, parent, rang);
            arbore[index++] = muchii[i];
            costTotal += muchii[i].cost;
        }
    }
   fout << costTotal << endl;

    for (int i = 0; i < index; i++)
        fout << arbore[i].u << "  "<<arbore[i].v << endl;
    fin.close();
    fout.close();
    return 0;
}