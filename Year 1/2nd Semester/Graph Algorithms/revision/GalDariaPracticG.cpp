#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("in.txt");
int n, nr_muchii;
int mat_a[101][101], mat_i[101][101];
int main()
{
	fin >> n >> nr_muchii; // n e numarul de noduri si nr_muchii e numarul de muchii
	cout << "Matricea de adiacenta:\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			fin >> mat_a[i][j];
			cout << mat_a[i][j]<<" ";
		}
		cout << '\n';
	}

	int k = 0;
	mat_i[100][100] = { 0 };
	cout << "Matricea de incidenta:\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
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

}

