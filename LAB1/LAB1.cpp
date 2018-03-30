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

//######################## DECLARING FUNCTIONS ####################
std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph);		// Creates an adjacency list in the form of vector<list<int>>
void printAdjacencyList(std::vector< std::list< int > > &sourceToPrint);					// Prints the adjacency list of a graph
void printMaxToMinDegree(std::vector<VERTEX> &adjListSource);							// Prints all vertices with regard to their degrees, from max. to min.
std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source);							// Sorts a vector of vertices | auxiliary to printMaxToMinDegree()
int bkSearch(std::vector< std::list<int> > &adjacencyVector, std::list<int> &P, std::list<int> &S, std::list<int> &C); // Bron-Kerbosch implementation
std::list<int> nthClique(int degree, std::vector< std::list<int> > &adjacencyVector);	//run bkSearch() until find the first maximal of degree n
// ###################### MAIN ###################################
int main(int argc, char** argv)
{
	std::vector< std::list<int> > adjacencyV;
	std::list<int> nDegreeClique;
	std::list<int> P;
	std::list<int> S;
	NETWORK G("karate.gml");	
	adjacencyV = buildAdjacencyList(G.vertex);


//	printAdjacencyList(adjacencyV);
//	nDegreeClique = nthClique(5, adjacencyV); 
//	std::cout << bkSearch(adjacencyVector, P, S, nDegreeClique) << "\n\n"; // bkSearch() works!!!

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

int bkSearch(std::vector< std::list<int> > &adjacencyVector, std::list<int> &P, std::list<int> &S, std::list<int> &C)
{	
	std::list<int> neighbors;
	std::list<int> buffer;
	int degree = 0;

	if((P.size() == 0) && (S.size() == 0))
	{
		degree = C.size();
		return degree;
	}
	else
	{
		C.push_back(P.front());
		neighbors = adjacencyVector [(P.front() - 1)];
		P.pop_front(); 

		buffer = intersectionOf(P, neighbors);
		P = buffer;
		buffer.clear();
		buffer = intersectionOf(S, neighbors);
		S = buffer;
		buffer.clear();

		degree = bkSearch(adjacencyVector, P, S, C);
		return degree;
	}
}

std::list<int> nthClique(int degree, std::vector< std::list<int> > &adjacencyVector)	//run bkSearch() until find the first maximal of degree n
{
	int degree_inScope = 0;
	std::list<int> clique;
	std::list<int> allCandidates;
	std::list<int> alreadyVisited;

	for(int i = 0; i < adjacencyVector.size(); ++i)
	{
		allCandidates = adjacencyVector[i];		// create a list with all adjacent vertices of vertice_in_scope
		allCandidates.push_front(i + 1);		// adds the vertice_in_scope to the list
		degree_inScope = bkSearch(adjacencyVector, allCandidates, alreadyVisited, clique);	//calls function to find a maximal clique from vertice_in_scope
		if(degree_inScope == degree)			// checks whether the desired degree has been found
			return clique;						// if so, returns the clique found.
		else
		{
			allCandidates.clear();				// else, it clears the lists to start looking for an nth clique on the vertice next to the vertice_in_scope.
			alreadyVisited.clear();
			clique.clear();
			degree_inScope = 0;
		}
	}
	return {};		// returns empty list if no cliques of nth degree are found.
}