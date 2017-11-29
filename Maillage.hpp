#include "T3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
using namespace std;

T3<double>* LoadNodes(char* const);
T3<int>* LoadTriangles(char* const);

class Maillage{
    
private:
    T3<double>* sommets;
    T3<int>* triangles;
public:
	Maillage(char* const input):sommets(LoadNodes(input)), triangles(LoadTriangles(input)){};
	
	T3<double>* GetSommets() {return sommets;}
	T3<int>* GetTriangles() {return triangles;}
};

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

