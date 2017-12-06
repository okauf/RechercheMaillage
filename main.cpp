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

// T3<double> p1 = T3<double>(-1,0,0);
// T3<double> p2 = T3<double>(1,0,0);
// T3<double> p3 = T3<double>(0,1,0);
// double vol = p1.oriented_vol(p2,p3);
// cout << "oriented volume of p1-p2-p3 is " << vol << endl;
// vol = p1.oriented_vol(p3,p2);
// cout << "oriented volume of p1-p3-p2 is " << vol << endl;

//
   cout << "beginning promende" << endl;
   
   const T3<double> p = T3<double>(0,0,0);

   Triangle T = m.GetTriangles()[5];
   Triangle P = m.Promenade(T, p, path);
   
   cout << endl;
   cout << P << endl;
	
    
     //exportGnuplot(m,path);
    
    
    
    return 0;
}