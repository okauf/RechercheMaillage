#include "T3.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <time.h>
using namespace std;

class Maillage{
    
private:
    T3<double>* vertices;
    Triangle* triangles;
    int numbVertices, numbTri;
public:
    Maillage(string input):vertices(LoadVertices(input)), triangles(LoadTriangles(input)){};
    
    T3<double>* GetVertices() {return vertices;}
    Triangle* GetTriangles() {return triangles;}
    int GetNumbVertices() {return numbVertices;}
    int GetNumbTri() {return numbTri;}
    
    void SetNumbVertices(int n) { numbVertices = n; }
    void SetNumbTri(int n) { numbTri = n; }
    
    T3<double>* LoadVertices(string input){
        
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
        // saving the number of vertices
        int numbVertices = stoi(line);
        SetNumbVertices(numbVertices);
        
        //generating the tableau of R3
        T3<double> * tab = new T3<double>[numbVertices];
        
        //ignoring the next line
        getline(mshmaillage,line);
        
        int i = 0;
        while(i < numbVertices){
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
    
    Triangle* LoadTriangles(string input){
        
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
    
    Triangle & Promenade(Triangle & T, const T3<double> & p, vector<Triangle> & path){
        
        path.push_back(T);
        
        T3<double> c1 = vertices[T[0]-1], c2 = vertices[T[1]-1], c3 = vertices[T[2]-1];
        
        double aire = c1.oriented_vol(c2,c3);
        double a1 = c2.oriented_vol(c3,p), a2 = c3.oriented_vol(c1,p), a3 = c1.oriented_vol(c2,p);
        
        if (aire < 0){
            a1 = -a1; a2 = -a2; a3 = -a3;
        }
		
		a1 = T.getNeighbor1() < 0 ? 0 : a1;
		a2 = T.getNeighbor2() < 0 ? 0 : a2;
		a3 = T.getNeighbor3() < 0 ? 0 : a3;
        
		switch (min_neg(a1,a2,a3)) {
            case -1:
                //all oriented volumes are positive
                return T;
            case 1:
                return Promenade(triangles[T.getNeighbor1()],p,path);
            case 2:
                return Promenade(triangles[T.getNeighbor2()],p,path);
            case 3:
                return Promenade(triangles[T.getNeighbor3()],p,path);
			default:
				return T; // XXXXX avoid warning
        }
         
    }
    
    //promenade for ex 5
    Triangle & Promenade(Triangle & T, const T3<double> & p){
 
        T3<double> c1 = vertices[T[0]-1], c2 = vertices[T[1]-1], c3 = vertices[T[2]-1];
        
        double aire = c1.oriented_vol(c2,c3);
        double a1 = c2.oriented_vol(c3,p), a2 = c3.oriented_vol(c1,p), a3 = c1.oriented_vol(c2,p);
        
        if (aire < 0){
            a1 = -a1; a2 = -a2; a3 = -a3;
        }
        
        a1 = T.getNeighbor1() < 0 ? 0 : a1;
        a2 = T.getNeighbor2() < 0 ? 0 : a2;
        a3 = T.getNeighbor3() < 0 ? 0 : a3;
        
        switch (min_neg(a1,a2,a3)) {
            case -1:
                //all oriented volumes are positive
                return T;
            case 1:
                return Promenade(triangles[T.getNeighbor1()],p);
            case 2:
                return Promenade(triangles[T.getNeighbor2()],p);
            case 3:
                return Promenade(triangles[T.getNeighbor3()],p);
			default:
				return T; // XXXXX avoid warning
        }

    }
	
	void setAdjacencyViaMultimap(){
    
    multimap<pair<int,int>,int> adjacency;
    // each triangle defines three edges which will serve as keys for the multimap, the mapped value will be the position of triangle int list triangles
    for(int i = 0; i < numbTri; i++){
        
        pair<int,int> edge1  (triangles[i][0],triangles[i][1]);
        adjacency.insert(make_pair(edge1,i));
        
        pair<int,int> edge2  (triangles[i][0],triangles[i][2]);
        adjacency.insert(make_pair(edge2,i));
        
        pair<int,int> edge3  (triangles[i][1],triangles[i][2]);
        adjacency.insert(make_pair(edge3,i));
    }
    
    //find the adjacent triangles
    //therefore, it has to be ranged over the multimap again
    //pos2 will be changed to the position of the neighbored triangle if it exists
    int pos2 = -1;
    
    multimap<pair<int,int>,int>:: iterator it = adjacency.begin();
    while(it != adjacency.end()){
        pair<int,int> commonEdge = it->first;
        int pos1 = it->second;
        
        
        //erase the element, happens in constant time
        //directly erasing by using the iterator is not working
        multimap<pair<int,int>,int>:: iterator it2 = it;
        it++;
        
        adjacency.erase(it2);
        
        //find the neighborded triangle if it exists and save the key
        map<pair<int,int>,int>::iterator itemp = adjacency.find(commonEdge);
        if(itemp != adjacency.end()){
            pos2 = itemp->second;
            
            
            //set the reference to the neighbor at the right position if it exists
            if(triangles[pos1][0] != commonEdge.first && triangles[pos1][0] != commonEdge.second){
                triangles[pos1].setNeighbor1(pos2);
            }
            else {
                if(triangles[pos1][1] != commonEdge.first && triangles[pos1][1] != commonEdge.second){
                    triangles[pos1].setNeighbor2(pos2);
                }
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

void setAdjacencyViaList(){
    
    list<Triangle> adjacency;
    
	// each triangle is inserted three times in the list (once for each edge)
    for (int i = 0; i < numbTri; i++){
        adjacency.push_front(Triangle(triangles[i][0],triangles[i][1],i));
        adjacency.push_front(Triangle(triangles[i][0],triangles[i][2],i));
        adjacency.push_front(Triangle(triangles[i][1],triangles[i][2],i));
    }
    
	// lexicographical ordering of the list to enable finding adjacent triangles
    adjacency.sort();
    
    Triangle prev_tri = adjacency.front();
    adjacency.pop_front();
    Triangle curr_tri;
    while (!adjacency.empty()){
        curr_tri = adjacency.front();
        adjacency.pop_front();
        
        if (curr_tri[0] == prev_tri[0] && curr_tri[1] == prev_tri[1]){
            
            //set the reference to the neighbor at the right position if it exists
			// set neighbor for prev_tri
            if(triangles[prev_tri[2]][0] != curr_tri[0] && triangles[prev_tri[2]][0] != curr_tri[1]){
                triangles[prev_tri[2]].setNeighbor1(curr_tri[2]);
            }
            else {
                if(triangles[prev_tri[2]][1] != curr_tri[0] && triangles[prev_tri[2]][1] != curr_tri[1]){
                    triangles[prev_tri[2]].setNeighbor2(curr_tri[2]);
                }
                else
                    triangles[prev_tri[2]].setNeighbor3(curr_tri[2]);
            }
            
			// set neighbor for curr_tri
            if(triangles[curr_tri[2]][0] != curr_tri[0] && triangles[curr_tri[2]][0] != curr_tri[1])
                triangles[curr_tri[2]].setNeighbor1(prev_tri[2]);
            else {
                if(triangles[curr_tri[2]][1] != curr_tri[0] && triangles[curr_tri[2]][1] != curr_tri[1])
                    triangles[curr_tri[2]].setNeighbor2(prev_tri[2]);
                else
                    triangles[curr_tri[2]].setNeighbor3(prev_tri[2]);
            }
        }
        
        prev_tri = curr_tri;
    }
    
}

void exportGnuplot(vector<Triangle> & triangles_path, const T3<double>* points, int numbPoints){
    //if just one point shall be depicted, give the function a T3<double>* pointer to an array of length 1 and set numbPoints to one
    cout << "Creating the plot" << endl;
    
    
    // creating the textfile for the marked triangles in the mesh
    ofstream Data;
    Data.open("outputTriangles.txt");
    Data << "#Coordiantes" << endl;
    Data << "#X \t Y \t Z" << endl;
    
    int i = 0;
    for (vector<Triangle>::iterator it = triangles_path.begin(); it != triangles_path.end(); it++){
        Data << "#Triangle " << endl;
        for(int j = 0; j < 3; j++){
            Data << vertices[triangles_path[i][j]-1] << endl;
        }
        Data << vertices[triangles_path[i][0]-1] << endl;
        // insert the last point again in order to connect the points
        Data << endl;  //This creates blocks of points which will be connected by lines
        i++;
    }
    Data.close();
    
    //creating a textfile for the whole mesh
    Data.open("outputNetwork.txt");
    for(int i = 0; i < numbTri; i++){
        Data << "#Triangle " << i+1 << endl;
        for(int j = 0; j < 3; j++){
            Data << vertices[triangles[i][j]-1] << endl;
        }
        Data << vertices[triangles[i][0]-1] << endl;
        // insert the last point again in order to connect the points
        //This creates blocks of points which will be connected by lines
        Data << endl;
    }
    Data.close();
    
    //creating the textfile for the points
    if(numbPoints != 0){
        Data.open("outputPoint.txt");
        Data << "#Point" << endl;
        for(int i = 0; i < numbPoints; i++){
            Data << points[i] << endl;
        }
		Data.close();
    }

    //Script for Gnuplot
    ofstream GnuCom;
    GnuCom.open("GnuExe.txt");
    
	GnuCom << "set xrange [-2:2]" << endl << "set yrange [-2:2]" << endl;
    
    if(numbPoints != 0){
        GnuCom << "plot 'outputNetwork.txt' with lines linetype 4,  'outputtriangles.txt' with lines lt -1, 'outputPoint.txt' " << endl;
    } else {
        GnuCom << "plot 'outputNetwork.txt' with lines linetype 4,  'outputtriangles.txt' with lines lt -1 " << endl;
	}
	
	// GnuCom << "set output 'b.png'" << endl;
    // In order to keep the file open
    GnuCom << "pause -1 'Hit any key to continue' " << endl;
    GnuCom.close();
    
    system("gnuplot GnuExe.txt ");
    
}

};

int selectAdjacentVertex(const pair<int,int> & edge, const Triangle & Neighbor_m){
    if (Neighbor_m[0] != edge.first && Neighbor_m[0] != edge.second){
        return 0;
    } else if (Neighbor_m[1] != edge.first && Neighbor_m[1] != edge.second){
        return 1;
    } else {
        return 2;
    }
}

void Triangle_Recurrence(vector<Triangle> & coveringTriangles, Maillage & m, Maillage & M, Triangle firstTriangle_m){
    
    Triangle * triangles_m = m.GetTriangles();
    T3<double> * vertices_m = m.GetVertices();
    
    //the starting triangles are exactly the triangles (in M) who cover the vertices of the triangle in m (firstTriangle_m)
    
    //covers the 1st vertex of firstTriangle_m
    Triangle firstTriangle_M = coveringTriangles[firstTriangle_m[0]-1];
    //covers the 2nd vertex of firstTriangle_m
    Triangle secondTriangle_M = coveringTriangles[firstTriangle_m[1]-1];
    //covers the 3rd vertex of firstTriangle_m
    Triangle thirdTriangle_M = coveringTriangles[firstTriangle_m[2]-1];
   
    Triangle Start;
    int adjVertex;
    
    //the vertices of m who shall be covered next are the vertices of the neighbors of firstTriangle_m
    //they are (relatively) close to first/second/third triangle_M
    
    //check if it has a neighbor
    if (firstTriangle_m.getNeighbor1() != -1){
        
        //selesct neighbor1_m
        Triangle Neighbor1_m = triangles_m[firstTriangle_m.getNeighbor1()];
        
        //find the vertex of the neighbor1_m that is possibly not covered yet
        pair<int,int> edge (firstTriangle_m[1],firstTriangle_m[2]);
        adjVertex = selectAdjacentVertex(edge, Neighbor1_m);
        
        
        if (adjVertex == 0) {
            // if the first vertex of neighbor1_m is possibly not covered yet we will start the algorithm with the covering triangle of
            // a vertex of the adjacent triangle neghbor1_m of firstTriangle_m; these are secondTriangle_M and thirdTriangle_M
            //they are closer to this vertex than firstTriangle_M XXXXXX????
            Start = secondTriangle_M;
        } else if (adjVertex == 1){
            Start = thirdTriangle_M;
        } else { Start = firstTriangle_M; }
        // check if a covering triangle has been found before
        if (coveringTriangles[Neighbor1_m[adjVertex]-1][0] == 0){
            
            //Find the actual covering triangle and ad it to the list
            coveringTriangles[Neighbor1_m[adjVertex]-1] = M.Promenade(Start, vertices_m[Neighbor1_m[adjVertex]-1]);
            //start the algorithm again with neighbor1_m
            Triangle_Recurrence(coveringTriangles, m, M, Neighbor1_m);
        }
    }
    
    if( firstTriangle_m.getNeighbor2() != -1){
        Triangle Neighbor2_m = triangles_m[firstTriangle_m.getNeighbor2()];
        pair<int,int> edge (firstTriangle_m[0],firstTriangle_m[2]);
        adjVertex = selectAdjacentVertex(edge, Neighbor2_m);
        if (adjVertex == 0) {
            Start = secondTriangle_M;
        } else if (adjVertex == 1){
            Start = thirdTriangle_M;
        } else { Start = firstTriangle_M; }
        
        if (coveringTriangles[Neighbor2_m[adjVertex]-1][0] == 0){
            coveringTriangles[Neighbor2_m[adjVertex]-1] = M.Promenade(Start, vertices_m[Neighbor2_m[adjVertex]-1]);
            
            Triangle_Recurrence(coveringTriangles, m, M, Neighbor2_m);
        }
    }
    
    if ( firstTriangle_m.getNeighbor3() != -1){
        Triangle Neighbor3_m = triangles_m[firstTriangle_m.getNeighbor3()];
        pair<int,int> edge (firstTriangle_m[0],firstTriangle_m[1]);
        adjVertex = selectAdjacentVertex(edge, Neighbor3_m);
        if (adjVertex == 0) {
            Start = secondTriangle_M;
        } else if (adjVertex == 1){
            Start = thirdTriangle_M;
        } else { Start = firstTriangle_M; }
        
        if (coveringTriangles[Neighbor3_m[adjVertex]-1][0] == 0){
            coveringTriangles[Neighbor3_m[adjVertex]-1] = M.Promenade(Start, vertices_m[Neighbor3_m[adjVertex]-1]);
            Triangle_Recurrence(coveringTriangles, m, M, Neighbor3_m);
        }
    }
    
}

vector<Triangle>& findVertices(Maillage & m, Maillage & M, vector<Triangle> & coveringTriangles){
    
    //search for vertices of m in M 
    
    // int numbVertices_m = m.GetNumbVertices();
    T3<double> * vertices_m = m.GetVertices();
    Triangle * triangles_m = m.GetTriangles();
    
    //int numbVertices_M = M.GetNumbVertices();
    int numbTri_M = M.GetNumbTri();
    // T3<double> * vertices_M = M.GetVertices();
    Triangle * triangles_M = M.GetTriangles();
    
    srand(time(NULL));
    
    //choose a random start triangle whose vertices shall be searched
    Triangle firstTriangle_m = triangles_m[rand()%m.GetNumbTri()];
    
    //choose the first vertex for which a covering triangle shall be found
    T3<double> firstVertex = vertices_m[firstTriangle_m[0]-1];
    
    //choose a random start triangle for the algorithm promenade
    Triangle firstStartTri = triangles_M[rand()%numbTri_M];
    
    //find the first covering triangle for the vertex
    Triangle firstTriangle_M = M.Promenade(firstStartTri, firstVertex);
    
    //all covering triangles will be saved in the vector covering triangles
    //they have to be saved at the right position, that is the number of the vertex they cover
    coveringTriangles[firstTriangle_m[0]-1] = firstTriangle_M;
    
    //find the other covering triangles of the second and third vertex of the start triangle whose vertices shall be covered
    T3<double> secondVertex = vertices_m[firstTriangle_m[1]-1];
    //start the algorithm with the covering triangle of the first vertex
    Triangle secondStartTri = firstTriangle_M;
    Triangle secondTriangle_M = M.Promenade(secondStartTri, secondVertex);
    coveringTriangles[firstTriangle_m[1]-1] = secondTriangle_M;
    
    T3<double> thirdVertex = vertices_m[firstTriangle_m[2]-1];
    //start the algorithm with the covering triangle of the second vertex
    Triangle thirdStartTri = secondTriangle_M;
    Triangle thirdTriangle_M = M.Promenade(thirdStartTri, thirdVertex);
    coveringTriangles[firstTriangle_m[2]-1] = thirdTriangle_M;
    
    //after the first three covering triangles are found the recurrence can be started
    Triangle_Recurrence(coveringTriangles, m, M, firstTriangle_m);
    
    return coveringTriangles;
    
}






