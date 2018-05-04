#include "toposort.hpp"

using namespace std;


GRAPH::GRAPH(void)
{
	this->n_vertices = 0;
}

GRAPH::GRAPH(const char* file_name)
{
	fstream file (file_name, fstream::in);
	file.is_open() ? this->populate_graph(file) : throw ("\nCouldn't open file for reading...\n");
	file.close();
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

void GRAPH::populate_graph(fstream &file)
{
	string str_from_file;
	int vertices = 0;
	int in_scope = 0;
	int target = 0;

	// get the size of graph from file:
	getline(file, str_from_file);
	vertices = stoi(str_from_file);
	this->n_vertices = vertices;
	
	// initializing vectors to avoid out_of_bound exceptions
	 this->adjacency_vector.resize(vertices);
	 this->incidence_vector.resize(vertices, 0);
	// read from file
	while(!file.eof())
	{
		getline(file, str_from_file, ' ');
		in_scope	=	stoi(str_from_file);
		getline(file, str_from_file);
		target		=	stoi(str_from_file);

		this->adjacency_vector[in_scope].push_back(target);
		this->incidence_vector[target] += 1;
	}
}

vector<vector<int>> GRAPH::tarjan_toposort(void)
{
	int size_path = 0;
	vector<int> to_visit;
	vector<int> result_in_scope;
	vector<vector<int>> all_sortings;

	for (int i = 0; i < this->incidence_vector.size(); ++i)
	{
		if (this->incidence_vector[i] == 0)
		{
			to_visit = this->adjacency_vector[i];
			size_path = sort_from (i, this->adjacency_vector, result_in_scope, to_visit);
			all_sortings.push_back (result_in_scope);
			result_in_scope.clear();
		}
	}
	return all_sortings;

}
// AUX_FUNCTIONS_START -----------------------------------------------------------------------------------------------------------------------------------
int GRAPH::sort_from(int vertex_in_scope, vector<vector<int>> &adjacency_vector, vector<int> &visited, vector<int> &to_visit)
{
	// The final path found will be stored in the vector ~visited~
	int size_of_path = 0;

	if (to_visit.empty())
	{
		size_of_path = visited.size();
		return size_of_path;
	}
	else
	{
		visited.push_back(vertex_in_scope);
		to_visit.insert (to_visit.end(), adjacency_vector[vertex_in_scope].begin(), adjacency_vector[vertex_in_scope].end()); // append
		difference (to_visit, visited);
		size_of_path = sort_from (to_visit.back(), adjacency_vector, visited, to_visit);
		return size_of_path;
	}
}

void GRAPH::difference(vector<int> &a, vector<int> &b)
{
	// removes all elements of a from b
	a.erase( remove_if( begin(a),end(a),
    [&](int x){return find(begin(b),end(b),x)!=end(b);}), end(a));

}
// AUX_FUNCTIONS_END --------------------------------------------------------------------------------------------------------------------------------------
vector<vector<int>> GRAPH::khan_toposort(void)
{

}