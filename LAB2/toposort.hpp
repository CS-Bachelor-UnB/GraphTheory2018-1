// LAB2 - GraphTheory - Toposort of DACs
#ifndef TOPOSORT_H
#define TOPOSORT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class GRAPH
{
	public:
		int n_vertices;
		std::vector< std::vector<int> > adjacency_vector;
		std::vector<int> incidence_vector;

		GRAPH(void);
		GRAPH(const char* file_name);
		~GRAPH(void);

	private:
		bool populate_graph(std::fstream *file_ptr);

};

#endif