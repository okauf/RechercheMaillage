#include "T3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <list>
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

T3<int> Adjacency(const T3<int> & T, int i){
	
	assert(i <= 2 && i >= 0);
	
	// initialisation
	list<T3<int>> l;
	int n0, n1, n2, m01, m02, m12, M01, M02, M12;
	for (int i = 0; i < numbTri; i++){
		n0 = triangles[i][0];
		n1 = triangles[i][1];
		n2 = triangles[i][2];
		m01 = min(n0,n1); m02 = min(n0,n2); m12 = min(n1,n2);
		M01 = max(n0,n1); M02 = max(n0,n2); M12 = max(n1,n2);
		l.push_front(T3<int>(m01,M01,n2));
		l.push_front(T3<int>(m02,M02,n1));
		l.push_front(T3<int>(m12,M12,n0));
	}
	// lexicographical ordering in O(NlogN) where N is the container size
	l.sort();
	
	int a1 = (i+1)%3, a2 = (i+2)%3;
	// cout << "Popping out the elements in l:"<<endl;
	while (!l.empty() && (l.front()[0] != T[a1] || l.front()[1] != T[a2] || l.front()[2] == T[i])){
		// cout << l.front() << endl;
		l.pop_front();
	}
	
	// list<T3<int>>::iterator it = l.begin();
	// cout << *it << endl;
	return !l.empty() ? l.front() : T;
}

T3<int> Promenade(const T3<int> & T, const T3<double> & p){
	cout << T << endl;
	double a1, a2, a3;
	T3<double> c1 = sommets[T[0]], c2 = sommets[T[1]], c3 = sommets[T[2]];
	a1 = c1.produit_mixte(c2,p);
	a2 = c2.produit_mixte(c3,p);
	a3 = c3.produit_mixte(c1,p);
	
	if (a1 > 0 && a2 > 0 && a3 > 0){
		return T;
	} else {
		int i = rand()%3; // random number between 0 and 2
		T3<int> RandomNeighbor = Adjacency(T,i);
		return Promenade(RandomNeighbor,p);
	}
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


