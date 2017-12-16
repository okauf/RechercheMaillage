#include "Maillage.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    
	char nom[255] = "maillage1.msh";
	char* const pnom = nom;
    Maillage m(pnom);
	// setAdjacencyViaList(m);
    setAdjacencyViaMultiMap(m);
	
	char nom_M[255] = "maillage2.msh";
	char* const pnom_M = nom_M;
    Maillage M(pnom_M);
	// setAdjacencyViaList(M);
    setAdjacencyViaMultiMap(M);

   cout << "beginning promende" << endl;
   vector<Triangle> path;
   const T3<double> p = T3<double>(2,0,0);
   Triangle T = M.GetTriangles()[0];
   Triangle P = M.Promenade(T, p, path);
   T3<double>* sommets = M.GetSommets();
   cout << "point " << p << " is in the triangle with vertices " << endl << sommets[P[0]] << endl << sommets[P[1]] << endl << sommets[P[2]] << endl;
   exportGnuplot(M,path,&p,1);
	
	// int numbSommets_m = m.GetNumbSommets();
    // vector<Triangle> coveringTriangles;
	// for (int i=0; i < numbSommets_m; i++){
		// coveringTriangles.push_back(Triangle(0,0,0));
	// }
	// coveringTriangles = findSommets(m, M, coveringTriangles);    
    // exportGnuplot(M,coveringTriangles,m.GetSommets(),m.GetNumbSommets());
    
    return 0;
}