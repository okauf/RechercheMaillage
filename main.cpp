#include "Maillage.hpp"
#include <iostream>
using namespace std;

int main(){
    
    Maillage m("maillage2.msh");
	T3<double> vec, vec2(0,1.,3);
	T3<int> vec3(1,2,3), vec4(0.,1,2);
	cout << vec << endl;
	cout << vec2 << endl;
	cout << vec3 << endl;
	cout << vec4 << endl;
    return 0;
}