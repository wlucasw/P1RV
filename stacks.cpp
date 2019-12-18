//stacks.cpp : définition des fonctions sur les piles

#include "stacks.h"
#include <iostream>
using namespace std;


//push : on rajoute un élément à la pile
void push(stack<int>* ptrS, int a) {
	ptrS->push(a);
};


//pop : on enlève le premier élément de la pile
void pop(stack<int>* ptrS) {
	if (!(ptrS->empty())) {
		ptrS->pop();
	}
};


//add : on sort les deux premières valeurs de la pile, on les additionne et on rajoute la valuer obtenue en haut de la pile
void add(stack<int>* ptrS) {
	int a1, a2;

	if (ptrS->size() > 1) {
		a1 = ptrS->top();
		pop(ptrS);
		a2 = ptrS->top();
		pop(ptrS);
		push(ptrS, a1 + a2);
	}
};


//subtract : on sort les deux premières valeurs de la pile, on les soustrait et on rajoute la valeur obtenue en haut de la pile
void subtract(stack<int>* ptrS) {
	int a1, a2;

	if (ptrS->size() > 1) {
		a1 = ptrS->top();
		pop(ptrS);
		a2 = ptrS->top();
		pop(ptrS);
		push(ptrS, a2 - a1);
	}
};


//multiply : on sort les deux premières valeurs de la pile, on les multiplie et on rajoute la valeur obtenue en haut de la pile
void multiply(stack<int>* ptrS) {
	int a1, a2;

	if (ptrS->size() > 1) {
		a1 = ptrS->top();
		pop(ptrS);
		a2 = ptrS->top();
		pop(ptrS);
		push(ptrS, a2 * a1);
	}
};


//divide : on sort les deux premières valeurs de la pile, on divise la deuxième par la première et on rajoute la valeur obtenue en haut de la pile
void divide(stack<int>* ptrS) {
	int a1, a2;

	if ((ptrS->size() > 1)& (ptrS->top() != 0)) {
		a1 = ptrS->top();
		pop(ptrS);
		a2 = ptrS->top();
		pop(ptrS);
		push(ptrS, a2 / a1);
	}
};


//mod : on sort les deux premières valeurs de la pile, on fait la deuxième modulo la première et on rajoute la valeur obtenue en haut de la pile
void mod(stack<int>* ptrS) {
	int a1, a2;

	if ((ptrS->size() > 1)& (ptrS->top() != 0)) {
		a1 = ptrS->top();
		pop(ptrS);
		a2 = ptrS->top();
		pop(ptrS);
		push(ptrS, a2 % a1);
	}
};


//notP : on remplace le premier élément par un 0 ou par un 1 s'il est déjà égal à 0
void notP(stack<int>* ptrS) {
	if (!(ptrS->empty())) {
		int a;

		if (ptrS->top() == 0) {
			a = 1;
		}
		else {
			a = 0;
		}
		pop(ptrS);
		push(ptrS, a);
	}
};


//greaterP : on sort les deux premières valeurs de la pile, si la deuxième est plus grande que la première, on rajoute un 1, sinon on rajoute un 0
void greaterP(stack<int>* ptrS) {
	int a, a1, a2;

	if (ptrS->size() > 1) {
		a1 = ptrS->top();
		pop(ptrS);
		a2 = ptrS->top();
		pop(ptrS);
		if (a2 > a1) {
			a = 1;
		}
		else {
			a = 0;
		}
		push(ptrS, a);
	}
};


//pointer : on récupère la valeur de l'élément en haut de la pile et on tourne le DP autant de fois dans le sens horaire
void pointer(stack<int>* ptrS, vector<int> position) {
	int a;

	if (!(ptrS->empty())) {
		a = ptrS->top();
		pop(ptrS);
		a = a % 4;
		position.at(2) = (position.at(2) + a + 4) % 4;
	}
};


//switchP : on récupère la valeur de l'élément en haut de la pile et on tourne le CC autant de fois
void switchP(stack<int>* ptrS, vector<int> position) {
	int a;

	if (!(ptrS->empty())) {
		a = ptrS->top();
		pop(ptrS);
		a = a % 2;
		position.at(3) = (position.at(3) - a + 2) % 2;
	}
};


