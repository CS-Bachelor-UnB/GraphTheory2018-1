#include "toposort.hpp"

using namespace std;


GRAPH::GRAPH(void)
{
	this->n_vertices = 0;
}

GRAPH::GRAPH(std::string file_name)
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
	this->adjacency_vector.shrink_to_fit();

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

vector<int> GRAPH::tarjan_toposort(void)
{
	vector<int> result;
	vector<bool> visited(this->adjacency_vector.size(), false);

	for (int i = 0; i < this->incidence_vector.size(); ++i)
		if (this->incidence_vector[i] == 0)
			visit(i, this->adjacency_vector, visited, result);
	return result;

}
// AUX_FUNCTIONS_START -----------------------------------------------------------------------------------------------------------------------------------
void GRAPH::visit (int vertex_in_scope, vector<vector<int>> &adjacency_vector, vector<bool> &visited, vector<int> &result)
{
	// The final path found will be stored in the vector ~visited~
	int size_of_path = 0;
	vector<int> neighbors;

	if (visited[vertex_in_scope] == false)
	{
		neighbors = adjacency_vector[vertex_in_scope];
		for (vector<int>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
			visit ((*it), adjacency_vector, visited, result);
		visited[vertex_in_scope] = true;
		result.insert (result.begin(), vertex_in_scope);
	}
}
// AUX_FUNCTIONS_END --------------------------------------------------------------------------------------------------------------------------------------
vector<int> GRAPH::khan_toposort(void)
{
	vector<int> result;
	vector<int> next;
	vector<int> neighbors;
	vector<int> incidence(this->incidence_vector);

	for (int i = 0; i < incidence.size(); ++i)
		if (incidence[i] == 0)
			next.push_back(i);

	while (!next.empty())
	{
		result.push_back(next.back());
		next.pop_back();

		neighbors = adjacency_vector[result.back()];
		for (int i = 0; i < neighbors.size(); ++i)
		{
			incidence[neighbors[i]] += -1;
			if (incidence[neighbors[i]] == 0)
				next.push_back(neighbors[i]);
		}
	}
	return result;
}