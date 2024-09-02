#include <iostream>
#include <fstream>
#include <climits>

#define MAX_NODURI 100    // Numărul maxim de noduri
#define MAX_MUCHII 1000   // Numărul maxim de muchii
#define INF INT_MAX       // Valoare infinită pentru costuri
#define MAX1 100
#define MAX2 1000 

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct Muchie {
    int u, v;
    int cost;
};

int gasesteNodNevizitat(int costMinim[], bool vizitat[], int n)
{
    int minCost = INF;
    int nodMin = -1;
    for (int i = 0; i < n; ++i)
    {
        if (!vizitat[i] && costMinim[i] < minCost)
        {
            minCost = costMinim[i];
            nodMin = i;
        }
    }
    return nodMin;
}

void prim(Muchie muchii[], int n, int m)
{
    int costMinim[MAX_NODURI];
    int tati[MAX_NODURI];
    bool vizitat[MAX_NODURI] = { false };

    for (int i = 0; i < n; i++)
    {
        costMinim[i] = INF;
        tati[i] = -1;
    }

    costMinim[0] = 0;
    for (int i = 0; i < n ; i++)
    {
        int u = gasesteNodNevizitat(costMinim, vizitat, n);
        vizitat[u] = true;
        for (int j = 0; j < m; j++)
        {
            if (muchii[j].u == u || muchii[j].v == u)
            {
                int v;
                if (muchii[j].u == u)
                    v = muchii[j].v;
                else
                    v = muchii[j].u;
                if (!vizitat[v] && muchii[j].cost < costMinim[v])
                {
                    costMinim[v] = muchii[j].cost;
                    tati[v] = u;
                }
            }
        }
    }
    int costTotal = 0;
    for (int i = 1; i < n; ++i)
    {
        fout << tati[i] << " - " << i << " : " << costMinim[i] << endl;
        costTotal += costMinim[i];
    }
    fout << "Costul total al arborelui partial de cost minim: " << costTotal << endl;
}

int main()
{
    int n, m;
    fin >> n >> m;
    Muchie muchii[MAX_MUCHII];
    for (int i = 0; i < m; i++)
        fin >> muchii[i].u >> muchii[i].v >> muchii[i].cost;
    prim(muchii, n, m);
    fin.close();
    fout.close();
    return 0;
}

/*

struct Muchie
{
    int u, v;
    int cost;
};

int gasesteCC(int u, int parinte[])
{
    if (u != parinte[u])
        parinte[u] = gasesteCC(parinte[u], parinte);
    return parinte[u];
}

void uneste(int u, int v, int parinte[], int rang[]) {
    int radacinaU = gasesteCC(u, parinte);
    int radacinaV = gasesteCC(v, parinte);
    if (radacinaU != radacinaV)
    {
        if (rang[radacinaU] < rang[radacinaV])
            parinte[radacinaU] = radacinaV;
        else if (rang[radacinaU] > rang[radacinaV])
            parinte[radacinaV] = radacinaU;
        else {
            parinte[radacinaV] = radacinaU;
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
    Muchie muchii[MAX2];
    for (int i = 0; i < m; i++)
        fin >> muchii[i].u >> muchii[i].v >> muchii[i].cost;
    sortare(muchii, m);
    int parinte[MAX1 + 1];
    int rang[MAX1 + 1] = { 0 };
    for (int i = 1; i <= n; i++)
        parinte[i] = i;
    Muchie arbore[MAX1];
    int costTotal = 0;
    int index = 0;
    for (int i = 0; i < m; i++) {
        if (gasesteCC(muchii[i].u, parinte) != gasesteCC(muchii[i].v, parinte))
        {
            uneste(muchii[i].u, muchii[i].v, parinte, rang);
            arbore[index++] = muchii[i];
            costTotal+= muchii[i].cost;
        }
    }
    fout << "Costul total al arborelui: " << costTotal << endl;
    fout << "Muchii:" << endl;
    for (int i = 0; i < index; i++)
        fout << arbore[i].u << " - " << arbore[i].v << " : " << arbore[i].cost << endl;
    fin.close();
    fout.close();
    return 0;
}
*/