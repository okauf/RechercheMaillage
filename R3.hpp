
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
using namespace std;

template <typename T>;
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
    T3();
    T3(T a, T b, T c): x(a),y(b),z(c){}
    T3(const T3 &v){x = v.x; y = v.y; z = v.z;}
    T & operator[] (int i){
        assert(0 <= i && i < 3);
        switch (i) {
            case 0:
                return x;
                break;
            case 1:
                return y;
            case 2:
                return z;
            default:                                  //should never be reached because of assert
                return x;
        }
    }
    T3 & operator =(const T3 & v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    T dist(const T3&);
    bool operator==(const T3&);
    T operator,(const T3&);
    T3 operator +(const T3&);
    
    
};
T3:: T3(): x(0), y(0), z(0){}
//T T::double dist(const T3 &v){                       //by & the function accepts just the refence of the variable
//    return  sqrt(x*v.x+y*v.y+z*v.z);
//}
bool T3::operator==(const T3 &v){
    
    return (x == v.x && y == v.y && z == v.z);
}
T T3:: operator,(const T3 &v){
    return x*v.x+y*v.y+z*v.z;
}
T3 T3::operator +(const T3 &v){
    return T3(x+v.x, y+v.y, z+v.z);
}

