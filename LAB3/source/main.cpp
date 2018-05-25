//main.cpp
#include "graph.hpp"

int main (int argv, char** argc)
{
	GRAPH g ("./input.txt");
	g.stable_match();
	g.print();
	return 0;
}
