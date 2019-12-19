
#include "pixel.h"
#include <vector>
#include "lodepng.h"

class program{
private:

	int width,height;
	vector<vector<pixel>> image;

public:

	//Constructeurs :
	program(const char* filename);

	//Accesseurs 
	int Get_width(){return(width);};
	int Get_height(){return(height);};
	vector<vector<pixel>> Get_image(){return(image);};

	//Fonctions de parcours de l'image
	int compt_codel(vector<int> *position,vector<vector<int>> *case_vu,int tailleCodel);
	bool chemin_block_blanc(vector<int> *position,vector<vector<int>> casesVues);
	vector<int> nextCodel(pixel* pixelApr, vector<vector<int>> casesVues, vector<int> position, int tailleCodel);

};
