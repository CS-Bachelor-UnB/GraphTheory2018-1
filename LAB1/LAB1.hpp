//LAB1.hpp
#ifndef LAB1_H
#define LAB1_H

#include <algorithm>
#include "network.hpp"	// My rewritten version of it. New parser and all

//######################## START_FUNCTIONS - ABSTRACT ###############################################################################
std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph);	// Creates an adjacency list in the form of vector<list<int>>
void printAdjacencyList(std::vector< std::list< int > > &sourceToPrint);			// Prints the adjacency list of a graph
void printMaxToMinDegree(std::vector<VERTEX> &adjListSource);						// Prints all vertices with regard to their degrees, from max. to min.
std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source);						// Sorts a vector of vertices | auxiliary to printMaxToMinDegree()
int bkSearch(std::vector< std::list<int> > &adjacencyVector, std::list<int> &P, std::list<int> &S, std::list<int> &C); // Bron-Kerbosch implementation
std::list<int> firstNthClique(int degree, std::vector< std::list<int> > &adjacencyVector);	//run bkSearch() until find the first maximal of degree n
std::vector< std::list<int> > maxClique(std::vector< std::list<int> > &adjacencyVector); // stacks cliques. Highest Clique comes last.
//######################## END_FUNCTIONS - ABSTRACT ##################################################################################

//######################## START_DOCOMENTATION #######################################################################################
//------------------------------------------------------------------------------------------------------------------------------------
// std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
// void printAdjacencyList(std::vector< std::list< int > > &sourceToPrint)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
// void printMaxToMinDegree(std::vector< std::list<int> > &adjListSource)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
// std::vector< std::list<int> > sortMaxToMin(std::vector< std::list<int> > &source)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
// int bkSearch(std::vector< std::list<int> > &adjacencyVector, std::list<int> &P, std::list<int> &S, std::list<int> &C)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
// std::list<int> firstNthClique(int degree, std::vector< std::list<int> > &adjacencyVector)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
// std::vector< std::list<int> > maxClique(std::vector< std::list<int> > &adjacencyVector)
//	Parameters:
//
//	Return:
//
//	Functionality:
//
//------------------------------------------------------------------------------------------------------------------------------------
//######################## END_DOCOMENTATION #########################################################################################

//######################## START_REFERENCES ##########################################################################################
// C++ tutorials and functionalities:
// 	https://www.cplusplus.com
// 	https://www.tutorialspoint.com/cplusplus/
// 	https://www.geeksforgeeks.org/cplusplus/
//
// Bron-Kerbosch implementation
//	https://en.wikipedia.org/wiki/Bron–Kerbosch_algorithm
//	https://www.youtube.com/watch?v=132XR-RLNoY
//	https://stackoverflow.com/questions/143140/bron-kerbosch-algorithm-for-clique-finding
//	www.dcs.gla.ac.uk/~pat/jchoco/clique/enumeration/report.pdf
//	https://github.com/NikolasEnt/Clique-Bron-Kerbosch
//######################## END_REFERENCES ##########################################################################################

#endif