// Otto Kristian von Sperling
// MAT: 12/0131510
// Lucas Miranda
//MAT: xx/xxxxxxx
//###############################################################
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include "network.hpp"	// My rewritten version of it. New parser and all

// OBS 1. --------- Adjacency Lists ------------------------------
// Two types of adjacency list are present in the software.
// One represented by a vector<list<int>>
// The other as a list<list<int>>
// This is due some diverse applications of each, which were more suitable for some but not all cases.
// Thus, taking advantage of the best tools at hand seemed reasonable.
// ---------------------------------------------------------------

//######################## DEFINING FUNCTIONS ####################
std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph);		// Creates an adjacency list in the form of vector<list<int>>
void printAdjacencyList(std::vector< std::list< int > > &sourceToPrint);					// Prints the adjacency list of a graph
void printMaxToMinDegree(std::vector<VERTEX> &adjListSource);							// Prints all vertices with regard to their degrees, from max. to min.
std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source);							// Sorts a vector of vertices | auxiliary to printMaxToMinDegree()
void bkSearch(std::vector< std::list<int> > &adjList, std::list<int> &P, std::list<int> &S, std::list<int> &C);
// ###################### MAIN ###################################
int main(int argc, char** argv)
{
	std::list<int> possibleCliques;
	std::list<int> allCandidates;
	std::list<int> alreadyVisited;
	std::vector< std::list<int> > adjacencyVector;
	NETWORK G("karate.gml");	

	adjacencyVector = buildAdjacencyList(G.vertex);
//	printAdjacencyList(adjacencyVector);
	for(int i = 5; i < G.nvertices; ++i)
	{
		allCandidates.push_back(i + 1);
	}

	std::cout << bkSearch(adjacencyVector, allCandidates, alreadyVisited, possibleCliques) << "\n" << std::endl;
	for(auto v : possibleCliques)
		std::cout << v << std::endl;

	return 0;
}

// ######################## FUNCTIONS ############################
std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph)
{
	try
	{
		std::vector< std::list<int> > newAdjList((sourceGraph.size()));

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

void printAdjacencyList(std::vector< std::list<int> > &sourceToPrint)
{
	int i= 0;
	for(std::vector< std::list<int>>::iterator it = sourceToPrint.begin(); it != sourceToPrint.end(); ++it)
	{
		std::cout << "VERTEX " << (i + 1) << std::endl;
		for(std::list<int>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt)
		{
			std::cout << "\tEDGE TO " << (*jt) << std::endl;
		}
		++i;
		if((i + 1) == sourceToPrint.size())	// just to avoid printing an extra non-existing vertex
			break;							
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

std::list<int> intersectionOf(std::list<int> a, std::list<int> b)
{
	std::list<int> out;

	a.sort();
	b.sort();
	std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(out));
	return out;

}

void bkSearch(std::vector< std::list<int> > &adjList, std::list<int> &P, std::list<int> &S, std::list<int> &C)
{	
	std::list<int> neighbors;
	std::list<int> buffer;

	if((P.size() == 0) && (S.size() == 0))
	{
		break;
	}
	else
	{
		C.push_back(P.front());
		neighbors = adjList [(P.front() - 1)];
		P.pop_front(); 

		buffer = intersectionOf(P, neighbors);
		P = buffer;
		buffer.clear();
		buffer = intersectionOf(S, neighbors);
		S = buffer;
		buffer.clear();

		bkSearch(adjList, P, S, C);

	}

}

void nthClique()	//run bkSearch() until find the first maximal of degree n
{

}