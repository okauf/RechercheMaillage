#include "T3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
using namespace std;

class Maillage{
    
private:
    T3<double>* sommets;
    Triangle* triangles;
	int numbSommets, numbTri;
public:
	Maillage(char* const input):sommets(LoadNodes(input)), triangles(LoadTriangles(input)){};
	
	T3<double>* GetSommets() {return sommets;}
	Triangle* GetTriangles() {return triangles;}
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

Triangle* LoadTriangles(char* const input){
	
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
    Triangle* triangles = new Triangle[numbTri];
    
    //ignoring the nextline
    getline(mshmaillage,line);
    
    int i = 0;
    while(i < numbTri){
        int a,b,c;     // save the positions of the points
        getline(mshmaillage,line);
        stringstream linestream;
        linestream << line;
        linestream >> a >>  b >> c;
        triangles[i] = Triangle(a,b,c);
        i++;
    }
    mshmaillage.close();
    
    return triangles;
}

Triangle Adjacency(const Triangle & T, int i){
	
	assert(i <= 2 && i >= 0);
	
	// initialisation
	list<Triangle> l;
	int n0, n1, n2, m01, m02, m12, M01, M02, M12;
	for (int i = 0; i < numbTri; i++){
		n0 = triangles[i][0];
		n1 = triangles[i][1];
		n2 = triangles[i][2];
		m01 = min(n0,n1); m02 = min(n0,n2); m12 = min(n1,n2);
		M01 = max(n0,n1); M02 = max(n0,n2); M12 = max(n1,n2);
		l.push_front(Triangle(m01,M01,n2));
		l.push_front(Triangle(m02,M02,n1));
		l.push_front(Triangle(m12,M12,n0));
	}
	// lexicographical ordering in O(NlogN) where N is the container size
	l.sort();
	
	int a1 = (i+1)%3, a2 = (i+2)%3;
	// cout << "Popping out the elements in l:"<<endl;
	while (!l.empty() && (l.front()[0] != T[a1] || l.front()[1] != T[a2] || l.front()[2] == T[i])){
		// cout << l.front() << endl;
		l.pop_front();
	}
	
	// list<Triangle>::iterator it = l.begin();
	// cout << *it << endl;
	return !l.empty() ? l.front() : T;
}

Triangle Promenade(const Triangle & T, const T3<double> & p){
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
		Triangle RandomNeighbor = Adjacency(T,i);
		return Promenade(RandomNeighbor,p);
	}
}

};

void setAdjacencyViaMultiMap(Maillage m){
    Triangle* triangles = m.GetTriangles();
    
    
    multimap<pair<int,int>,int> adjacency;
    // each traingle defines three edges which will serve as keys for the multimap, the mapped value will be the position of triangle int list triangles
    int numbTriangles = m.GetNumbTri();
    for(int i = 0; i < numbTriangles; i++){
        pair<int,int> edge1  (triangles[i][0],triangles[i][1]);
        adjacency.insert(make_pair(edge1,i));
        
        pair<int,int> edge2  (triangles[i][0],triangles[i][2]);
        adjacency.insert(make_pair(edge2,i));
        
        pair<int,int> edge3  (triangles[i][1],triangles[i][2]);
        adjacency.insert(make_pair(edge3,i));
    }
    
    //find the adjacent triangles
    //therefore, it has to be ranged over the multimap again
    //pos2 will be changed to the postion of the neighbored triangle if it exists
    int pos2 = -1;
    
    multimap<pair<int,int>,int>:: iterator it;
    for(it = adjacency.begin(); it != adjacency.end(); ++it){
        pair<int,int> commonEdge = it->first;
        int pos1 = it->second;
        cout << "Considering edge (" << commonEdge.first << "," << commonEdge.second << ") in the triangle " << triangles[pos1] << endl;
        //erase the element, happens constant time
        adjacency.erase(it);
        
        //find the neighborded triangle if it exists and save the key
        map<pair<int,int>,int>::iterator itemp = adjacency.find(commonEdge);
        if(itemp != adjacency.end()){
           pos2 = itemp->second;
            cout << "The neighbor is " << triangles[pos2] << endl;
            //set the reference to the neighbor at the right position if it exists
            if(triangles[pos1][0] != commonEdge.first && triangles[pos1][0] != commonEdge.second)
                triangles[pos1].setNeighbor1(pos2);
            else {
                if(triangles[pos1][1] != commonEdge.first && triangles[pos1][1] != commonEdge.second)
                    triangles[pos1].setNeighbor2(pos2);
                    else
                        triangles[pos1].setNeighbor3(pos2);
                }
           
                if(triangles[pos2][0] != commonEdge.first && triangles[pos2][0] != commonEdge.second)
                    triangles[pos2].setNeighbor1(pos1);
                else {
                    if(triangles[pos2][1] != commonEdge.first && triangles[pos2][1] != commonEdge.second)
                        triangles[pos2].setNeighbor2(pos1);
                    else
                        triangles[pos2].setNeighbor3(pos1);
                }
        }
        
    }



    

        
        
                
            
        
    
        
        
            
    




}

void exportGnuplot(Maillage m){
    ofstream TriangleData;
    TriangleData.open("output.txt");
    TriangleData << "#Coordiantes" << endl;
    TriangleData << "#X \t Y \t Z" << endl;
    
    Triangle* triangles = m.GetTriangles();
    T3<double>* sommets = m.GetSommets();
    cout << endl;
   
    
    for(int i = 0; i < m.GetNumbTri(); i++){
        TriangleData << "#Triangle " << i+1 << endl;
        for(int j = 0; j < 3; j++){
            TriangleData << sommets[triangles[i][j]-1] << endl;
        }
        cout << endl;
        TriangleData << sommets[triangles[i][0]-1] << endl;
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


