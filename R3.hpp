
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
using namespace std;


class R3{
    
    friend std::ostream& operator <<(std::ostream& f, const R3 &v){   //friend in order to get private variables
        f   << v.x << "\t" << v.y << "\t" << v.z;
        return f;
    }
    friend std::istream& operator >>(std::istream& f,  R3 &v){
        char a;
        
        f >> a >> v.x >> a >> v.y >> a >> v.z >> a;
        return f;
    }
    
private:
    double x,y,z;
    
public:
    R3();
    R3(double a, double b, double c): x(a),y(b),z(c){}
    R3(const R3 &v){x = v.x; y = v.y; z = v.z;}
    double & operator[] (int i){
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
    R3 & operator =(const R3 & v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    double dist(const R3&);
    bool operator==(const R3&);
    double operator,(const R3&);
    R3 operator +(const R3&);
    
    
};
R3:: R3(): x(0), y(0), z(0){}
double R3:: dist(const R3 &v){                       //by & the function accepts just the refence of the variable
    return  sqrt(x*v.x+y*v.y+z*v.z);
}
bool R3::operator==(const R3 &v){
    
    return (x == v.x && y == v.y && z == v.z);
}
double R3:: operator,(const R3 &v){
    return x*v.x+y*v.y+z*v.z;
}
R3 R3::operator +(const R3 &v){
    return R3(x+v.x, y+v.y, z+v.z);
}

