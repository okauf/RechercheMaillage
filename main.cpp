#include "Maillage.hpp"
#include <iostream>
using namespace std;

int main(){
    
    Maillage m("maillage1.msh");
	T3<double>* Sommets = m.GetSommets();
	T3<int>* Triangles = m.GetTriangles();
	
	for (int i = 0; i < 30; i++){
		cout << Sommets[i] << endl;
	}
	
	for (int i = 0; i < 30; i++){
		cout << Triangles[i] << endl;
	}
	
    return 0;
}