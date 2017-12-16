#include "Maillage.hpp"
#include "Visualization.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    
	char nom[255] = "maillage2.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	
	char nom_M[255] = "maillage1.msh";
	char* const pnom_M = nom_M;
    Maillage M(pnom_M);
	
	 // T3<double>* sommets = m.GetSommets();
    
     // Triangle* triangles = m.GetTriangles();
    
//    Triangle t1(1,2,3);
//    Triangle t2(2,1,3);
//    Triangle t3(1,2,4);
   
    
	
	
	// Nachbarschaften ausgeben
	// for (int i = 0; i < m.GetNumbTri(); i ++ ){
		// cout << "Triangle " << triangles[i] << " has neighbors :" << endl;
		// cout << triangles[ triangles[i].getNeighbor1()] << endl;
		// cout << triangles[ triangles[i].getNeighbor2()] << endl;
		// cout << triangles[ triangles[i].getNeighbor3()] << endl;
		// cout << endl;
	// }
    
    
 

//    Triangle neighbor1 = triangles[triangles[53].getNeighbor1()];
//    Triangle neighbor2 = triangles[triangles[53].getNeighbor2()];
//    Triangle neighbor3 = triangles[triangles[53].getNeighbor3()];
//    path.push_back(neighbor1);
//    path.push_back(neighbor2);
//    path.push_back(neighbor3);
//    exportGnuplot(m,path);

//T3<double> p1 = T3<double>(-1,0,0);
//T3<double> p2 = T3<double>(1,0,0);
//T3<double> p3 = T3<double>(0,1,0);
    
//    Triangle t1 = triangles[20];
//    Triangle t2 = triangles[22];
//    
//    path.push_back(t1);
//    path.push_back(t2);
//    
//    
//    T3<double> c1 = sommets[t1[0]-1], c2 = sommets[t1[1]-1], c3 = sommets[t1[2]-1];
//    cout << "1st triangle " << c1 << endl << c2 << endl << c3 << endl;
//    
//    T3<double> d1 = sommets[t2[0]-1], d2 = sommets[t2[1]-1], d3 = sommets[t2[2]-1];
//    cout << "2nd triangle " << d1 << endl << d2 << endl << d3 << endl;
//    cout << d2.wheretogo(c1,c3,c2) << endl;
//    
    
// double vol = p1.oriented_vol(p2,p3);
// cout << "oriented volume of p1-p2-p3 is " << vol << endl;
// vol = p1.oriented_vol(p3,p2);
// cout << "oriented volume of p1-p3-p2 is " << vol << endl;

 // T3<double> p = T3<double>(0,-1,0);

 // bool x = p.wheretogo(p1,p2,p3);
 // cout << x << endl;


//    cout << "beginning promende" << endl;
//    vector<Triangle> path;
//    setAdjacencyViaList(M);
//    setAdjacencyViaMultiMap(M);
//
//    const T3<double> p = T3<double>(0,0,0);
//    //const T3<double> p = T3<double>(-0.185,0.0718,0);
//
//    Triangle T = M.GetTriangles()[0];
//    Triangle P = M.Promenade(T, p, path);
//    T3<double>* sommets = M.GetSommets();
//	
//     cout << "point " << p << " is in the triangle with vertices " << endl << sommets[P[0]] << endl << sommets[P[1]] << endl << sommets[P[2]] << endl;
//	
    
//     exportGnuplot(M,path,&p,1);
	
	int numbSommets_m = m.GetNumbSommets();
    vector<Triangle> coveringTriangles;
	for (int i=0; i < numbSommets_m; i++){
		coveringTriangles.push_back(Triangle(0,0,0));
	}
	coveringTriangles = findSommets(m, M, coveringTriangles);
    vector <Triangle> empty;
    T3<double>* p;
    
    exportGnuplot(M,coveringTriangles,m.GetSommets(),m.GetNumbSommets());
    
    
    
    
    
    return 0;
}