//main.cpp
#include "graph.hpp"

int main (int argv, char** argc)
{
	GRAPH g ("/home/ottok92/Documents/UnB/2018-1/GRAFOS/GraphTheory2018-1/LAB3/input.txt");
	g.stable_match();
	g.print();
	return 0;
}
