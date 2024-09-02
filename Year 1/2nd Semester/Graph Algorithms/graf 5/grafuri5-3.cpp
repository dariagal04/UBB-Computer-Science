#include <iostream>
#include <fstream>

using namespace std;

int j=0,n, m, x, y, a[101][101] = { 0 }, b[201] = { 0 };

void AlgoritmEuler(int k)
{
    for (int i = 0; i < n; i++)
        if (a[k][i])
        {
            a[k][i] = a[i][k] = 0;
            AlgoritmEuler(i);
        }   
    j++;
    b[j] = k;
}

int main(int argc, char **argv) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        a[x][y] = a[y][x] = 1;
    }
    AlgoritmEuler(0);
    for (int i = 1; i < j; i++) {
        fout << b[i] << " ";
    }
    fout << 0;
    return 0;
}