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
std::list<int> intersectionOf(std::list<int> a, std::list<int> b);					// finds the intersection of two lists
std::list<int> firstNthClique(int degree, std::vector< std::list<int> > &adjacencyVector);	//run bkSearch() until find the first maximal of degree n
std::vector< std::list<int> > maxClique(std::vector< std::list<int> > &adjacencyVector); // stacks cliques. Highest Clique comes last.
//######################## END_FUNCTIONS - ABSTRACT ##################################################################################

//######################## START_DOCOMENTATION #######################################################################################
//------------------------------------------------------------------------------------------------------------------------------------
// std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph)
//	Parameters:
//		sourceGraph 		-	reference to the member vertex of type vector<VERTEX> from class NETWORK, which is the blueprint for
//								a graph object.
//	Return:
//		vector<list<int>> 	-	returns a vector which references to all vertices of object graph and contains for each vertex
//								a list<int> of all adjacent vertices.
//	Functionality:	
//							-	1. creates a new empty vector<list<int>> to be the adjacency list
//								2. points to the beginning of sourceGraph and creates loop to cover it till the end
//								3. points to the begining of each list<pair<int, int>> cointaned in the vertex under scope and loops till
//								   end of the list<pair<int, int>>
//								4. pushes every first element of pair<int, int>, wich is adjacent node, and ignore the second, which
//								   is supposed to be the weight of that edge. It also makes sure to register in the field "degree" of
//								   each "VERTEX" under scope the new link found.
//								5. returns the new adjacency list created
//------------------------------------------------------------------------------------------------------------------------------------
// void printAdjacencyList(std::vector< std::list< int > > &sourceToPrint)
//	Parameters:
//		sourceToPrint		-	reference to the adjacency list of the graph in scope
//	Return:
//		void
//	Functionality:
//							-	1. points to the first vertex of the adjacency list and loops until it reaches the end
//								2. points to the beginning of the list<int> cointained in the vertex in scope and loops until the end
//								3. prints the counter to the vertex and the elements within list<int>
//------------------------------------------------------------------------------------------------------------------------------------
// void printMaxToMinDegree(std::vector<VERTEX> &adjListSource)
//	Parameters:
//		adjListSource		-	reference to the member "vertex" of the graph in scope
//	Return:
//		void
//	Functionality:
//							-	1. calls sortMaxToMin() on the adjacency list
//								2. prints the vertex and it's degree after sorted
//------------------------------------------------------------------------------------------------------------------------------------
// std::vector<VERTEX> sortMaxToMin(std::vector<VERTEX> &source)
//	Parameters:
//		source 				-	reference to the member "vertex" of the graph in scope of the graph in scope
//	Return:
//		vector<VERTEX>		-	returns the sorted vector with respect to "vertex.degree"
//	Functionality:
//							-	1. points the the beginning of "source"
//								2. copies content onto new vector to be sorted.
//								3. calls std::sort() with an implicit lambda funtion for sorting
//										lambda - compares member "degree" of object
//								4. returns sorted vector
//------------------------------------------------------------------------------------------------------------------------------------
// int bkSearch(std::vector< std::list<int> > &adjacencyVector, std::list<int> &P, std::list<int> &S, std::list<int> &C)
//	Parameters:
//		adjacencyVector 	-	reference to the adjacency list of the graph in scope
//		P 					-	all adjacent vertices to the vertex in scope
//		S 					-	all previously visited vertices
//		C 					-	all elegible vertices to form a clique
//	Return:
//		int 				-	returns the degree of the clique found
//	Functionality:
//							-	1. checks whether P and S are empty, which means that a clique has been found;
//								   if so returns the degree of that clique, which is now stored in "C"
//								2. 
//									2.1 if clique not found, adds the current vertex to possible cliques ("C");
//								    2.2 adds its adjacent vertices to "P" - all vertices that need checking;
//									2.3 removes the vertex in scope from "P" because it's being checked at the moment
//								3. 
//									3.1 gets the intersection of all elements in "P" and adjacents to the current vertex in scope
//										in other words, removes from "P" the elements which are not adjacent to the vertex in scope
//									3.2 does the same as the previous step to "S", elements visited
//								4. calls recursively bkSearch() with the new parameters established. In other words, it checks the
//								   next depth of vertices.
//								5. symbolically returns degree, which serves only to tell function to backtrack because a clique has
//								   not yet been found
//------------------------------------------------------------------------------------------------------------------------------------
// std::list<int> intersectionOf(std::list<int> a, std::list<int> b)
//	Parameters:
//		a 					-	first list to be compared
//		b 					-	second list to be compared
//	Return:
//		std::list<int> 		-	returns the intersection of both lists
//	Functionality:
//							-	1. sorts both lists before comparing, with list::sort()
//								2. finds the intersection of both lists with std::intersection()
//								3. returns a new list with such intersection
//------------------------------------------------------------------------------------------------------------------------------------
// std::list<int> firstNthClique(int degree, std::vector< std::list<int> > &adjacencyVector)
//	Parameters:
//		degree 				-	desired degree of clique to be found
//		adjacencyVector 	-	adjacency list of graph in scope
//	Return:
//		std::list<int>		-	returns the first clique of degree n found in the graph
//	Functionality:
//							-	1. loads the adjacency list of the vertex in scope
//								2. calls bkSearch() for the vertex in scope
//								3. if desired clique is found, return it
//								4. otherwise, cleans variables and proceeds to the next vertex(loop)
//								5. if it reaches the end of all vertices, it returns an empty list
//------------------------------------------------------------------------------------------------------------------------------------
// std::vector<std::list<int>> maxClique(std::vector< std::list<int> > &adjacencyVector)
//	Parameters:
//		adjacencyVector 	-	adjacency list of graph in scope
//	Return:
//		std::vector<std::list<int>>
//							-	returns vector with all cliques of maximum degree.
//	Functionality:
//							-	1. loads the adjacency list of the vertex in scope
//								2. calls bkSearch() and stores the degree of the clique found for further comparisson
//								3. if the degree found is higher than the one previously stored, it stacks the degree and the clique
//								   otherwise, it just moves on to the next vertex, cleaning all temporary variables first
//								4. returns the stack of cliques sorted. The maximum clique(s) is(are) always on top.
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