//duplicate : on rajoute sur la pile un élément égal en valeur à celui qui est au sommet de la pile
void duplicate(stack<int>* ptrS) {
	if (ptrS->size() > 0) {
		int a = ptrS->top();
		push(ptrS, a);
	}
};


//recursive : exécute un roll à la profondeur n (on 'enterre' ajout)
void recursive(stack<int>* ptrS, int n, int ajout) {
	if (ptrS->size() >= (n - 1)) {
		if (n == 1) {
			push(ptrS, ajout);
		}
		if (n > 1) {
			int top = ptrS->top();
			pop(ptrS);
			recursive(ptrS, n - 1, ajout);
			push(ptrS, top);
		}
	}
};

//roll : on récupère les deux éléments du dessus de la pile et on "roll" le reste de la pile à une profondeur égale au deuxième élément enlevé, d'un nombre de "roll" égal au premier élément enlevé
void roll(stack<int>* ptrS) {
	int numRolls, n;

	if (ptrS->size() > 1) {
		//on récupère les deux premières valeurs
		numRolls = ptrS->top();
		pop(ptrS);
		n = ptrS->top();
		pop(ptrS);

		//et on execute les rolls
		for (int i = 0; i < numRolls; i = i + 1) {
			int ajout = ptrS->top();
			pop(ptrS);
			recursive(ptrS, n, ajout);
		}
	}
};


//inNum : on rajoute sur la pile un élément égal dont on rentre la valeur au clavier
void inNum(stack<int>* ptrS) {
	int a;
	cout<<"Entrez un entier : "<<endl;
	cin >> a;
	push(ptrS, a);
};


//outNum : on enlève le premier élément de la pile et on l'affiche en entier
void outNum(stack<int>* ptrS) {
	int a;

	if (!(ptrS->empty())) {
		a = ptrS->top();
		pop(ptrS);
		cout << a;
	}
};


//inChar : on rajoute sur la pile un élément égal dont on rentre la valeur au clavier
void inChar(stack<int>* ptrS) {
	char a;
	cout<<"Entrez un caractere : "<<endl;
	cin >> a;
	push(ptrS, int(a));
};


//outChar : on enlève le premier élément de la pile et on l'affiche en caractère
void outChar(stack<int>* ptrS) {
	int a;

	if (!(ptrS->empty())) {
		a = ptrS->top();
		pop(ptrS);
		cout << char(a);
	}
};



void choixAction(stack<int>* ptrS, vector<int> position, int hueChange, int lightnessChange, int nbCodels) {
	switch (hueChange) {
	case 0 :
		switch (lightnessChange) {
		case 1 :
			push(ptrS, nbCodels);
			break;

		case 2 :
			pop(ptrS);
			break;
		}
		break;

	case 1:
		switch (lightnessChange) {
		case 0:
			add(ptrS);
			break;

		case 1:
			subtract(ptrS);
			break;

		case 2:
			multiply(ptrS);
			break;
		}
		break;

	case 2:
		switch (lightnessChange) {
		case 0:
			divide(ptrS);
			break;

		case 1:
			mod(ptrS);
			break;

		case 2:
			notP(ptrS);
			break;
		}
		break;

	case 3:
		switch (lightnessChange) {
		case 0:
			greaterP(ptrS);
			break;

		case 1:
			pointer(ptrS, position);
			break;

		case 2:
			switchP(ptrS, position);
			break;
		}
		break;
	case 4:
		switch (lightnessChange) {
		case 0:
			duplicate(ptrS);
			break;

		case 1:
			roll(ptrS);
			break;

		case 2:
			inNum(ptrS);
			break;
		}
		break;

	case 5:
		switch (lightnessChange) {
		case 0:
			inChar(ptrS);
			break;

		case 1:
			outNum(ptrS);
			break;

		case 2:
			outChar(ptrS);
			break;
		}
		break;
	}
};