//main.cpp

#include <iostream>
#include <stack>
#include <vector>
#include "program.h"
#include "stacks.h"

using namespace std;


int main() { 
	//Chargement de l'image
	program prg("hw6_big.png");

	//Déclarations des variables
		//Pile
	stack<int>* ptrS = new stack<int>;
	
		//Pour se déplacer et exécuter les actions correspondant aux changements de bloc de couleur
			//Pour effectuer les actions sur la pile
	int nbCodelsBloc = 0;
	int hueChange = 0;
	int lightnessChange = 0;
	
			//Coordonnées des pixels, dp, cc et accumulateur pour le parcours
	vector<vector<int>> casesVues(0);
	vector<int> position(4);
	position.at(0) = 2;
	position.at(1) = 2;
	position.at(2) = 0;   //DP
	position.at(3) = 0;   //CC

	int largeurCodel;
	cout << "Combien de pixels pour la largeur d'un codel ?" << endl; 
	cin >> largeurCodel;
	
			//Pour faire les calculs sur les couleurs
	pixel pixelAv, pixelApr;

			//Booléens de cas particuliers et fin de programme
	bool terminate = false;
	bool white = false;
	bool black = false;

	while (!(terminate)) {
		//Parcours du bloc de couleur avec une fonction récursive qui nous donne 1.le nombre de codels et 2.le tableau des codels du bloc (dans casesVues)
		casesVues.clear();
		//cout<<position.at(0)<<" ; "<<position.at(1)<<endl;
		nbCodelsBloc = prg.compt_codel(&position, &casesVues,largeurCodel);
		//cout<<position.at(0)<<" ; "<<position.at(1)<<endl;
		//cout<<nbCodelsBloc<<endl;
		//Calcul du pixel d'après
		pixelAv = prg.Get_image()[position.at(0)][position.at(1)];
		position = prg.nextCodel(&pixelApr, casesVues, position, largeurCodel);
		
		//Test pour voir si le bloc de couleur d'après est pas noir ou blanc
		if (pixelApr.Get_Lightness() == -2) { //le codel où l'interpréteur est arrivé est noir
			black = true;
			int compteur = 1;
			while (black & (compteur < 8)) {//on revient au codel coloré (non noir) précédent
				switch(position.at(2)){
				case 0:
					position.at(1) -= largeurCodel;
					break;
				case 1:
					position.at(0) -= largeurCodel;
					break;
				case 2:
					position.at(1) += largeurCodel;
					break;
				case 3:
					position.at(0) += largeurCodel;
					break;
				}
				//on tourne le cc ou le dp selon lequel on a tourné en dernier (en commençant par le cc)
				if (compteur % 2 == 1) {
					position.at(3) = 1 - position.at(3);
				}
				else {
					position.at(2) = (position.at(2) + 1) % 4;
					//position.at(1) = 1 - position.at(1);
				}
				//met les coordonnées du codel suivant dans position et remet pixelApr à jour à partir du tableau accumulateur et des cc et dp
				position = prg.nextCodel(&pixelApr, casesVues, position,largeurCodel);
				if (pixelApr.Get_Lightness() == -2) {compteur += 1;}
				else {black = false;}
			}
			if (compteur == 8) {
				terminate = true;
			}
		}
		
		if (pixelApr.Get_Lightness() == -3) {//le codel où l'interpréteur est arrivé est blanc
			white = true;
			//on continue tout droit jusqu'à trouver un bloc d'un autre couleur 
			vector<int> position_direction;
			position_direction.push_back(position.at(0));
			position_direction.push_back(position.at(1));
			position_direction.push_back(position.at(2));
			position_direction.push_back(position.at(3));
			vector<vector<int>> casesVues;
			terminate = prg.chemin_block_blanc(&position_direction,casesVues);
			
			position.at(0) = position_direction.at(0);
			position.at(1) = position_direction.at(1);
			position.at(2) = position_direction.at(2);
			position.at(3) = position_direction.at(3);
			pixelApr = prg.Get_image()[position.at(0)][position.at(1)];
		}
		//Si à cette étape l'interpréteur est passé d'un codel coloré à un autre sans passer par un codel blanc, l'interpréteur exécute l'action correspondant au changement de pixel
		if (!(black || white)) {
			//Calcul des différences de couleur et de luminosité
			hueChange = pixelApr.difference_hue(pixelAv);
			lightnessChange = pixelApr.difference_lightness(pixelAv);
			
			//Action sur la pile
			choixAction(ptrS, position, hueChange, lightnessChange, nbCodelsBloc);
		}
		white = false;
	}
	cout << endl << "Au revoir ! (fin du programme)" << endl;
	return(0);
}