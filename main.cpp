#include "Maillage.hpp"
#include "Visualization.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    
	char nom[255] = "maillage1.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	// T3<double>* Sommets = m.GetSommets();
    //
    // Triangle* triangles = m.GetTriangles();
    
    // for(int i = 0; i < m.GetNumbTri(); i++){
        // cout << "Triangle " << triangles[i] << " has neighbors " << endl << triangles[i].getNeighbor1() << " " << triangles[i].getNeighbor2() << " " << triangles[i].getNeighbor3() << endl;

    // }
	
	//setAdjacencyViaList(m);
    setAdjacencyViaMultiMap(m);
	 const T3<double> p = T3<double>(0,0,0);
    vector<Triangle> path;
    Triangle T = m.GetTriangles()[rand()%m.GetNumbTri()];
    Triangle P = m.Promenade(T, p, path); // Fehler in Wahl des Nachbardreiecks, Abbruchbedingung einfügen
	// cout << P << endl;
	
     exportGnuplot(m,path);
    
    
    
    return 0;
}