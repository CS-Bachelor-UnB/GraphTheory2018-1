// Otto Kristian von Sperling
// MAT: 12/0131510
// Lucas M. L.
//MAT: xx/xxxxxxx
//###############################################################
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include "network.hpp"	// My rewritten version of it. New parser and all

typedef std::vector< std::list<int> > adjList; //Adjacency list disregarding the edge's weight
// In this program, 2 types of djacency list will be used.
// The simple one being a vector of lists of ints std::vector<list<pair<int, int>>>
// The complex one being a vector of struct VERTEX due to the likely use of weighted graphs in future projects.

//######################## DEFINING FUNCTIONS ####################
adjList buildAdjacencyList(std::vector<VERTEX> &sourceGraph);
std::list< std::list< int > > get_adjList(NETWORK &graph);
void printAdjacencyList(std::list< std::list< int > > &sourceToPrint);
void printMaxToMinDegree(std::vector<VERTEX> &adjListSource);
std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source);
std::list< std::list< int > > powerGraph(std::list<int> &source);
bool isConnected(std::list<int> candidate, std::list< std::list<int> > graph);
std::list< std::list<int> > allMaximalCliques(NETWORK &graph);

// ###################### MAIN ###################################
int main(int argc, char** argv)
{
	std::list< std::list<int> > adjacencyList;
	std::list< std::list<int> > graphPowerSet;
	NETWORK graph("karate.gml");	
	
	adjacencyList = get_adjList(graph);
	std::cout << "\t\tADJACENCY LIST - PRINTING" << std::endl;
	printAdjacencyList(adjacencyList);

	return 0;
}

// ######################## FUNCTIONS ############################
adjList buildAdjacencyList(std::vector<VERTEX> &sourceGraph)
{
	try
	{
		adjList newAdjList((sourceGraph.size()));

		for(std::vector<VERTEX>::iterator it = sourceGraph.begin(); it != sourceGraph.end(); ++it) // goes through the vector for each vertex
		{

			for(std::list< std::pair< int, int > >::iterator jt = (*it).edge.begin(); jt != (*it).edge.end(); ++jt) // goes through the list for each edge
			{
				newAdjList[((*it).id) - 1].push_back((*jt).first);	//makes first link	v1 --> v2
				newAdjList[((*jt).first) - 1].push_back((*it).id);	//makes second link	v2 --> v1
			}
		}
		return newAdjList;
	}
	catch(std::exception e)
	{
		throw e.what();
	}
}

void printAdjacencyList(std::list< std::list<int> > &sourceToPrint)
{
	int i= 0;
	for(std::list< std::list<int>>::iterator it = sourceToPrint.begin(); it != sourceToPrint.end(); ++it)
	{
		++i;
		std::cout << "VERTEX " << i << std::endl;
		for(std::list<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt)
		{
			std::cout << "\tEDGE TO " << (*jt) << std::endl;
		}
	}
}

std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source)
{
	std::vector<VERTEX> middleMan = source;
	std::vector<VERTEX>::iterator it = middleMan.begin();

	try
	{
		std::sort(middleMan.begin(), middleMan.end(), [](const VERTEX& left, const VERTEX& right)
		{
			return left.degree > right.degree;	// SORTING THE VECTOR WITH AN IMPLICIT LAMBDA FUNCTION
		});
		return middleMan;
	}
	catch(std::exception e)
	{
		throw e.what();
	}
	//returns adjacency list from a sorted set of vector<VERTEX>
}

