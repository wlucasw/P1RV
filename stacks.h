#pragma once
#include <stack>
#include <vector>

using namespace std;

void push(stack<int>* ptrS, int a);

void pop(stack<int>* ptrS);

void add(stack<int>* ptrS);

void subtract(stack<int>* ptrS);

void multiply(stack<int>* ptrS);

void divide(stack<int>* ptrS);

void mod(stack<int>* ptrS);

void notP(stack<int>* ptrS);

void greaterP(stack<int>* ptrS);

void pointer(stack<int>* ptrS, int* ptrDP);

void switchP(stack<int>* ptrS, int* ptrCC);

void duplicate(stack<int>* ptrS);

void recursive(stack<int>* ptrS, int n, int ajout);
void roll(stack<int>* ptrS);

void inNum(stack<int>* ptrS);

void outNum(stack<int>* ptrS);

void inChar(stack<int>* ptrS);

void outChar(stack<int>* ptrS);



void choixAction(stack<int>* ptrS, vector<int> position, int hueChange, int lightnessChange, int nbCodels);