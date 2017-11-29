//
//  main.cpp
//  NetworkAndTriangles
//
//  Created by Arne Heimendahl on 23/10/2017.
//  Copyright © 2017 Arne Heimendahl. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;


class R3{
   
    friend std::ostream& operator <<(std::ostream& f, const R3 &v){   //friend in order to get private variables
        f   << v.x << "\t" << v.y << "\t" << v.z;
        return f;
    }
    friend std::istream& operator >>(std::istream& f,  R3 &v){
        char a;
        
        f >> a >> v.x >> a >> v.y >> a >> v.z >> a;
        return f;
    }
    
private:
    double x,y,z;
    
public:
    R3();
    R3(double a, double b, double c): x(a),y(b),z(c){}
    R3(const R3 &v){x = v.x; y = v.y; z = v.z;}
    double & operator[] (int i){
        assert(0 <= i && i < 3);
        switch (i) {
            case 0:
                return x;
                break;
            case 1:
                return y;
            case 2:
                return z;
            default:                                  //should never be reached because of assert
                return x;
        }
    }
    R3 & operator =(const R3 & v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    double dist(const R3&);
    bool operator==(const R3&);
    double operator,(const R3&);
    R3 operator +(const R3&);

    
};
R3:: R3(): x(0), y(0), z(0){}
double R3:: dist(const R3 &v){                       //by & the function accepts just the refence of the variable
    return  sqrt(x*v.x+y*v.y+z*v.z);
}
bool R3::operator==(const R3 &v){
    
    return (x == v.x && y == v.y && z == v.z);
}
double R3:: operator,(const R3 &v){
    return x*v.x+y*v.y+z*v.z;
}
R3 R3::operator +(const R3 &v){
    return R3(x+v.x, y+v.y, z+v.z);
}



class N3{
    friend std::ostream& operator <<(std::ostream& f, const N3 &v){   //friend in order to get private variables
        f  << v.x << "\t" << v.y << "\t" << v.z;
        return f;
    }
    friend std::istream& operator >>(std::istream& f,  N3 &v){
        char a;
        
        f >> a >> v.x >> a >> v.y >> a >> v.z >> a;
        return f;
    }
private:
    int x,y,z;
public:
    N3():x(0),y(0),z(0) {}
    N3(double a, double b, double c): x(a),y(b),z(c){}
    N3(const N3 &v){
        x = v.x; y = v.y; z = v.z;
    }
    int & operator[] (int i){
        assert(0 <= i && i < 3);
        switch (i) {
            case 0:
                return x;
                break;
            case 1:
                return y;
            case 2:
                return z;
            default:            //should never be reached because of assert
                return x;
        }
    }
    N3 & operator =(const N3 &v) {
        x = v.x; y = v.y; z = v.z;
        return *this;
    }
    
};






class Tri{
private:
    R3* t;
public:
    static int NbTri;  //Important: has to be public
    
    //default constructor
    Tri(){
        NbTri++;
        cout << "Number of generated triangles: " << NbTri << endl;
    }
    Tri(const R3 v1,const R3 v2,const R3 v3): t(new R3[3]){
        cout << "Generate triangle  with reference " << t << endl;
        t[0] = v1;
        t[1] = v2;
        t[2] = v3;
        NbTri++;
        cout << "Number of generated triangles: " << NbTri << endl;
    }
    
    //copy constructor
    Tri(const Tri & tt): t(new R3[3]){
        t[0] = tt[0];
        t[1] = tt[1];
        t[2] = tt[2];
        NbTri++;
        cout << "Number of generated triangles: " << NbTri << endl;
    };
    
    ~Tri() {
        NbTri--; 
        //cout << "Delete a Triangle with reference " << t <<"; total number of deleted Triangles is "<< NbTri <<endl;
        delete []t;                         // set brackets for array
    }
    
    R3 & operator [](int i){
        assert(i >= 0 && i <3);
        return t[i];
    }
    // in order to pass const objects for the copy constructor
    const R3 & operator[](int i) const{
        assert(i >= 0 && i <3);
        return t[i];
    }
    
    //copy assignment
    Tri operator= (const Tri &);

    friend std::ostream& operator <<(std::ostream& f, Tri &t){   //friend in order to get private variables
        f << t[0] << "\t \t"  << t[1] << endl << " \t " << t[2] << endl;
        return f;
    }
    
    
    
    
};
//make a deep copy
Tri Tri :: operator =(const Tri & tt){
    // delete the old pointer
    delete [] t;
    t = new R3[3];
    t[0] = tt[0];
    t[1] = tt[1];
    t[2] = tt[2];
    return *this;
}

//Declaration of the triangle counter
int Tri:: NbTri = 0;



//will return a searched number in a file
int findNumber(char* input, string searchedLine){
    int number;
    string line;
    
    fstream mshmaillage;
    mshmaillage.open(input);
    
    //save the first line in line
    getline(mshmaillage,line);
    
    while(line != searchedLine){
        getline(mshmaillage, line);
    }
    //line is found, next line is important
    getline(mshmaillage,line);
    number = stoi(line);
    return number;
}



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
//////////////////////////////////////////////////




Tri* LoadTri(char* const input, R3* tabNoeuds){
    
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
    
    
    Tri* tab = new Tri[numbTri];
    
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
        tab[i] = Tri(tabNoeuds[a-1], tabNoeuds[b-1], tabNoeuds[c-1]);
        cout <<  "Representation of the triangle: \n " << tab[i] << endl;
        i++;
        
    }
    mshmaillage.close();
    
