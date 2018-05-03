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
	sort (this->incidence_vector.begin(), this->incidence_vector.end());
}

vector<vector<int>> GRAPH::tarjan_toposort(void)
{
	vector<int> visited;
	vector<int> to_visit
	vector<int> result_in_scope;
	vector<vector<int>> all_sortings;

	for (int i = 0; i < this->incidence_vector.size(); ++i)
	{
		if (this->incidence_vector[i] == 0)
		{
			to_visit = this->adjacency_vector[i]
			all_sortings.push_back (sort_from (i, this->adjacency_vector, visited, result_in_scope, to_visit));
		}
	}

}

vector<int> GRAPH::sort_from(int vertex_in_scope, vector<vector<int>> &adjacency_vector, vector<int> visited, vector<int> result_in_scope, vector<int> to_visit)
{
	if (to_visit == {})
		return result_in_scope;
	else
	{
		//CONTINUE FROM HERE
		// HERE IS THE RECURSIVE MAGIC, THINK ABOUT IT
	}
}

vector<int> GRAPH::khan_toposort(void)
{

}