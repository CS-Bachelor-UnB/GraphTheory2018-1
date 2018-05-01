//CODING CLASS NETWORKING

#include "network.hpp"

using namespace std;

int NETWORK::findVertices(const char* fileName)
{
	fstream file;
	file.open(fileName, std::fstream::in);

	if(file.is_open() && !file.eof())
	{
		string strFromFile;
		int countVertex = 0;

		while(!file.eof())
		{
			getline(file, strFromFile);	// read the gml file until "node is found"
			if((strFromFile.find("node") != string::npos))
			{
				getline(file, strFromFile); // get brackets
				getline(file, strFromFile); // get id line
				strFromFile.erase(0, 6);	//cleans data, keeps only node ID
				VERTEX newNode = {std::stoi(strFromFile), 0};	//creates new node type struct VERTEX with identified ID and 0 degree
				this->vertex.push_back(newNode);
				countVertex++;
			}
		}
		file.close();
		return countVertex;
	}
	else
	{
		throw "Unable to access file for reading | NUM OF VERTICES";
	}
}

int NETWORK::findEdges(const char* fileName, vector<VERTEX>::iterator vertexIt)//int vertexId, VERTEX &newNode)
{
	std::fstream file;
	file.open(fileName, std::fstream::in);

	if(file.is_open() && !file.eof())
	{
		string lookForSource("    source ");				// creates a token to  
		lookForSource.append(to_string((*vertexIt).id));	// find edges originated from the current node
		string strFromFile;		//string to read from gml file
		int countEdge = 0;
		pair<int, int> newEdge;	// new edge has fields target and weight

		while(!file.eof())
		{
			getline(file, strFromFile);
			if((strFromFile.find("edge") != string::npos))	// read the gml file until edge is found
			{
				//GET SOURCE VRETEX ID FROM FILE
				getline(file, strFromFile);	// first bracket
				getline(file, strFromFile);	// source id
				if(strFromFile.compare(lookForSource) == 0)	// if the edge found in the file has source == current node
				{
					getline(file, strFromFile);	//then get the target id
					strFromFile.erase(0, 11);	// clean up the data, keep only target ID
					newEdge = make_pair (std::stoi(strFromFile), 1);	//edges's target and weight(in this case always 1)
					(*vertexIt).edge.push_back(newEdge);	// add the new edge to the list of edges of the current node
					++countEdge;

				}
			}
		}
		file.close();
		return countEdge;
	}
	else
	{
		throw "Unable to access file for reading | NUM OF EDGES";
	}	
}

void NETWORK::populateGraph(const char* fileName)
{
	for(vector<VERTEX>::iterator it = this->vertex.begin(); it != this->vertex.end(); ++it)
	{
		(*it).degree = this->findEdges(fileName, it);
	}
}


NETWORK::NETWORK (void)
{
	nvertices = 0;
	directed = 0;
}

NETWORK::NETWORK (const char* fileName)
{
		this->directed = 0;
		this->nvertices = this->findVertices(fileName);
		populateGraph(fileName);
}

NETWORK::~NETWORK()
{
	for(std::vector<VERTEX>::reverse_iterator it = this->vertex.rbegin(); it != this->vertex.rend(); ++it)
	{
		(*it).edge.clear();	
	}
	this->vertex.clear();
}