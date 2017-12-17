#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void prepareMaillageFile(char* const input);

int main(){
    
	char nom[255] = "maillage7.msh";
	char* const pnom = nom;
    prepareMaillageFile(pnom);
	
    return 0;
}

void prepareMaillageFile(char* const input){
	
	string line;
    
	fstream mshmaillage;
	mshmaillage.open(input);
	
	fstream mshmaillage_prep;
	mshmaillage_prep.open("new.msh");
	
	mshmaillage_prep << "# Nombre de sommets" << endl;
	
	getline(mshmaillage,line);
	getline(mshmaillage,line);
	int numbSommets = stoi(line);
	mshmaillage_prep << numbSommets << endl << "# Coordonnees des sommets" << endl;
	
	for (int i = 0; i < numbSommets; i++){
		getline(mshmaillage,line);
		double a,b,c,d;
		stringstream linestream;
		linestream << line;
		linestream >> a >> b >> c >> d;
		mshmaillage_prep << b << " " << c << " " << d << endl;
	}
	
	mshmaillage_prep << endl << "# Nombre de triangle" << endl;
	
	getline(mshmaillage,line);
	getline(mshmaillage,line);
	getline(mshmaillage,line);
	int numbTri = stoi(line);
	
	double h = 0;
	while (h == 0){
		getline(mshmaillage,line);
		double a,b,c,d,e,f,g;
		stringstream linestream;
		linestream << line;
		linestream >> a >> b >> c >> d >> e >> f >> g >> h;
		numbTri--;
	}
	numbTri++;
	
	mshmaillage_prep << numbTri << endl;
	mshmaillage_prep << "# Numeros des sommets de chaque triangle" << endl;
	
	
	while(line != "$ENDELM"){
		double a,b,c,d,e,f,g;
		stringstream linestream;
		linestream << line;
		linestream >> a >> b >> c >> d >> e >> f >> g >> h;
		if (f < g && g < h){ mshmaillage_prep << f << " " << g << " " << h << endl; }
		if (f < h && h < g){ mshmaillage_prep << f << " " << h << " " << g << endl; }
		if (g < f && f < h){ mshmaillage_prep << g << " " << f << " " << h << endl; }
		if (g < h && h < f){ mshmaillage_prep << g << " " << h << " " << f << endl; }
		if (h < f && f < g){ mshmaillage_prep << h << " " << f << " " << g << endl; }
		if (h < g && g < f){ mshmaillage_prep << h << " " << g << " " << f << endl; }
		getline(mshmaillage,line);
	}
    
	mshmaillage.close();
}