#include<iostream>
#include<fstream>
#include<vector>
#include<string>
int const INF = 1 << 30;
using namespace std;



struct pondere {
	int sursa, destinatie, cost;
};

vector <int> dest; //drumurile de cost minim 
vector <pondere> point; //vector de pointeri
int n, m, nsursa; 
string fisierIntrare = "", fisierIesire = "";



void relax(int  sursa, int destinatie, int cost) {
	if (dest[sursa] != INF && dest[sursa] + cost < dest[destinatie])
		dest[destinatie] = dest[sursa] + cost;
}



bool BellmanFord(int nSursa) {
	//initializare
	for (int i = 0; i < n; i++) {
		if (i == nSursa)
			dest[i] = 0;
		else
			dest[i] = INF;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			relax(point[j].sursa, point[j].destinatie, point[j].cost);


	for (int i = 0; i < m; i++)
		if (dest[point[i].sursa] != INF && dest[point[i].sursa] + point[i].cost < dest[point[i].destinatie])
			return false;
	return true;

}



int main(int argc, char* argv[])
{

	int a, b, c;
	/*cout << "Dati numele fisierului de intrare: ";
	cin >> fisierIntrare;
	cout << "Dati numele fisierului de iesire: ";
	cin >> fisierIesire;*/
	ifstream fin(argv[1]);
	// ifstream fin(fisierIntrare);
	fin >> n >> m >> nsursa;
	dest.resize(n); point.resize(m);
	for (int i = 0; i < m; i++)
	{
		fin >> a >> b >> c;
		point[i].sursa = a;
		point[i].destinatie = b;
		point[i].cost = c;
	}
	fin.close();
	bool ok = BellmanFord(nsursa);
	ofstream fout(argv[2]);
	//ofstream fout(fisierIesire);
		if (ok == false)
			fout << "Circuitul are pondere negativa. " << endl;
		else {

			for (int i = 0; i < n; i++) {
				if (dest[i] != INF)
					fout << dest[i] << " ";
				else
					fout << "INF" << " ";

			}
			cout << endl;
		}
		fout.close();
	
	return 0;
}
