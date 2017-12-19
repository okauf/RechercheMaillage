#include "Maillage.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <time.h>
#include <math.h>
using namespace std;
using namespace std::chrono;

int main(){
	
string name = "maillage4.msh";
Maillage m(name);
m.setAdjacencyViaList();
int numbExp = 10;

// random starting triangles
int numbTri = m.GetNumbTri();
int * randomTriIndex = new int[numbExp];
// random points in the unit disk to be covered
T3<double> * randomSommets = new T3<double>[numbExp];
double radius, angle;
srand(time(NULL));
for (int i = 0; i < numbExp; i++){
	int help = rand()%numbTri;
	randomTriIndex[i] = help;
	// cout << help << " ";
	
	radius = (rand() % 10000) / 10000.0;
	angle = 2 * M_PI * (rand() % 10000) / 10000.0;	
	randomSommets[i] = T3<double>(radius*cos(angle),radius*sin(angle),0);
	// cout << randomSommets[i] << endl;
}

Triangle* triangles = m.GetTriangles();
vector<Triangle> path;
int * path_length = new int[numbExp];
double * running_time = new double[numbExp];
for (int i = 0; i < numbExp; i++){
	path.clear();
	auto t1 = high_resolution_clock::now();
	Triangle P = m.Promenade(triangles[randomTriIndex[i]],randomSommets[i],path);
	auto t2 = high_resolution_clock::now();
	duration<double> durationIns = t2-t1;
	running_time[i] = durationIns.count();
	path_length[i] = path.size();
	cout << running_time[i] << " " << path_length[i] << endl;
}
	
}

	// string name = "maillage4.msh";
	// Maillage m(name);
	// auto t1 = high_resolution_clock::now();
	// setAdjacencyViaList(m);
	// setAdjacencyViaMultiMap(m);
	// auto t2 = high_resolution_clock::now();
	// duration<double> durationIns = t2-t1;
	// cout << durationIns.count() << endl;