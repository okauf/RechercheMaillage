#include <iostream>
#include <cassert>
#include <time.h>
using namespace std;

template<typename T>

class T3{
    
    friend std::ostream& operator <<(std::ostream& f, const T3 &v){   //friend in order to get private variables
        f   << v.x << "\t" << v.y << "\t" << v.z;
        return f;
    }
    friend std::istream& operator >>(std::istream& f,  T3 &v){
        char a;
        
        f >> a >> v.x >> a >> v.y >> a >> v.z >> a;
        return f;
    }
    
private:
    T x,y,z;
    
public:
    T3(): x(0), y(0), z(0){}
    T3(T a, T b, T c): x(a),y(b),z(c){}
    T3(const T3 &v){x = v.x; y = v.y; z = v.z;}
    // version qui peut modifie la class  via l'adresse de x ou y 
	T & operator[](int i) { if(i==0) return x; else if (i==1) return y; else if (i==2) return z; else {assert(0);exit(1);} ;}
	// version qui retourne une reference const qui ne modifie pas la class
	const T & operator[](int i) const { if(i==0) return x; else if (i==1) return y; else if (i==2) return z; else {assert(0);exit(1);} ;}
    T3 & operator =(const T3 & v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    
    bool operator==(const T3 &v){
        return (x == v.x && y == v.y && z == v.z);
    }
    T operator,(const T3 &v){
        return x*v.x+y*v.y+z*v.z;
    }
   	
    // lexicographical order
    bool operator<(const T3& v) const {
        if (x<v.x) return 1; else if (x==v.x && y<v.y) return 1; else if (x==v.x && y==v.y && z<v.z) return 1; else return 0;
    }


	
	T oriented_vol(const T3 &v, const T3 &w){
		return (v.x-x)*(w.y-v.y) - (v.y-y)*(w.x-v.x);
	}
	
	
};



int min_neg(const double & x, const double & y, const double & z){
	if (x>=0 && y>=0 && z>=0){
		return -1;
	} else if (x < 0 && x<=y && x<=z) {
		return 1;
	} else if (y < 0 && y<=x && y<=z) {
		return 2;
	} else { return 3;}
};

// int random_neg(const double & x, const double & y, const double & z){
//     
//     int boolx = (x < 0)?1:0, booly = (y < 0)?1:0, boolz = (z < 0)?1:0;
//     if (boolx == 0 && booly == 0 && boolz == 0){
//         return -1;
//	 }
//     int neg_numb = boolx + booly + boolz;
//     if (neg_numb  == 1){
//         if(boolx == 1){ return 1; }
//         if(booly == 1){ return 2; }
//         if(boolz == 1){ return 3; }
//     } else {
//		 struct timespec nanos;
//		 clock_gettime(CLOCK_MONOTONIC, &nanos);
//		 srand(nanos.tv_nsec);
//         int rand_numb = rand()%2; cout << rand_numb << " ";
//         if(boolx == 0){ return rand_numb + 2; }
//         if(booly == 0){ return 2*rand_numb + 1; }
//         if(boolz == 0){ return rand_numb + 1; }
//     }
//	 return -2; // XXXXX avoid warning
// };


//Class triangle which is a derived class from the class T3<int>; it has as additional members the neighbors
class Triangle: public T3<int>{
private:
    //Neighbors are described by their position in the list of triangles in Maillage
    int neighbor1, neighbor2, neighbor3;
public:
    //The default constructor sets the neighbors to -1, this is changed lateron when a neighbor exists
    Triangle():neighbor1(-1),neighbor2(-1),neighbor3(-1) {}
    
    //Constructor of the base class has to be defined for the derived class
    Triangle(int x, int y, int z): T3<int>(x,y,z){
        neighbor1 = -1;neighbor2 = -1;neighbor3 = -1;
    }
    
    //Getter and setter who are necessary for adjacency functions
    
    int getNeighbor1(){
        return neighbor1;
    }
    int getNeighbor2(){
        return neighbor2;
    }
    int getNeighbor3(){
        return neighbor3;
    }
    void setNeighbor1(int pos){
        neighbor1 = pos;
    }
    void setNeighbor2(int pos){
        neighbor2 = pos;
    }
    void setNeighbor3(int pos){
        neighbor3 = pos;
    }
    
};