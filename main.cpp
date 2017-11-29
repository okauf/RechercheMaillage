#include "Maillage.hpp"
#include <iostream>
using namespace std;

int main(){
    
    Maillage m("maillage1.msh");
	T3<double>* Sommets = m.GetSommets();
	T3<int>* Triangles = m.GetTriangles();
	
	cout << " Number Sommets " << m.GetNumbSommets() << endl;
	for (int i = 0; i < m.GetNumbSommets(); i++){
		cout << Sommets[i] << endl;
	}
	
	cout << " Number Tri " << m.GetNumbTri() << endl;
	for (int i = 0; i < m.GetNumbTri(); i++){
		cout << Triangles[i] << endl;
	}
	
    return 0;
}