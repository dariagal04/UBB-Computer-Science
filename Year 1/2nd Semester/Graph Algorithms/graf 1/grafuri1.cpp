#include <iostream>
#include <fstream>
#define nr 100
using namespace std;
ifstream f("date.txt");
int main()
{
    int v, e;
    f >> v >> e;
    int ma[nr][nr] = { 0 }, mi[nr][nr] = { 0 }, la[nr][nr] = { 0 };
    for (int i = 1; i <= e; i++)
    {
        int m, n;
        f >> m >> n;
        ma[n][m] = 1; ma[m][n] =1;
        mi[m][i] = mi[n][i] = 1;
    }
    cout << "matrice adiacenta:" << endl;
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= e; j++)
        {
            cout << ma[i][j] << " ";
            if (ma[i][j] == 1)
            {
                la[i][j] = la[j][i] = 1;
                la[i][0]++;
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << "liste de adiacenta:"<<endl;
    for (int i = 1; i <= v; i++)
    {
        cout << i << ":";
        for (int j = 0; j <= v; j++)
        {
            if (j == 0)
                cout << la[i][j] << " ";
            if (ma[i][j] ==1)
               cout << j<< " ";
 
        }
        cout << endl;
    }
    cout << endl;
    cout << "matrice incidenta:" << endl;
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= e; j++)
            cout << mi[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    f.close();
    return 0;

}
