#include "solver.hpp"

using namespace std;

int main()
{
//deklaracje wstêpne
	std::string p, p2, p3, Line;
	int InsType, VerNum, Edges, V1, V2, ile, i=0;
	float Sat;	
	time_t start, stop, tim;
//	double ;
	bool Automat, one;
//POBRANIE WARUNKÓW ANALIZY<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//pobranie danych o plikach wejœciwym i wyjœciowym
	std::cout<<"podaj œcierzkê pliku instancji"<<std::endl;
	std::cin>>p;
	std::cout<<"podaj œcierzkê pliku wyjœciowego"<<std::endl;
	std::cin>>p2;
	std::cout<<"podaj œcierzkê pliku czasów"<<std::endl;
	std::cin>>p3;	
	std::cout<<"podaj typ wprowadzanej instancji:"<<std::endl<<"1. Macierz Sasiedztwa"<<std::endl<<"2. Macierz Incydencji"<<std::endl<<"3. Lista s¹siedztwa"<<std::endl;
	std::cin>>InsType;
	std::cout<<"Czy instancja zawiera wlasciwy zapis danych dodatkowych: (liczba wierzcholkow saturacja)";
	std::cin>>Automat;
	std::cout<<"Czy wystarczy jeden cykl hamiltona?";
	std::cin>>one;
//	std::cout<<"ile instancji wczytaæ?";
//	std::cin>>ile;
//otwarcie plików wejœcia i wyjscia
	std::fstream PlikIn, PlikOut, PlikTimes;
	PlikIn.open(p.c_str(), std::ios::in);
	PlikOut.open(p2.c_str(), std::ios::app);
	PlikTimes.open(p3.c_str(), std::ios::app);
	if (Automat)
	{
		PlikIn>>VerNum>>Sat;
		cout<<endl<<VerNum<<" "<<Sat<<endl;
	}
	else
	{
		std::cout<<"podaj liczbe wierzcholkow"<<std::endl;
		std::cin>>VerNum;
		std::cout<<"podaj nasycenie"<<std::endl;
		std::cin>>Sat;
	}
//	for(int ille = 0 ; ille<ile; ille++)
//	while (!PlikIn.eof())
//	{
// pobranie danych o instancji
//	cout<<"1";
// inicjalizacja grafu
	int** Graf = new int* [VerNum];
	for (int ver=0; ver<VerNum; ver++)
	{
		Graf[ver]=new int [VerNum];
		for(int ver2 = 0 ; ver2<VerNum; ver2++)
		{
			Graf[ver][ver2] = 0;
		}
	}
	PlikTimes<<VerNum;
//TRANSLATOR GRAFU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	switch(InsType)
	{
		case 1://macierz s¹siedztwa
			{
				for (int ver=0 ; ver<VerNum; ver++)
				{
					for(int ver2 = 0 ; ver2<VerNum; ver2++)
					{
						int a=0;
						PlikIn>>a;
						if (a>0) 
						{
							Graf[ver][ver2] = 1;
						}
						else
						{
							Graf[ver][ver2] = 0;
						}
					}
				}
			}
			break;
		case 2:// macierz Incydencji
			{
				Edges = (VerNum * (VerNum - 1))/2 * Sat;
				int** grafpom = new int* [VerNum];
				for (int ver=0 ; ver <VerNum; ver++)
				{
					grafpom[ver] = new int [Edges];
					for (int edge = 0 ; edge< Edges; edge++)
					{
						PlikIn>>grafpom[ver][edge];
//						cout<<grafpom[ver][edge];					
					}
//					std::cout<<std::endl;
				}
//				std::cout<<std::endl;
//				std::cout<<std::endl;
//				std::cout<<std::endl;
				for (int edge = 0 ; edge<Edges; edge++)
				{
					for (int ver = 0; ver<VerNum; ver++)
					{
						if (grafpom[ver][edge] == 1)
						{
							if (i==1)
							{
								V2=ver;
								i = 0;
							} 
							else
							{
								V1=ver;
								i = 1;
							}
						}
					}
//					std::cout<<V1<<" "<<V2<<std::endl;
//					std::cout<<std::endl;
					
					Graf[V1][V2] = 1;
					Graf[V2][V1] = 1;
				}
				for(int ver = 0; ver<VerNum; ver++) delete[] grafpom[ver];
				delete[] grafpom;
			}
			break;
		case 3: //lita incydencji
			{
				for (int ver = 0; ver<VerNum; ver++)
				{
					std::string a, b, c;
					getline(PlikIn, Line);
					for (int ver2 = 0; ver2< VerNum; ver2++)
					{
						std::ostringstream os ("");
						os<<" "<<ver2;
						a = os.str();
						os<<" "<<ver2;
						b = os.str();
						os<<" "<<ver2<<" ";
						c = os.str();
						if (Line.find(a) != string::npos || Line.find(b) != string::npos || Line.find(c) != string::npos )
						{
							Graf[ver][ver2] = 1;
							Graf[ver2][ver] =1;
						}
						
					}
				}
				break;
			}
		}
		
		int**GrafCopy = new int* [VerNum];
		for(int ver=0;ver<VerNum;ver++) 
		{
			GrafCopy[ver] = new int [VerNum];
			for(int v2 = 0; v2<VerNum; v2++) GrafCopy[ver][v2]=Graf[ver][v2];
		}
		std::stack <int> stos;
		std::vector<int> lista;
		start = clock();
		Euler (GrafCopy, 0, VerNum, lista, stos);
		stop = clock();
		PlikOut<<"Cykl Euera:	";		
		for(std::vector<int>::iterator it = lista.begin(); it != lista.end(); it++)  PlikOut<<(*it)+1<<", ";
		PlikOut<<std::endl;
		PlikTimes<<"	"<<stop-start;
		lista.clear();
		for(int ver=0;ver<VerNum;ver++) for(int v2 = 0; v2<VerNum; v2++) GrafCopy[ver][v2]=Graf[ver][v2];
		bool* visited = new bool [VerNum];
		for(int i=0;i<VerNum;i++)visited[i]=false;
		start = clock();
		bool cdn[1]={true};
		Hamilton (GrafCopy, 0, VerNum, lista, visited, PlikOut, cdn, one);
		PlikTimes<<"	"<<clock()-start<<endl;
		for (int i =0; i<VerNum; i++)
		{
			delete[] Graf[i];
			delete[] GrafCopy[i];
		}
		delete[] Graf;
		delete[] GrafCopy;
		delete[] visited;
//		}
	return 0;
	}
