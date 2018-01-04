#include "Maillage.hpp"
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main(){
    
   cout << "Choose from the following testing options" << endl;
   cout << "1: Find neighbors for a triangle" << endl;
   cout << "2: Find the covering triangle for a point of your choice" << endl;
   cout << "3: Find the covering triangles for all the points of another maillage" << endl;
   
   int option;
   cin >> option;
   switch(option) {
       
       case 1: {
           cout << "Choose a maillage file: " << endl << "1: maillage1.msh" << endl << "2: maillage2.msh" << endl << "3: maillage3.msh" << endl << "4: maillage4.msh" << endl <<  "5: maillage5.msh" << endl;
           int mOption;
           cin >> mOption;
           assert(mOption >= 0 && mOption < 6);
           string name;
           switch (mOption) {
               case 1: {name = "maillage1.msh";    break;}
               case 2: {name = "maillage2.msh";    break;}
               case 3: {name = "maillage3.msh";    break;}
               case 4: {name = "maillage4.msh";    break;}
               case 5: {name = "maillage5.msh";    break;}
           }
           
           Maillage m(name);
           int numbTri = m.GetNumbTri();
           cout << "How should the adjacency be initialized?" << endl << "1: Via List" << endl << "2: Via Map" << endl;
           int adjoption;
           cin >> adjoption;
           assert(adjoption == 1 || adjoption == 2);
           adjoption == 1? m.setAdjacencyViaList() : m.setAdjacencyViaMultiMap();
           cout << "Choose a number between " << 1 << " and " << numbTri << " in order to choose a triangle" << endl;
           int triangleIndex;
           cin >> triangleIndex;
           assert(triangleIndex >= 1 && triangleIndex <= numbTri);
           Triangle* triangles = m.GetTriangles();
           Triangle T = triangles[triangleIndex-1];
           vector<Triangle> neighbors;
           neighbors.push_back(T);
           if(T.getNeighbor1() != -1)
               neighbors.push_back(triangles[T.getNeighbor1()]);
           if(T.getNeighbor2() != -1)
               neighbors.push_back(triangles[T.getNeighbor2()]);
           if(T.getNeighbor3() != -1)
               neighbors.push_back(triangles[T.getNeighbor3()]);
           
           m.exportGnuplot(neighbors,nullptr,0);
           break;
       }
           
       case 2: {
           cout << "Choose a maillage file: " << endl << "1: maillage1.msh" << endl << "2: maillage2.msh" << endl << "3: maillage3.msh" << endl << "4: maillage4.msh" << endl <<  "5: maillage5.msh" << endl;
           int mOption;
           cin >> mOption;
           assert(mOption >= 0 && mOption < 6);
           string name;
           switch (mOption) {
               case 1: {name = "maillage1.msh";    break;}
               case 2: {name = "maillage2.msh";    break;}
               case 3: {name = "maillage3.msh";    break;}
               case 4: {name = "maillage4.msh";    break;}
               case 5: {name = "maillage5.msh";    break;}
           }
           
           Maillage m(name);
           int numbTri = m.GetNumbTri();
           cout << "Choose a point of the format <double> <double> " << endl;
           double x,y;
           cin >> x >> y;
           const T3<double> p(x,y,0);
           
           vector<Triangle> path;
           m.setAdjacencyViaList();
           cout << "Choose a number between " << 1 << " and " << numbTri << " in order to choose the starting triangle" << endl;
           int triangleIndex;
           cin >> triangleIndex;
           assert(triangleIndex >= 1 && triangleIndex <= numbTri);
           Triangle* triangles = m.GetTriangles();
           Triangle T = triangles[triangleIndex-1];
           
           T3<double>* vertices = m.GetVertices();
           cout << "The starting triangle is " << endl << vertices[T[0]-1] << endl  << vertices[T[1]-1] << endl  << vertices[T[2]-1] << endl;
           Triangle P = m.Promenade(T,p,path);
           cout << "The point " << p << " is in the triangle with vertices " << endl << vertices[P[0]-1] << endl << vertices[P[1]-1] << endl << vertices[P[2]-1] << endl;
           m.exportGnuplot(path,&p,1);
           break; 
       }
           
       case 3: {
           cout << "Choose two maillage files, the maillages become finer with increasing index. " << endl;
           cout << "Choose the maillage whose sommets should be covered by triangles of the finer maillage " << endl << "1: maillage1.msh" << endl << "2: maillage2.msh" << endl << "3: maillage3.msh" << endl << "4: maillage4.msh" << endl << "5: maillage5.msh" << endl;
           int mOption;
           cin >> mOption;
           assert(mOption >= 0 && mOption < 6);
           string name;
           switch (mOption) {
               case 1: {name = "maillage1.msh";    break;}
               case 2: {name = "maillage2.msh";    break;}
               case 3: {name = "maillage3.msh";    break;}
               case 4: {name = "maillage4.msh";    break;}
               case 5: {name = "maillage5.msh";    break;}
           }
           
           Maillage m(name);
           
           
           cout << "Chose the finer maillage file " << endl << "1: maillage1.msh" << endl << "2: maillage2.msh" << endl << "3: maillage3.msh" << endl << "4: maillage4.msh" << endl << "5: maillage5.msh" << endl;
           cin >> mOption;
           assert(mOption >= 0 && mOption < 6);
           switch (mOption) {
               case 1: {name = "maillage1.msh";    break;}
               case 2: {name = "maillage2.msh";    break;}
               case 3: {name = "maillage3.msh";    break;}
               case 4: {name = "maillage4.msh";    break;}
               case 5: {name = "maillage5.msh";    break;}
           }
           Maillage M(name);
           m.setAdjacencyViaMultiMap(); M.setAdjacencyViaList();
           
           vector<Triangle> coveringTriangles;
           for(int i = 0; i <m.GetNumbVertices();i++)
               coveringTriangles.push_back(Triangle(0,0,0));
           
           coveringTriangles = findVertices(m,M,coveringTriangles);
           
           M.exportGnuplot(coveringTriangles,m.GetVertices(),m.GetNumbVertices());
           
       }
   
   }

    return 0;
}