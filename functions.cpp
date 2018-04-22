#include "solver.hpp"
void Euler (int** T1, int V, int Ver, std::vector<int>& lista, std::stack<int>& stos)
{
	int v, w = V;
	do 
	{
		int ver=0;
		while (T1[w][ver] != 1 && ver < Ver)
		{
			ver++;
		}
		v=ver;
		if(v<Ver)
		{
			T1[v][w] = -1;
			T1[w][v] = -1;
			stos.push(w);
			w=v;
		}
		else
		{
			w=V;
		}
	}while (w!=V);
	lista.push_back(V);
	w = stos.top();
	stos.pop();
	while(w!=V)
	{
		v=0;
		for(int ver = 0; ver<Ver; ver++) if (T1[w][ver]==1) v=1;
		if(v==0)
		{
			lista.push_back(w);
		}
		else
		{
			Euler (T1, w, Ver, lista, stos);
		}
		w=stos.top();	
		stos.pop();
//		for(std::vector<int>::iterator it = lista.begin(); it != lista.end(); it++)  std::cout<<*it<<", ";
//		std::cout<<std::endl;
	}
	lista.push_back(V);
}

void wypisz (std::vector<int>& lista, std::fstream & plikout)
{
	plikout << "   Cykl Hamiltona :	1, ";
    for(std::vector<int>::iterator i = lista.end()-1; i != lista.begin()-1; i--) plikout<< ((* i) +1) << ", ";
    plikout <<endl;
}


void Hamilton(int** T1, int v, int VerNum, std::vector<int>& lista, bool* visited, std::fstream & p2, bool cdn[], bool one)
{
  lista.push_back(v);
  if(lista.size() == VerNum)
  {
    bool test = false;
    
      if(T1[0][lista.back()]== 1)
      {
        test = true;
      }
    if(test) 
	{
		wypisz(lista, p2);
		if(one) cdn[0]=false;
	}
  }
  else
  {
    visited[v] = true;
    for(int i=1; i <VerNum; i++)
    {
    	if(!cdn[0]) return;
    	if(!visited[i] && T1[v][i] ==1 ) Hamilton(T1, i, VerNum, lista, visited, p2, cdn, one);
    }
    visited[v] = false; 
  }
  lista.pop_back();     
}	
