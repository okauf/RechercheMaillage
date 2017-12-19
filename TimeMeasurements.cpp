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

int numbTri = m.GetNumbTri();
vector<int> randomTriIndex;
for (int i = 0; i < 10; i++){
	srand(time(NULL));
	randomTriIndex.push_back(rand()%numbTri);
}

vector<T3<double>> randomSommets;
double radius, angle;
srand(time(NULL));
for (int i = 0; i < 10; i++){
	radius = (rand() % 10000) / 10000.0;
	angle = 2 * M_PI * (rand() % 10000) / 10000.0;	
	T3<double> randomSommet(radius*cos(angle),radius*sin(angle),0);
	cout << randomSommet << endl;
	randomSommets.push_back(randomSommet);
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