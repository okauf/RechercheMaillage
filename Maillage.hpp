#include "R3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
using namespace std;


R3* LoadNodes(char* const);
R3* LoadTriangles(char* const);

class Maillage{
    

private:
    R3* sommets;
    R3* triangles;
public: 
    Maillage(char* const input):sommets(LoadNodes(input)), triangles(LoadTriangles(input)){};
};

R3* LoadNodes(char* const input){
    
    int numbSommets;
    string   line;
    
    
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
    numbSommets = stoi(line);
    
    
    
    
    //generating the tableau of R3
    R3 * tab = new R3[numbSommets];
    
    
    int i = 0;
    //ignoring the next line
    getline(mshmaillage,line);
    
    while(i < numbSommets){
        getline(mshmaillage,line);
        double a,b,c;
        stringstream linestream;
        linestream << line;
        linestream >> a >>  b >> c;
        
        //declaring the R3 objects
        tab[i] = R3(a,b,c);
        cout << tab[i] << endl;
        i++;
    }
    
    mshmaillage.close();
    
    
    return tab;
}

R3* LoadTriangles(char* const input){
    
    int numbTri;
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
    numbTri = stoi(line);
    cout << "Number of triangles: " << numbTri << endl;
    //generating the tableau of triangles
    
    
    R3* triangles = new R3[numbTri];
    
    //ignoring the next line
    getline(mshmaillage,line);
    
    int i = 0;
    while(i < numbTri){
        int a,b,c;     // save the positions of the points
        getline(mshmaillage,line);
        stringstream linestream;
        linestream << line;
        linestream >> a >>  b >> c;
        cout << "numbers of necessary points for the triangle were: " << a <<  " " <<  b << " " << c << endl;
        triangles[i] = R3(a,b,c);
        i++;
        
    }
    mshmaillage.close();
    
    return triangles;
}

