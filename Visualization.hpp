#include "Maillage.hpp"
//#include "T3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>


void exportGnuplot(Maillage m){
    ofstream TriangleData;
    TriangleData.open("output.txt");
    TriangleData << "#Coordiantes" << endl;
    TriangleData << "#X \t Y \t Z" << endl;
    
    T3<int>* triangles = m.GetTriangles();
    T3<double>* sommets = m.GetSommets();
    
    for(int i = 0; i < m.GetNumbTri(); i++){
        TriangleData << "#Triangle " << i+1 << endl;
        for(int j = 0; j < 3; j++){
            TriangleData << sommets[triangles[i][j]] << " ";
        }
        TriangleData << sommets[triangles[i][0]] << endl;
        //insert the last point again in order to connect the points
        TriangleData << endl;  //This creates blocks of points which will be connected by lines
    }
    TriangleData.close();
    
    //Script for Gnuplot
    ofstream GnuCom;
    GnuCom.open("GnuExe.txt");
    
    
    GnuCom << "plot 'output.txt' with lines " << endl;
    // In order to keep the file open
    GnuCom << "pause -1 'Hit any key to continue' " << endl;
    GnuCom.close();
    
    system("gnuplot GnuExe.txt ");
    
}