void printMaxToMinDegree(std::vector<VERTEX> &adjListSource)
{
	std::vector<VERTEX> toPrint = sortMaxToMin(adjListSource);
	try
	{
		for(std::vector<VERTEX>::iterator it = toPrint.begin(); it != toPrint.end(); ++it)
		{
			std::cout << "VERTEX " << (*it).id << std::endl;
			for(std::list< std::pair< int, int > >::iterator jt = (*it).edge.begin(); jt != (*it).edge.end(); ++jt)
			{
				std::cout << "\t\tTARGET " << (*jt).first << " | WEIGHT " << (*jt).second << std::endl;
			}
			std::cout << std::endl;
		}
		toPrint.clear();
	}
	catch(std::exception e)
	{
		throw e.what();
	}
}
std::list< std::list< int > > get_adjList(NETWORK &graph)	// auxiliar function in finding maximal and maximum cliques
{
	try
	{
		std::vector< std::list< int > > list((graph.vertex.size()) + 1);
		std::list< std::list< int > > listToReturn;

		// Converts from VERTEX to vector of lists
		for(std::vector<VERTEX>::iterator it = graph.vertex.begin(); it != graph.vertex.end(); ++it) // goes through the vector for each vertex
		{

			for(std::list< std::pair< int, int > >::iterator jt = (*it).edge.begin(); jt != (*it).edge.end(); ++jt) // goes through the list for each edge
			{
				list[((*it).id) - 1].push_back((*jt).first);	//makes first link	v1 --> v2 | only 1 representative link will be made btw nodes
				list[((*jt).first) - 1].push_back((*it).id);	//makes second link	v2 --> v1
			}
		}

		// Converts from vector of lists to list of lists | it will be needed when getting the power sets of the graph
		for(std::vector<std::list< int > >::iterator it = list.begin(); it != list.end(); ++it)
		{
			listToReturn.push_back((*it));
		}
		return listToReturn;
	}
	catch(std::exception e)
	{
		throw e.what();
	}
}

std::list< std::list< int > > powerGraph(std::list<int> &source) //return all possible sub-graphs of source
{

	std::list< std::list<int> > smaller;
	std::list< std::list<int> > allOfThem;
	std::list< std::list<int> > withElement;
	std::list<int> buffer;
	std::list<int> element;

	if(source.size() == 0)
		return {{}};
	else
	{
		element = {source.front()};	// saves first element
		source.pop_front();	//removes from list
		for(std::list<int>::iterator it = source.begin(); it != source.end(); ++it) // iterate through the remaining list
		{
			buffer = element;
			buffer.insert(buffer.end(), it, source.end());	//for each sublist, it pairs with the initial element
			withElement.push_back(buffer);		//adds to the list of all solutions with the previously removed element
		}
		smaller.splice(smaller.end(), powerGraph(source)) ;	//does the same recursively to the sublist
		allOfThem.splice(allOfThem.end(), withElement);
		allOfThem.insert(allOfThem.end(), smaller.begin(), smaller.end());
		allOfThem.push_back(element);
		return allOfThem;
	}
}

bool isConnected(std::list<int> candidate, std::vector< std::list<int> > graph)
{	
	for(std::list<int>::iterator it = candidate.begin(); it != candidate.end(); ++it)
	{
		for(std::list<int>::iterator jt = candidate.begin(); jt != candidate.end(); ++jt)
		{
			if(jt != it)
			{
				if(std::find(graph[(*it)].begin(), graph[(*it)].end(), (*jt)) == graph[(*it)].end())
				{
					return false;
				}
			}
		}
	}
	return true;
}

std::list< std::list<int> > allMaximalCliques(NETWORK &graph)
{
	std::vector< std::list<int> > adjacencyList = buildAdjacencyList(graph.vertex);
	std::list< std::list<int> > powerG;
	std::list< std::list<int> > allCliques;
	std::list<int> buffer;

	for(int i = 0; i < graph.nvertices; ++i)	//initializing a list with all the nodes represented
	{											// required for creating the powergraph
		buffer.push_back(i + 1);
	}
	powerG = powerGraph(buffer);				//powerGraph created

	for(std::list< std::list<int> >::iterator it = powerG.begin(); it != powerG.end(); ++it)
	{
		if(isConnected((*it), adjacencyList))
		{
			allCliques.push_back((*it));
			for(auto v : allCliques.back())
				std::cout << v << std::endl;
		}
	}
	return allCliques;
}