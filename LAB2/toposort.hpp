// LAB2 - GraphTheory - Toposort of DACs
#ifndef TOPOSORT_H
#define TOPOSORT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

typedef std::vector< std::vector<int>>  long_vector;

class GRAPH
{
	public:
		int n_vertices;
		long_vector adjacency_vector;
		std::vector<int> incidence_vector;

		GRAPH(void);
		GRAPH(const char* file_name);
		~GRAPH(void);
		long_vector tarjan_toposort(void);
		long_vector khan_toposort(void);

	private:
		void populate_graph(std::fstream &file);
		void difference(std::vector<int> &a, std::vector<int> &b);
		int sort_from(int vertex_in_scope, long_vector &adjacency_vector, std::vector<int> &visited, std::vector<int> &to_visit);
		//std::vector<int> sort_from(int vertex_in_scope, long_vector &adjacency_vector, std::vector<int> visited, std::vector<int> result_in_scope, std::vector<int> to_visit);

};

#endif

// References:
// set_difference() in toposort.cpp: https://goo.gl/U6XHYV