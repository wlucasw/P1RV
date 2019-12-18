#include "pixel.h"

pixel::pixel(int R,int G,int B,int A){
	this->R=int(R);
	this->G=int(G);
	this->B=int(B);
	this->A=int(A);

	Ligthness=-1;
	Hue=-1;
	if (R==255 && G==192 && B==192 && A==255){
		Ligthness=1;
		Hue=1;
	}
	if (R==255 && G==255 && B==192 && A==255){
		Ligthness=1;
		Hue=2;
	}
	if (R==192 && G==255 && B==192 && A==255){
		Ligthness=1;
		Hue=3;
	}
	if (R==192 && G==255 && B==255 && A==255){
		Ligthness=1;
		Hue=4;
	}
	if (R==192 && G==192 && B==255 && A==255){
		Ligthness=1;
		Hue=5;
	}
	if (R==255 && G==192 && B==255 && A==255){
		Ligthness=1;
		Hue=6;
	}
	if (R==255 && G==0 && B==0 && A==255){
		Ligthness=2;
		Hue=1;
	}
	if (R==255 && G==255 && B==0 && A==255){
		Ligthness=2;
		Hue=2;
	}
	if (R==0 && G==255 && B==0 && A==255){
		Ligthness=2;
		Hue=3;
	}
	if (R==0 && G==255 && B==255 && A==255){
		Ligthness=2;
		Hue=4;
	}
	if (R==0 && G==0 && B==255 && A==255){
		Ligthness=2;
		Hue=5;
	}
	if (R==255 && G==0 && B==255 && A==255){
		Ligthness=2;
		Hue=6;
	}
	if (R==192 && G==0 && B==0 && A==255){
		Ligthness=3;
		Hue=1;
	}
	if (R==192 && G==192 && B==0 && A==255){
		Ligthness=3;
		Hue=2;
	}
	if (R==0 && G==192 && B==0 && A==255){
		Ligthness=3;
		Hue=3;
	}
	if (R==0 && G==192 && B==192 && A==255){
		Ligthness=3;
		Hue=4;
	}
	if (R==0 && G==0 && B==192 && A==255){
		Ligthness=3;
		Hue=5;
	}
	if (R==192 && G==0 && B==192 && A==255){
		Ligthness=3;
		Hue=6;
	}
	if (R==0 && G==0 && B==0 && A==255){
		Ligthness=-2;
		Hue=-2;
	}
	if (R==255 && G==255 && B==255 && A==255){
		Ligthness=-3;
		Hue=-3;
	}
	if (Ligthness==-1 || Hue==-1){
		cout<<"---pas piet---"<<endl;
		cout<<*this<<endl;
	}

};

void pixel::Affiche(ostream &f){
		f<<"Rouge : "<<R<<endl;
		f<<"Vert : "<<G<<endl;
		f<<"Bleu : "<<B<<endl;
		f<<"Alpha : "<<A<<endl;
		f<<"Hue : "<<Hue<<endl;
		f<<"Lightness : "<<Ligthness<<endl;
	};

bool pixel::same(pixel p2){
	return(Hue==p2.Get_Hue() && Ligthness==p2.Get_Lightness());
};

int pixel::difference_hue(pixel p2){
	return((Hue-p2.Get_Hue())%6);
};

int pixel::difference_lightness(pixel p2){
	return((Ligthness-p2.Get_Lightness())%3);
};

bool operator==(pixel p,pixel p2){
	return(p.same(p2));
};

int operator-(pixel p,pixel p2){
	return(p.difference_hue(p2));
};

int operator/(pixel p,pixel p2){
	return(p.difference_hue(p2));
};

ostream& operator<<(ostream& f,pixel p){
	p.Affiche(f);
	return(f);
};