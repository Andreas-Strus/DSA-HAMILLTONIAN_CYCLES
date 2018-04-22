#ifndef solver_hpp
#define solver_hpp
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <math.h>
#include <vector>
#include <stack>

using namespace std;

void Euler (int** T1, int V, int Ver, std::vector<int>& lista, std::stack<int>& stos);
void wypisz (std::vector<int>& lista, std::fstream & plikout);
void Hamilton(int** T1, int v, int VerNum, std::vector<int>& lista, bool* visited, std::fstream & p2, bool cdn[], bool one = true);

#endif
