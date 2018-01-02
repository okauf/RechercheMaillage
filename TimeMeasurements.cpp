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
void runPromenade(Maillage & m, string input, string name);
void mergeResultsToOneTxtFile(string randMeasurements, string minMeasurements, string randomData);

int main(){
	
    string name = "maillage5.msh";
    Maillage m(name);
    m.setAdjacencyViaList();
    int numbExp = 20;

    // file stores starting triangles and points to cover
    string input = "randomData.txt";
    // do not execute defineTriandPoints in order to compare the results of min_neg and random_neg
    //defineTriandPoints(m, input, numbExp);
    
    //runPromenade(m,"RandomData.txt", "MinMeas.txt");
    
    mergeResultsToOneTxtFile("RandMeas.txt","MinMeas.txt","RandomData.txt");

   
	
}

void defineTriandPoints(Maillage & m, string input, int numbExp){
	
	ofstream randomData;
	randomData.open(input);
	
	// random starting triangles
	int numbTri = m.GetNumbTri();
	int randomTriIndex;
	
	// define random points in the unit disk via radius and angle
	double radius, angle;
	srand(time(NULL));
	for (int i = 0; i < numbExp; i++){
		int randomTriIndex = rand()%numbTri;
        
        //index of the random starting triangle
		randomData << randomTriIndex << endl;
	
		radius = (rand() % 10000) / 10000.0;
		angle = 2 * M_PI * (rand() % 10000) / 10000.0;
        //data of the point in the unit disk
		randomData << radius*cos(angle) << " " << radius*sin(angle) << " " << 0 << endl;
	}
	
	randomData.close();
};

void runPromenade(Maillage & m, string input, string name){
	
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
    ofstream searchData;
    searchData.open(name);
	
//	for (int i = 0; i < numbExp; i++){
    while(getline(randomData,line)){
        //path is rewritten in each loop
		path.clear();
		
		// reading list position of the starting triangle
		// getline(randomData,line);
		idx = stoi(line);
		StartTri = triangles[idx];
		// cout << "idx " << idx << endl;
		
		// reading point to cover
		getline(randomData,line);
		stringstream linestream;
		linestream << line;
		linestream >> a >> b >> c;
		p = T3<double>(a,b,c);
		// cout << "p " << p << endl;
		
		// time measurement and path length for method promenade
		auto t1 = high_resolution_clock::now();
		P = m.Promenade(StartTri,p,path);
		auto t2 = high_resolution_clock::now();
		durationIns = t2-t1;
        
        //writing the data in the file
        searchData << durationIns.count() << endl;
        searchData << path.size() << endl;
        
	}
    searchData.close();
	randomData.close();
};


void mergeResultsToOneTxtFile(string randMeasurements, string minMeasurements, string randomData){
    ofstream newFile;
    fstream data, minM, randM;
    string line1, line2, line3;
    newFile.open("Comparison_Min_and_Rand.txt");
    randM.open(randMeasurements);
    minM.open(minMeasurements);
    data.open(randomData);
    
    newFile << "#Each block contains the measurements of the time and number of triangles needed if min_neg respectively rand_neg is used" << endl;
    newFile << "#The first two lines contain the index of the starting triangle as well as the point which is searched" << endl;
    while(getline(data,line1)){
        newFile << line1 <<endl;
        getline(data,line1);
        newFile << line1 << endl;
        newFile << "#results minimum" << endl;
        getline(minM,line2);
        newFile << line2 << endl;
        getline(minM,line2);
        newFile << line2 << endl;
        
        newFile << "#results random" << endl;
        getline(randM, line3);
        newFile << line3 << endl;
        getline(randM, line3);
        newFile << line3 << endl;
        
        newFile << endl;
    }
    
}












