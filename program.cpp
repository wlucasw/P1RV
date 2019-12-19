
#include "program.h"

program::program(const char* filename){
	vector<unsigned char> lecture;
	unsigned width,height;

	//decode
	unsigned error = lodepng::decode(lecture, width, height, filename);

	//if there's an error, display it
	if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;
	cout<<"hauteur : "<<height<<endl<<"Longueur : "<<width<<endl;
	vector<vector<pixel>> image(height);
	this->width=width;
	this->height=height;

	//Convertion du vecteur lodepng en matrice (vecteur de vecteur) de pixel
	for (int i=0;i<int(height-1);i++){
		for (int j=0;j<int(width-1);j++){
			int R,G,B,A;
			R=int(lecture[4*(i*width+j)]);
			G=int(lecture[4*(i*width+j)+1]);
			B=int(lecture[4*(i*width+j)+2]);
			A=int(lecture[4*(i*width+j)+3]);
			image[i].push_back(pixel(R,G,B,A));
		}
	}

	cout<<"lecture ok"<<endl;
	this->image=image;
};

int program::compt_codel(vector<int> *position,vector<vector<int>> *casesVues,int tailleCodel)
{
	//Définition des différents vecteurs directionnels (haut, bas, gauche, droite)
	vector<int> position1 (2);
	vector<int> position2 (2);
	vector<int> position3 (2);
	vector<int> position4 (2);
	position1.at(0)=(tailleCodel);
	position1.at(1)=(0);
	position2.at(0)=(0);
	position2.at(1)=(tailleCodel);
	position3.at(0)=(-tailleCodel);
	position3.at(1)=(0);
	position4.at(0)=(0);
	position4.at(1)=(-tailleCodel);
	vector<vector<int>> direction;
	direction.push_back(position1);
	direction.push_back(position2);
	direction.push_back(position3);
	direction.push_back(position4);

	//On mémorise la position de la case visitée
	casesVues->push_back(*position);
	int nb_codex=1;

	vector<vector<int>>::iterator it;

	//On cherche dans les voisins directs de la case ceux qu'on a pas déjà comptés
	for (it=direction.begin();it<direction.end();it++)
	{
		vector<int> new_pos; 
		new_pos.push_back(it->at(0) + position->at(0));
		new_pos.push_back(it->at(1) + position->at(1));
		new_pos[0] = min(max(new_pos[0],0),height-2);
		new_pos[1] = min(max(new_pos[1],0),width-2);
		new_pos.push_back(position->at(2));
		new_pos.push_back(position->at(3));
		//On verifie que le voisin est de la bonne couleur
		if (image[new_pos[0]][new_pos[1]] == image[position->at(0)][position->at(1)])
		{
			vector<vector<int>>::iterator vu;
			vu=find(begin(*casesVues),end(*casesVues),new_pos);
			
			//Cas où l'on a pas déjà compté la case 
			if (vu==end(*casesVues))
			{
				//On va chercher dans les voisins directs de la nouvelle case ceux qu'on a pas déjà comptés
				nb_codex+=compt_codel(&new_pos,casesVues,tailleCodel);
			}
		}
		
	}
	
	return nb_codex;
}

bool program::chemin_block_blanc(vector<int> *position_direction,vector<vector<int>> cases_vu)
{
	//On mémorise la case et la direction
	cases_vu.push_back(*position_direction);
	bool fin;

	//On avance en restant dans les blocs blancs
	while (image[position_direction->at(0)][position_direction->at(1)].Get_Hue()==-3)
	{
		switch (position_direction->at(2)) 
		{
			case 0:
					position_direction->at(1) += 1;
					break;
				case 1:
					position_direction->at(0) += 1;
					break;
				case 2:
					position_direction->at(1) -= 1;
					break;
				case 3:
					position_direction->at(0) -= 1;
					break;
		}
	}

	//Cas où à la fin du chemin blanc on s'arrête sur un bloc noir
	if (image[position_direction->at(0)][position_direction->at(1)].Get_Hue()==-2)
	{
		//On recule pour retourner dans le blanc
		switch(position_direction->at(2)){
				case 0:
					position_direction->at(1) -= 1;
					break;
				case 1:
					position_direction->at(0) -= 1;
					break;
				case 2:
					position_direction->at(1) += 1;
					break;
				case 3:
					position_direction->at(0) += 1;
					break;
				}

		//On change la direction
		position_direction->at(2) = (position_direction->at(2) + 1) % 4;
		position_direction->at(3)  = (position_direction->at(3)  + 1 )% 2;

		//On vérifie qu'on est pas déjà passé sur la même case avec la même direction
		vector<vector<int>>::iterator vu;
		vu=find(begin(cases_vu),end(cases_vu),*position_direction);

		//Cas : on est jamais passé par ici
		if (vu==end(cases_vu))
		{
			//On réitère depuis le bloc blanc où on est
			fin=chemin_block_blanc(position_direction,cases_vu);
		}

		//Cas : on est déjà passé par ici
		else 
		{
			//On arrête le programme
			fin = true;
		}
	}

	//Cas où à la fin du chemin blanc on s'arrête sur un bloc non noir
	else
	{
		//On continue le programme hors de la fonction, la nouvelle position est contenu dans le vecteur position_direction
		fin = false;
	}
	return fin;
}

