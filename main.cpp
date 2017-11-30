#include "Maillage.hpp"
#include "Visualization.hpp"
#include <iostream>
using namespace std;

int main(){
    
	char nom[255] = "maillage1.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	// T3<double>* Sommets = m.GetSommets();
    setAdjacencyViaMultiMap(m);
    
        
	
//	cout << " Number Sommets " << m.GetNumbSommets() << endl;
//	for (int i = 0; i < m.GetNumbSommets(); i++){
//		cout << Sommets[i] << endl;
//	}
//	
//	cout << " Number Tri " << m.GetNumbTri() << endl;
//	for (int i = 0; i < m.GetNumbTri(); i++){
//		cout << Triangles[i] << endl;
//	}

//	Triangle T = Triangle(1,18,5); // also in Maillage1: 1 18 16
//	// Triangle T = Triangles[5];
//	Triangle N = m.Adjacency(T,2);
//	cout << T << endl;
//	cout << N << endl;
	
	// const T3<double> p = T3<double>(0,0,0);
	// Triangle P = m.Promenade(T, p); // Fehler in Wahl des Nachbardreiecks, Abbruchbedingung einfügen
	// cout << P << endl;
	
  //   exportGnuplot(m);
    
    
    
    return 0;
}