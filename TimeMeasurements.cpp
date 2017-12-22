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
void runPromenade(Maillage & m, string input, int numbExp, int * path_length, double * running_time);

int main(){
	
string name = "maillage4.msh";
Maillage m(name);
m.setAdjacencyViaList();
int numbExp = 10;

string input = "randomData.txt";
// defineTriandPoints(m, input, numbExp);

int * path_length = new int[numbExp];
double * running_time = new double[numbExp];
runPromenade(m, input, numbExp, path_length, running_time);
	
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
		randomData << randomTriIndex << endl;
	
		radius = (rand() % 10000) / 10000.0;
		angle = 2 * M_PI * (rand() % 10000) / 10000.0;
		randomData << T3<double>(radius*cos(angle),radius*sin(angle),0) << endl << endl;
	}
	
	randomData.close();
};

void runPromenade(Maillage & m, string input, int numbExp, int * path_length, double * running_time){
	
	fstream randomData;
	randomData.open(input);
	
	Triangle* triangles = m.GetTriangles();
	vector<Triangle> path;
	
	Triangle StartTri;
	T3<double> p;
	string line;
	
	for (int i = 0; i < numbExp; i++){
		path.clear();
		
		getline(randomData,line);
		int idx;
		stringstream linestream;
		linestream << line;
		linestream >> idx;
		StartTri = triangles[idx];
		
		getline(randomData,line);
		double a, b, c;
		// stringstream linestream;
		linestream << line;
		linestream >> a >> b >> c;
		p = T3<double>(a,b,c);
		
		auto t1 = high_resolution_clock::now();
		Triangle P = m.Promenade(StartTri,p,path);
		auto t2 = high_resolution_clock::now();
		duration<double> durationIns = t2-t1;
		running_time[i] = durationIns.count();
		path_length[i] = path.size();
		cout << running_time[i] << " " << path_length[i] << endl;
	}
	
	randomData.close();
};

	// string name = "maillage4.msh";
	// Maillage m(name);
	// auto t1 = high_resolution_clock::now();
	// setAdjacencyViaList(m);
	// setAdjacencyViaMultiMap(m);
	// auto t2 = high_resolution_clock::now();
	// duration<double> durationIns = t2-t1;
	// cout << durationIns.count() << endl;