vector<int> program::nextCodel(pixel* pixelApr, vector<vector<int>> casesVues, vector<int> position, int tailleCodel) {
	//On se met dans le bon pixel par rapport au dp et au cc
	vector<vector<int>>::iterator it;
	vector<vector<int>> accumulateur;
	accumulateur.push_back(position);

	switch (position.at(2)) {
	case 0: //le dp pointe à droite
		//on cherche une des cases les plus à droite
		for (it = casesVues.begin(); it < casesVues.end(); it++) {
			if (it->at(1) > accumulateur.at(0)[1]) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else{
				if (it->at(1) == accumulateur.at(0)[1]) {
					accumulateur.push_back(*it);
				}
			}
		}
		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position.at(0) = accumulateur.at(0).at(0);
		position.at(1) = accumulateur.at(0).at(1);
		if (position.at(3) == 0) {//le cc pointe à gauche donc ici, on cherche le codel le plus en haut
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) < position.at(0)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		if (position.at(3) == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus en bas
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) > position.at(0)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}

		//On change de position pour un pixel du bloc d'après
		position.at(1) += tailleCodel;
		position[1] = min(position[1],width-2);
		break;

	case 1: //le dp pointe en bas
		//on cherche une des cases les plus en bas
		for (it = casesVues.begin(); it < casesVues.end(); it++) {
			if (it->at(0) > accumulateur.at(0).at(0)) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else {
				if (it->at(0) == accumulateur.at(0).at(0)) {
					accumulateur.push_back(*it);
				}
			}
		}

		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position.at(0) = accumulateur.at(0).at(0);
		position.at(1) = accumulateur.at(0).at(1);
		if (position.at(3) == 0) {//le cc pointe à gauche donc ici, on cherche le codel le plus à droite
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) > position.at(1)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		if (position.at(3) == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus à gauche
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) < position.at(1)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		
		//On change de position pour un pixel du bloc d'après
		position.at(0) += tailleCodel;
		position[0] = min(position[0],height-2);
		break;

	case 2: //le dp pointe à gauche
		//on cherche une des cases les plus à gauche
		for (it = casesVues.begin(); it < casesVues.end(); it++) {
			if (it->at(1) < accumulateur.at(0)[1]) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else {
				if (it->at(1) == accumulateur.at(0)[1]) {
					accumulateur.push_back(*it);
				}
			}
		}

		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et onchercher celui qui est le plus loin dans celle du cc p/r au DP
		position.at(0) = accumulateur.at(0).at(0);
		position.at(1) = accumulateur.at(0).at(1);
		if (position.at(3) == 0) {//le cc pointe à gauche donc ici, on cherche le codel le plus en bas
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) > position.at(0)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		if (position.at(3) == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus en haut
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(0) < position.at(0)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		
		//On change de position pour un pixel du bloc d'après
		position.at(1) -= tailleCodel;
		position[1] = max(position[1],0);
		break;

	case 3: //le dp pointe en haut
		//on cherche une des cases les plus en bas
		for (it = casesVues.begin(); it < casesVues.end(); it++) {
			if (it->at(0) < accumulateur.at(0).at(0)) {
				accumulateur.clear();
				accumulateur.push_back(*it);
			}
			else {
				if (it->at(0) == accumulateur.at(0).at(0)) {
					accumulateur.push_back(*it);
				}
			}
		}
		//accumulateur a maintenant toutes les cases qui sont le plus loin dans la direction du DP et on cherche celui qui est le plus loin dans celle du cc p/r au DP
		position.at(0) = accumulateur.at(0).at(0);
		position.at(1) = accumulateur.at(0).at(1);
		
		if (position.at(3) == 0) {//le cc pointe à gauche donc ici, on cherche le codel le plus à gauche
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) < position.at(1)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		if (position.at(3) == 1) {//le cc pointe à droite donc ici, on cherche le codel le plus à droite
			for (it = accumulateur.begin(); it < accumulateur.end(); it++) {
				if (it->at(1) > position.at(1)) {
					position.at(0) = it->at(0);
					position.at(1) = it->at(1);
				}
			}
		}
		
		//On change de position pour un pixel du bloc d'après
		position.at(0) -= tailleCodel;
		position[0] = max(position[0],0);
		break;
	}

	//Et on enregistre le pixel du bloc suivant
	*pixelApr = this->image[position.at(0)][position.at(1)];
	return position;
};