    return tab;
}




//additional function
int  compareTwoWithThreePoints( R3 point1, R3 point2, Tri tri){
    
    if(point1 == tri[0]){
        if(point2 == tri[1] || point2 == tri[2])
            return true;
    }
    if(point1 == tri[1]){
        if(point2 == tri[0] || point2 == tri[2])
            return true;
    }
    if(point1 == tri[2]){
        if(point2 == tri[0] || point2 == tri[1])
            return true;
    }

    
    return false;
    
}


N3* adjacency(Tri* triTab, int TriNumber){
    
    //TriNumber has to be smaller than the size of TriTab
    //This has to guaranteed before
    //I will try to add a check
    
    cout << " Start adjacency " << endl;
    N3 * adjacents = new N3[TriNumber];
    
   
    
    
    //1: xyz coordiantes of the 1st and 2nd point
    for(int i = 0; i < TriNumber; i++){
            for(int j = 0; j < TriNumber; j++){
                bool same = compareTwoWithThreePoints(triTab[i][0],triTab[i][1] , triTab[j]);
                if(same == true && i != j){
                    adjacents[i][0] = j+1;
                 
                 }
                
            }
        
    }
    
    
    
    //2: xyz coordiantes of the 1st and 3rd point
    for(int i = 0; i < TriNumber; ++i){
        R3 point1 = triTab[i][0];
        R3 point2 = triTab[i][2];
        for(int j = 0; j < TriNumber; ++j){
            bool same = compareTwoWithThreePoints(point1, point2, triTab[j]);
            if(same == true && i != j){
                //increment each number by 1 in order to characterize the zero
                adjacents[i][1] = j+1;
              
            }
        }
    }
    
    //3: with xyz coordiantes of the 2nd and 3rd point
    for(int i = 0; i < TriNumber; ++i){
        R3 point1 = triTab[i][1];
        R3 point2 = triTab[i][2];
        for(int j = 0; j < TriNumber; ++j){
            bool same = compareTwoWithThreePoints(point1, point2, triTab[j]);
            if(same == true && i != j){
                adjacents[i][2] = j+1;
                adjacents[j][2] = i+1;
            }
        }
    }
    
    
    for(int i = 0; i < TriNumber; ++i){
        cout << adjacents[i][0] << " " << adjacents[i][1]<< " " << adjacents[i][2] << endl;
    }
    
    
    
    
    return adjacents;
    
}

void exportGnuplot(Tri* TriTab, int n){
    ofstream TriangleData;
    TriangleData.open("output.txt");
    TriangleData << "#Coordiantes" << endl;
    TriangleData << "#X \t Y \t Z" << endl;
    
    for(int i = 0; i < n; i++){
        TriangleData << "#Triangle " << i+1 << " (index " << i << ")" << endl;
        for(int j = 0; j < 3; j++){
            TriangleData << TriTab[i][j] << endl;
        }
        TriangleData << TriTab[i][0] << endl; //insert the last point again in order to connect the points
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


void exportGnuplotBoundary(Tri* TriTab, N3* adjacenceTab, int n){
    ofstream TriangleData;
    TriangleData.open("output.txt");
    TriangleData << "#Coordiantes" << endl;
    TriangleData << "#X \t Y \t Z" << endl;
    
    for(int i = 0; i < n; i++){
        //Check if this one is an element of the boundary
        //Triangle is just added if it contains a 0 in its entry of adjacency tab
        // 0 means that there is no adjacent edge
        
        if(adjacenceTab[i][0] == 0 || adjacenceTab[i][1] == 0 || adjacenceTab[i][2] == 0){
        
            TriangleData << "#Triangle " << i+1 << " (index " << i << ")" << endl;
            for(int j = 0; j < 3; j++){
                TriangleData << TriTab[i][j] << endl;
            }
            TriangleData << TriTab[i][0] << endl; //insert the last point again in order to connect the points
            TriangleData << endl;  //This creates blocks of points which will be connected by lines
        }
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


int main(int argc, const char * argv[]) {
    
    
    /*
    R3 v1(1,1,1);
    R3 v2;
    R3 v3(1,2,3);
    cout << v3 << endl;
    
    Tri tri1 = *new Tri(v1,v2,v3);
    cout << "Tri1" << tri1 << endl;
    Tri tri2 = tri1;
    cout << "Tri2 = Tri1" << tri2 << endl;
    cout << " 1st vertice of Tri2: " << tri2[0] << endl;
    Tri* TriTab = new Tri[3];
    */
    
    //R3* loadedNodes = LoadNodes("maillage1.msh");
    
    Tri* tabTri = LoadTri("maillage1.msh", LoadNodes("maillage1.msh"));
    int TriNumber = findNumber("maillage1.msh", "# Nombre de triangle");
    exportGnuplot(tabTri,TriNumber);
    N3* adjacenceTab = adjacency(tabTri, TriNumber);
    
    
    exportGnuplotBoundary(tabTri, adjacenceTab, TriNumber);
    
    
}
