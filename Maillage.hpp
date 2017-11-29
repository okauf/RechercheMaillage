#include "T3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
using namespace std;

class Maillage{
    
private:
    T3<double>* sommets;
    T3<int>* triangles;
	int numbSommets, numbTri;
public:
	Maillage(char* const input):sommets(LoadNodes(input)), triangles(LoadTriangles(input)){};
	
	T3<double>* GetSommets() {return sommets;}
	T3<int>* GetTriangles() {return triangles;}
	int GetNumbSommets() {return numbSommets;}
	int GetNumbTri() {return numbTri;}
	
	void SetNumbSommets(int n) { numbSommets = n; }
	void SetNumbTri(int n) { numbTri = n; }

T3<double>* LoadNodes(char* const input){
    
    string line;
    
    fstream mshmaillage;
    mshmaillage.open(input);
    
    //save the first line in line
    getline(mshmaillage,line);
    //searching for the number
    while(line != "# Nombre de sommets"){
        getline(mshmaillage,line);
    }
    getline(mshmaillage,line);
    // saving the number of sommets
    int numbSommets = stoi(line);
	SetNumbSommets(numbSommets);
    
    //generating the tableau of R3
    T3<double> * tab = new T3<double>[numbSommets];
    
    //ignoring the next line
    getline(mshmaillage,line);
    
	int i = 0;
    while(i < numbSommets){
        getline(mshmaillage,line);
        double a,b,c;
        stringstream linestream;
        linestream << line;
        linestream >> a >>  b >> c;
        
        //declaring the T3 objects
        tab[i] = T3<double>(a,b,c);
        i++;
    }
    
    mshmaillage.close();
    return tab;
}

T3<int>* LoadTriangles(char* const input){
	
    string line;
    
    fstream mshmaillage;
    mshmaillage.open(input);
    
    //save the first line in line
    getline(mshmaillage,line);
    
    //searching for the number
    while(line != "# Nombre de triangle"){
        getline(mshmaillage,line);
    }
    getline(mshmaillage,line);
    
    // saving the number of triangles
    int numbTri = stoi(line);
	SetNumbTri(numbTri);
    
    //generating the tableau of triangles
    T3<int>* triangles = new T3<int>[numbTri];
    
    //ignoring the nextline
    getline(mshmaillage,line);
    
    int i = 0;
    while(i < numbTri){
        int a,b,c;     // save the positions of the points
        getline(mshmaillage,line);
        stringstream linestream;
        linestream << line;
        linestream >> a >>  b >> c;
        triangles[i] = T3<int>(a,b,c);
        i++;
    }
    mshmaillage.close();
    
    return triangles;
}

};

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
            TriangleData << sommets[triangles[i][j]] << endl;
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
	
	// plot "Output.txt" with lines
    
}


