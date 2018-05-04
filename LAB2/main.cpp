//main.cpp

#include "toposort.hpp"

using namespace std;

int main (int argc, char **argv)
{
	GRAPH G("./data/top_small.txt");
	G.tarjan_toposort();
}