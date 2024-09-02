#include<iostream>
#include<fstream>
using namespace std;

ifstream fin("in.txt");
int n, n1, n2, nr_muchii;
int mat_a[101][101], mat_i[101][101], l[101][101];

int main()
{
	fin >> n; 
	while (fin >> n1 >> n2)
	{
		nr_muchii++;
		mat_a[n1][n2] = mat_a[n2][n1] = 1;
	}
	cout << "Matricea de adiacenta:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << mat_a[i][j] << " ";
		cout << '\n';
	}
	cout << "Lista de adiacenta:\n";
	for (int i = 1; i <= n; i++)
	{
		int nrn = 0;
		for (int j = 1; j <= n; j++)
			if (mat_a[i][j] != 0)
			{
				nrn++;
				l[i][nrn] = j;
			}
		nrn++;
		l[i][nrn] = -1;
	}
	for (int i = 1; i <= n; i++)
	{
		cout << i << " : ";
		int j = 1;
		while (l[i][j] != -1)
		{
			cout << l[i][j] << " ";
			j++;
		}
		cout << '\n';
	}

	int mat_aa[100][100] = { 0 };
	cout << "Matricea de adiacenta iar:\n";
	for (int i = 1; i <= n; i++)
	{
		int j = 1;
		while (l[i][j] != -1)
		{
			mat_aa[i][l[i][j]] = 1;
			j++;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << mat_aa[i][j] << " ";
		cout << '\n';
	}
	int k = 0;
	mat_i[100][100] = { 0 };
	cout << "Matricea de incidenta:\n";
	for (int i = 1; i <=n; ++i) {
		for (int j = i + 1; j <=n; ++j) {
			if (mat_a[i][j] == 1) {
				k++;
				mat_i[i][k] = 1;
				mat_i[j][k] = 1;

			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= nr_muchii; j++)
			cout << mat_i[i][j] << " ";
		cout << '\n';
	}
	int mat_aaa[100][100] = { 0 };
	cout << "Matricea de adiacenta iar:\n";;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= nr_muchii; j++)
			if (mat_i[i][j] == 1) {
				for (int k = i + 1; k <= n; k++)
					if (mat_i[k][j] == 1 && i != k) {
						mat_aaa[i][k] = 1;
						mat_aaa[k][i] = 1;
					}
			}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << mat_aaa[i][j] << " ";
		cout << '\n';
	}

}