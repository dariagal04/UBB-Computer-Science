#include <iostream>
#include <fstream>

using namespace std;

int p[101], rez[101], n, v, k;

void elimina_frunza(int i)
{
    p[i] = -2;
    n--;
}

int frunza_minima()
{
    int i, j, is_parent;
    for (i = 0; i < v; i++)
        if (p[i] != -2)
        {
            is_parent = 0;
            for (j = 0; j < v; j++)
                if (i == p[j])
                    is_parent = 1;
            if (is_parent == 0)
                return i;
        }
}

void codare_Prufer()
{
    int i;
    while (n > 1)
    {
        i = frunza_minima();
        rez[k++] = p[i];
        elimina_frunza(i);
    }
}

int main(int argc, char * argv[])
{
    int i, j;
    ifstream f(argv[1]);
    ofstream fout(argv[2]);

    f >> n;
    for (i = 0; i < n; i++)
        f >> p[i];
    v = n;
    codare_Prufer();
    fout << k << endl;
    for (i = 0; i < k; i++)
        fout << rez[i] << " ";
    return 0;
}