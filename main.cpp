#include "Maillage.hpp"
#include "Visualization.hpp"
#include <iostream>
using namespace std;

int main(){
    
	char nom[255] = "maillage1.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	// T3<double>* Sommets = m.GetSommets();
	T3<int>* Triangles = m.GetTriangles();
	
//	cout << " Number Sommets " << m.GetNumbSommets() << endl;
//	for (int i = 0; i < m.GetNumbSommets(); i++){
//		cout << Sommets[i] << endl;
//	}
//	
//	cout << " Number Tri " << m.GetNumbTri() << endl;
//	for (int i = 0; i < m.GetNumbTri(); i++){
//		cout << Triangles[i] << endl;
//	}

	T3<int> T = T3<int>(1,18,5); // also in Maillage1: 1 18 16
	// T3<int> T = Triangles[5];
	T3<int> N = m.Adjacency(T,2);
	cout << T << endl;
	cout << N << endl;
	
	// const T3<double> p = T3<double>(0,0,0);
	// T3<int> P = m.Promenade(T, p); // Fehler in Wahl des Nachbardreiecks, Abbruchbedingung einfügen
	// cout << P << endl;
	
    // exportGnuplot(m);
    
    return 0;
}