#pragma once

#include <iostream>
using namespace std;

class pixel{
private :

	int R,G,B,A,Hue,Ligthness;

public:

	//Constructeurs
	pixel();
	pixel(int R,int G,int B,int A);

	//Accesseurs 
	int Get_R(){return(R);};
	int Get_G(){return(G);};
	int Get_B(){return(B);};
	int Get_A(){return(A);};
	int Get_Lightness(){return(Ligthness);};
	int Get_Hue(){return(Hue);};

	//Setters
	void Set_R(int R){this->R=R;};
	void Set_G(int G){this->G=G;};
	void Set_B(int B){this->B=B;};
	void Set_A(int A){this->A=A;};

	//Affiche
	void Affiche(ostream &f);

	// comparaison de pixel
	bool same(pixel p2);
	int difference_lightness(pixel p2);
	int difference_hue(pixel p2);

	//surcharge
	bool operator==(pixel p2);
	int operator-(pixel p2);
	int operator/(pixel p2);
};

ostream& operator<<(ostream& f,pixel p);