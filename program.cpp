
#include "program.h"
#include <algorithm>
using namespace std;

program::program(const char* filename){
	vector<unsigned char> lecture;
	unsigned width,height;

	//decode
	unsigned error = lodepng::decode(lecture, width, height, filename);

	//if there's an error, display it
	if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
	cout<<lecture.size()<<endl;
	cout<<width*height*4<<endl;
	vector<vector<pixel>> image(height);
	this->width=width;
	this->height=height;
	//cout<<image.size()<<endl;
	for (int i=0;i<height-1;i++){
		for (int j=0;j<width-1;j++){
			int R,G,B,A;
			R=int(lecture[4*(i*width+j)]);
			G=int(lecture[4*(i*width+j)+1]);
			B=int(lecture[4*(i*width+j)+2]);
			A=int(lecture[4*(i*width+j)+3]);
			image[i].push_back(pixel(R,G,B,A));
		}
	}
	this->image=image;
};


int position1[] = { 0,1 };
int position2[] = { 0,-1 };
int position3[] = { -1,0 };
int position4[] = { 1,0 };
vector<int> position1v(position1, position1 + sizeof(position1) / sizeof(int));
vector<int> position2v(position2, position2 + sizeof(position2) / sizeof(int));
vector<int> position3v(position3, position3 + sizeof(position3) / sizeof(int));
vector<int> position4v(position4, position4 + sizeof(position4) / sizeof(int));
vector<int> positions[] = { position1v,position2v,position3v,position4v };
vector<vector<int>> direction(positions, positions + sizeof(positions) / sizeof(int));

int program::compt_codel(vector<int> position, vector<vector<int>> case_vu) {
	int nb_codex = 1;

	case_vu.push_back(position);
	vector<vector<int>>::iterator it;
	bool fin = true;
	for (it = direction.begin(); it < direction.end(); it++)
	{
		vector<int> new_pos(2, 0);
		new_pos = *it;
		new_pos[0] += min(max(position[0], 0), width);
		new_pos[1] += min(max(position[1], 0), height);
		vector<vector<int>>::iterator vu;
		vu = find(begin(case_vu), end(case_vu), position);
		if (vu == end(case_vu))
		{
			nb_codex += compt_codel(new_pos, case_vu);
			fin = false;
		}
	}
	return nb_codex;
};


void program::nextCodel(pixel* pixelApr, int dp,int cc, vector<vector<int>> cases_vues, vector<int> position) {
	//On se met dans le bon pixel p/r au dp et cc
	vector<vector<int>>::iterator it;
	vector<vector<int>> accumulateur;
	accumulateur.push_back(position);

	switch (dp) {
	case 0: //le dp pointe à droite
		//on cherche une des cases les plus à droite
		for (it = cases_vues.begin(); it < cases_vues.end(); it++) {
			if (it->at(1) > accumulateur[0][1]) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else{
				if (it->at(1) == accumulateur[0][1]) {
					accumulateur.push_back(*it);
				}
			}
		}

		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position = accumulateur[0];
		if (cc == 1) {//le cc pointe à gauche donc ici, on cherche le codel le plus en haut
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) < position[0]) {
					position = *it;
				}
			}
		}
		if (cc == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus en bas
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) > position[0]) {
					position = *it;
				}
			}
		}
		
		//On change de position pour un pixel du bloc d'après
		position.at(1) += 1;
		break;

	case 1: //le dp pointe en bas
		//on cherche une des cases les plus en bas
		for (it = cases_vues.begin(); it < cases_vues.end(); it++) {
			if (it->at(0) > accumulateur[0][0]) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else {
				if (it->at(0) == accumulateur[0][0]) {
					accumulateur.push_back(*it);
				}
			}
		}

		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position = accumulateur[0];
		if (cc == 1) {//le cc pointe à gauche donc ici, on cherche le codel le plus à droite
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) > position[1]) {
					position = *it;
				}
			}
		}
		if (cc == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus à gauche
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) < position[1]) {
					position = *it;
				}
			}
		}

		//On change de position pour un pixel du bloc d'après
		position.at(0) += 1;
		break;

	case 2: //le dp pointe à gauche
		//on cherche une des cases les plus à gauche
		for (it = cases_vues.begin(); it < cases_vues.end(); it++) {
			if (it->at(1) < accumulateur[0][1]) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else {
				if (it->at(1) == accumulateur[0][1]) {
					accumulateur.push_back(*it);
				}
			}
		}

		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position = accumulateur[0];
		if (cc == 1) {//le cc pointe à gauche donc ici, on cherche le codel le plus en bas
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) > position[0]) {
					position = *it;
				}
			}
		}
		if (cc == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus en haut
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) < position[0]) {
					position = *it;
				}
			}
		}
		
		//On change de position pour un pixel du bloc d'après
		position.at(1) -= 1;
		break;

	case 3: //le dp pointe en haut
		//on cherche une des cases les plus en bas
		for (it = cases_vues.begin(); it < cases_vues.end(); it++) {
			if (it->at(0) < accumulateur[0][0]) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else {
				if (it->at(0) == accumulateur[0][0]) {
					accumulateur.push_back(*it);
				}
			}
		}

		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position = accumulateur[0];
		if (cc == 1) {//le cc pointe à gauche donc ici, on cherche le codel le plus à gauche
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) < position[1]) {
					position = *it;
				}
			}
		}
		if (cc == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus à droite
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) > position[1]) {
					position = *it;
				}
			}
		}
		
		//On change de position pour un pixel du bloc d'après
		position.at(0) -= 1;
		break;
	}

	//Et on enregistre le pixel du bloc suivant
	*pixelApr = this->image[position.at(0)][position.at(1)];
};