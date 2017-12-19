#include "Maillage.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <time.h>
using namespace std;
using namespace std::chrono;

int main(){
	
string name;
name = "maillage4.msh";
Maillage m(name);
setAdjacencyViaList(m);

int numbTri = m.GetNumbTri();
vector<int> randomTriIndex;
for (int i = 0; i < 10; i++){
	srand(time(NULL));
	randomTriIndex.push_back(rand()%numbTri);
}

vector<T3<double>> randomSommets;
int numbSommets = m.GetNumbSommets();
T3<double>* sommets = m.GetSommets();
T3<double> randomSommet;
for (int i = 0; i < 10; i++){
	srand(time(NULL));
	randomSommet = (sommets[rand()%numbSommets] + sommets[rand()%numbSommets])*0.5;
	cout << randomSommet << endl;
	randomSommets.push_back(randomSommet);
}
	
	
	
}

	// char nom[255] = "maillage4.msh";
	// char* const pnom = nom;
	// Maillage m(pnom);
	// auto t1 = high_resolution_clock::now();
	// setAdjacencyViaList(m);
	// setAdjacencyViaMultiMap(m);
	// auto t2 = high_resolution_clock::now();
	// duration<double> durationIns = t2-t1;
	// cout << durationIns.count() << endl;