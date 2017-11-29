#include "Maillage.hpp"
#include "Visualization.hpp"
#include <iostream>
using namespace std;

int main(){
    
	char nom[255] = "maillage1.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	// T3<double>* Sommets = m.GetSommets();
	// T3<int>* Triangles = m.GetTriangles();
	
//	cout << " Number Sommets " << m.GetNumbSommets() << endl;
//	for (int i = 0; i < m.GetNumbSommets(); i++){
//		cout << Sommets[i] << endl;
//	}
//	
//	cout << " Number Tri " << m.GetNumbTri() << endl;
//	for (int i = 0; i < m.GetNumbTri(); i++){
//		cout << Triangles[i] << endl;
//	}
	
    exportGnuplot(m);
    
    return 0;
}