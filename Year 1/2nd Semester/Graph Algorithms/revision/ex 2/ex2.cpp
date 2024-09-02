#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("in.txt");

int n, n1, n2, nr_muchii;
int mat_a[101][101], viz[101] = { 0 };

void dfs(int v) {
	viz[v] = 1;
	for (int i = 1; i <= n; i++) {
		if (mat_a[v][i] == 1 && viz[i] == 0)
			dfs(i);
	}

}
int main()
{
	fin >> n;
	while (fin >> n1 >> n2)
	{
		nr_muchii++;
		mat_a[n1][n2] = mat_a[n2][n1] = 1;
	}

	dfs(1);
	int ok3 = 0;
	for (int i = 1; i <= n; i++)
		if (viz[i] == 0) {
			ok3 = 1;

		}
	if (ok3 == 0)
		cout << "Graful e conex\n";
	else
	cout << "Graful nu e conex!\n";
}