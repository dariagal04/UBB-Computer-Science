#include <iostream>
#include <fstream>
using namespace std;

ifstream f("graf.txt");
int main() {
    int n, m;
    f >> n;
    f >> m;
    int a[100][100] = { 0 };
    for (int i = 1; i <= m; i++) 
    {
        a[i][i] = 1;
        int n1, n2;
        f >> n1 >> n2;
        a[n1][n2] = 1;
    }
    int tr[100][100] = { 0 };
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            tr[i][j] = a[i][j];
    cout << "Matricea tranzitiva:" << endl;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (tr[i][j] == 0 && tr[i][k] == 1 && tr[k][j] == 1)
                    tr[i][j] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << tr[i][j] << " ";
        cout << endl;
    }
    return 0;
}