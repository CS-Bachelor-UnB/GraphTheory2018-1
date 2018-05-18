//bipartile_graph.cpp
//
#include "graph.hpp"
#include <fstream>
#include <cstdio>
//
using namespace std;
//
// START_FUNCTIONS	--------------------------------------------------------------------------------------------
//
//	Empty Constructor:
GRAPH::GRAPH()
{
	//	do someting
}
//
//////////////////////////////////////////////////////
//	Full Constructor:
GRAPH::GRAPH(const string file_name)
{
	ifstream input_file (file_name, ifstream::in);
	if (input_file.is_open ())
	{
		string str_from_file;
		while (!input_file.eof())
		{
			// write the parser;
		}
	}
}
//
//////////////////////////////////////////////////////
//	Destructor:
GRAPH::~GRAPH()
{
	//	do something
}
//
//////////////////////////////////////////////////////