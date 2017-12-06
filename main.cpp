#include "Maillage.hpp"
#include "Visualization.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    
	char nom[255] = "maillage1.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	 T3<double>* Sommets = m.GetSommets();
    
     Triangle* triangles = m.GetTriangles();
    
    Triangle t1(1,2,3);
    Triangle t2(2,1,3);
    Triangle t3(1,2,4);
   
    
	//setAdjacencyViaList(m);
    setAdjacencyViaMultiMap(m);
    vector<Triangle> path;
//    Triangle neighbor1 = triangles[triangles[53].getNeighbor1()];
//    Triangle neighbor2 = triangles[triangles[53].getNeighbor2()];
//    Triangle neighbor3 = triangles[triangles[53].getNeighbor3()];
//    path.push_back(neighbor1);
//    path.push_back(neighbor2);
//    path.push_back(neighbor3);
//    exportGnuplot(m,path);
//
//    cout << "beginning promende" << endl;
//    
//    const T3<double> p = T3<double>(0,0,0);

//    Triangle T = m.GetTriangles()[5];
//    Triangle P = m.Promenade(T, p, path);
//    
//    cout << endl;
//    cout << P << endl;
    
    // Fehler in Wahl des Nachbardreiecks, Abbruchbedingung einfügen
	// cout << P << endl;
	
    
     //exportGnuplot(m,path);
    
    
    
    return 0;
}