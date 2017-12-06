#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>

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
    T3 operator+(const T3 &v){
        return T3(x+v.x, y+v.y, z+v.z);
    }
	
	// T3 operator-(const T3 &v){
		// return T3(x-v.x, y-v.y, z-v.z);
	// }
	
	// T3 crossproduct(const T3 &v) {return T3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);}
	
    // lexicographical order
    bool operator<(const T3& v){
        if (x<v.x) return 1; else if (x==v.x && y<v.y) return 1; else if (x==v.x && y==v.y && z<v.z) return 1; else return 0;
    }
//    bool comp(const T3 &u, const T3 &v){
//        if (u.x<v.x) return 1; else if (u.x==v.x && u.y<v.y) return 1; else if (u.x==v.x && u.y==v.y && u.z<v.z) return 1; else return 0;
//    }

	
	// T produit_mixte(const T3 & P, const T3 & Q) const {return  x*P.y*Q.z + P.x*Q.y*z + Q.x*y*P.z - z*P.y*Q.x - y*P.x*Q.z - x*P.z*Q.y;} // produit mixte
	
	T oriented_vol(const T3 &v, const T3 &w){
		// T3 cross = (v-this).crossproduct(w-v);
		return (v.x-x)*(w.y-v.y) - (v.y-y)*(w.x-v.x);
	}
	
	bool wheretogo(const T3 &u, const T3 &v, const T3 &w) const {
		T3 norm = T3(-u.y+v.y,u.x-v.x,0);
//        cout << "norm is " << norm << endl;
//		cout << "norm * 3rd point " <<  (norm,w) << endl;
//        cout << "norm * 1st or 2nd point " << (norm,u) <<  " " << (norm,v) << endl;
//		cout << "norm * this " <<  (norm,*this) << endl;
        
		// cout << " test u  - v " << u,norm == v,norm << endl;
		return ((norm,*this)<(norm,u) && (norm,u)<(norm,w)) || ((norm,w)<(norm,u) && (norm,u)<(norm,*this));
	}
    
};




//T T::double dist(const T3 &v){                       //by & the function accepts just the refence of the variable
//    return  sqrt(x*v.x+y*v.y+z*v.z);
//}

// inline T produit_mixte(const T3 & A, const T3 & P, const T3 & Q) {return A.produit_mixte(P,Q);}



//in order to define an object of the class T3 write T3<datatype> name;



//Class triangle which is a derived class from the class T3<int>; it has as additional members the neighbors
class Triangle: public T3<int>{
private:
    //Neighbors are described by their position in the list of triangles in Maillage
    int neighbor1, neighbor2, neighbor3;
public:
    //The default constructor sets the neoghbors to -1, this is changed lateron when a neighbor exists
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
    
//    bool operator<(const Triangle &v){
//        if (x<v.x) return 1; else if (x==v.x && y<v.y) return 1; else if (x==v.x && y==v.y && z<v.z) return 1; else return 0;
//    }

    
};













