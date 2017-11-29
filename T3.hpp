
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
    T3 operator +(const T3 &v){
        return T3(x+v.x, y+v.y, z+v.z);
    }

    
    
	
	T produit_mixte(const T3 & P, const T3 & Q) const {return  x*P.y*Q.z + P.x*Q.y*z + Q.x*y*P.z - z*P.y*Q.x - y*P.x*Q.z - x*P.z*Q.y;} // produit mixte
    
    // friend T3 operator*(T c,const T3 & P);
    
};

//T T::double dist(const T3 &v){                       //by & the function accepts just the refence of the variable
//    return  sqrt(x*v.x+y*v.y+z*v.z);
//}

// inline T produit_mixte(const T3 & A, const T3 & P, const T3 & Q) {return A.produit_mixte(P,Q);}



//in order to define an object of the class T3 write T3<datatype> name;

