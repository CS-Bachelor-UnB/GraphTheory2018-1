#include "toposort.hpp"

using namespace std;

GRAPH::populate_graph(fstream *file_ptr);

GRAPH::GRAPH(void)
{
	this->n_vertices = 0;
}

GRAPH::GRAPH(const char* file_name)
{
	fstream file (file_name, fstream::in);
	file_ptr.is_open() ? this->populate_graph(file) : cout << "\nCouldn't open file for reading...\n";
	file_ptr.close();
}

GRAPH::~GRAPH(void)
{
	for(auto v : this->adjacency_vector)
	{
		v.clear();
		v.shrink_to_fit();
	}
	
	this->incidence_vector.clear();
	this->incidence_vector.shrink_to_fit();
}

GRAPH::populate_graph(fstream *file_ptr)
{
	string str_from_file;
	int vertices = 0;
	int in_scope = 0;
	int target = 0;

	// get the size of graph from file:
	getline(file_ptr, str_from_file);
	vertices = stoi(str_from_file)
	this->n_vertices = vertices;
	
	// initializing vectors to avoid out_of_bound exceptions
	 this->adjacency_vector.resize(vertices);
	 this->incidence_vector.resize(vertices, 0);
	// for(int i = 0; i < n_vertices; ++i)
	// {
	// 	this->adjacency_vector.push_back([0]);
	// 	this->incidence_vector.push_back(0);
	// }

	// read from file
	while(!file_ptr.eof())
	{
		getline(file_ptr, str_from_file, ' ');
		in_scope	=	stoi(str_from_file);
		getline(file_ptr, str_from_file);
		target		=	stoi(str_from_file);

		this->adjacency_vector[in_scope].push_back(target);
		this->incidence_vector[target] += 1;
	}
}