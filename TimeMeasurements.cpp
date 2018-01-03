#include "Maillage.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <time.h>
#include <math.h>
using namespace std;
using namespace std::chrono;

void defineTriandPoints(Maillage & m, string input, int numbExp);
void runPromenade(Maillage & m, string input, string name1, string name2);
void exportGnuplot(string file1, string file2,bool runTime);


int main(){
	
    string name = "maillage5.msh";
    Maillage m(name);
    m.setAdjacencyViaList();
    int numbExp = 2000;

    // file stores starting triangles and points to cover
    string input = "randomData.txt";
    // do not execute defineTriandPoints in order to compare the results of min_neg and random_neg
    //defineTriandPoints(m, input, numbExp);
    
    //runPromenade(m,"RandomData.txt", "MinMeasRunTime.txt", "MinMeasPathlength.txt");
    exportGnuplot("MinMeasRunTime2000.txt","RandMeasRunTime2000.txt",true);
    
    
   
	
}
double trianglePointDistance(Maillage & m,const int triIndex, T3<double> &p){
    //distance is defined to be the distance of the centroid of the triangle and the point
    Triangle t = m.GetTriangles()[triIndex-1];
    T3<double>* vertices = m.GetVertices();
    T3<double> x = vertices[t[0]-1], y = vertices[t[1]-1], z = vertices[t[2]-1];
    T3<double> s = (x+y+z)*0.3333333;
    //cout << "The starting triangle is " << endl << x << endl << y << endl << z << endl;
    return s.dist(p);
    
}

void defineTriandPoints(Maillage & m, string input,const int numbExp){
	
	ofstream randomData;
	randomData.open(input);
	
	// random starting triangles
	int numbTri = m.GetNumbTri();
	int randomTriIndex;
	
	// define random points in the unit disk via radius and angle
	double radius, angle;
	srand(time(NULL));
	for (int i = 0; i < numbExp; i++){
		int randomTriIndex = rand()%numbTri+1;
        
        //index of the random starting triangle
		randomData << randomTriIndex << endl;
	
		radius = (rand() % 10000) / 10000.0;
		angle = 2 * M_PI * (rand() % 10000) / 10000.0;
        
        //data of the point in the unit disk
        T3<double> p(radius*cos(angle),radius*sin(angle),0);
        randomData << p << endl;
        
        //calculating the distance
        randomData << trianglePointDistance(m,randomTriIndex,p) << endl;
        
	}
	randomData.close();
};

void runPromenade(Maillage & m, string input, string name1, string name2){
	
	fstream randomData;
	randomData.open(input);
	
	Triangle* triangles = m.GetTriangles();
	vector<Triangle> path;
	
    
	Triangle StartTri;
	T3<double> p;
	string line;
	int idx;
	double a, b, c;
	duration<double> durationIns;
	Triangle P;
    
    //for directly writing the data in a txt file
    ofstream searchData1, searchData2;
    searchData1.open(name1);
    searchData2.open(name2);
    
	

    while(getline(randomData,line)){
        //path is rewritten in each loop
		path.clear();
		
        //for completion, data of triangle index in the result txt file
        searchData1 << "#"<< line << endl;
        searchData2 << "#"<< line << endl;
        
		// reading list position of the starting triangle
		idx = stoi(line);
        
		StartTri = triangles[idx-1];
		
		// reading point to cover
		getline(randomData,line);
        
        //for completion adding the point to the result txt file
        searchData1 << "#" << line << endl;
        searchData2 << "#" << line << endl;
        
		stringstream linestream;
		linestream << line;
		linestream >> a >> b >> c;
		p = T3<double>(a,b,c);
        
        
		
		// time measurement and path length for method promenade
		auto t1 = high_resolution_clock::now();
		P = m.Promenade(StartTri,p,path);
		auto t2 = high_resolution_clock::now();
		durationIns = t2-t1;
        
        //getting the distance
        getline(randomData,line);
        
        //writing the data in the file
        searchData1 << line << " "  << durationIns.count() << endl << endl;
        searchData2 << line << " " <<  path.size() << endl << endl;
        
        
        
	}
    searchData1.close();
    searchData2.close();
	randomData.close();
};


void exportGnuplot(string file1, string file2, bool runTime){
    ofstream GnuCom;
    GnuCom.open("GnuExe.txt");
    GnuCom << " set xlabel 'Distance between centroid of the starting triangle and searched point' "<< endl;
    if(runTime)
        GnuCom << " set ylabel 'Runtime' '" << endl; 
    else
        GnuCom << " set ylabel 'Length of path (number of passed triangles)' " << endl;
    
    GnuCom << "plot '" << file1 << "' , '" << file2 << "'" << endl;
    GnuCom << "pause -1 'Hit any key to continue' " << endl;
    GnuCom.close();
    system("gnuplot GnuExe.txt");
    system("rm GnuExe.txt");
}














