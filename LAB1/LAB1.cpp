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
void printAdjacencyList(adjList &sourceToPrint);
void printMaxToMinDegree(std::vector<VERTEX> &adjListSource);
std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source);

// ###################### MAIN ###################################
int main(int argc, char** argv)
{
	adjList adjacencyList;
	std::list<int> elemList;
	std::list< std::list<int> > graphPowerSet;
	NETWORK graph("karate.gml");	
	
//	adjacencyList = buildAdjacencyList((graph.vertex));
//	std::cout << "\t\tADJACENCY LIST - PRINTING" << std::endl;
//	printAdjacencyList(adjacencyList);
//	std::cout << std::endl;

//	std::cout << "\t\tGRAPH - PRINTING MAX TO MIN" << std::endl;
//	printMaxToMinDegree(graph.vertex);
//	std::cout << std::endl;

//THE FOLLOWING PART IS DOING SOMETHING BUT NOT WHAT I HAD EXPECTED - REDO IT
	// listOfEdges = graph.convertToList();
	for(int i = 0; i < 6; ++i)
		elemList.push_back(i + 1);

	graphPowerSet = graph.powerSetOfGraph(elemList);
	std::cout << "\t\tPOWERSET OF GRAPH - of size " << graphPowerSet.size() << std::endl;
	for(std::list< std::list<int>>::iterator it = graphPowerSet.begin(); it != graphPowerSet.end(); ++it)
	{
		for(auto v : (*it))
		{
			std::cout << v << " ";
		}
		std::cout << std::endl;
	}
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

void printAdjacencyList(adjList &sourceToPrint)
{
	for(unsigned int it = 0; it < sourceToPrint.size(); ++it)
	{
		std::cout << "VERTEX " << (it + 1) << std::endl;
		for(std::list<int>::iterator jt = sourceToPrint[it].begin(); jt != sourceToPrint[it].end(); ++jt)
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

void findMaximalClique(std::vector<int> R, std::vector<int> P, std::vector<int> X);