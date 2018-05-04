// LAB2 - GraphTheory - Toposort of DACs
#ifndef TOPOSORT_H
#define TOPOSORT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


class GRAPH
{
	public:
		int n_vertices;
		std::vector<int> incidence_vector;
		std::vector<std::vector<int>> adjacency_vector;

		GRAPH(void);
		GRAPH(std::string file_name);
		~GRAPH(void);
		std::vector<int> tarjan_toposort(void);
		std::vector<int> khan_toposort(void);

	private:
		void visit(int vertex_in_scope, std::vector<std::vector<int>> &adjacency_vector, std::vector<bool> &visited, std::vector<int> &result);
		void populate_graph(std::fstream &file);

};

#endif

// References:
// Graph Theory - Trajan's: https://goo.gl/xDfN3J
// Timer function: https://goo.gl/GVhymU