#pragma once

#include "pixel.h"
#include <vector>
#include "lodepng.h"

class program {
private:

	int width, height;
	vector<vector<pixel>> image;

public:

	//Constructeurs :
	program(const char* filename);

	//Accesseurs 
	int Get_width() { return(width); };
	int Get_height() { return(height); };
	vector<vector<pixel>> Get_image() { return(image); };

	//Se déplacer pour l'éxécution du programme
	int compt_codel(vector<int> position, vector<vector<int>> case_vu);
	void nextCodel(pixel* pixelApr, int dp, int cc, vector<vector<int>> accumulateur, vector<int> position);
}