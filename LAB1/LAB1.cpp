#include "LAB1.hpp"


std::vector< std::list<int> > buildAdjacencyList(std::vector<VERTEX> &sourceGraph)
{
	try
	{
		std::vector< std::list<int> > newAdjList((sourceGraph.size()));

		for(std::vector<VERTEX>::iterator it = sourceGraph.begin(); it != sourceGraph.end(); ++it) // goes through the vector for each vertex
		{
			(*it).degree = 0;	// reseting vertices degree transform it from directed to undirected(bilateral) graph

			for(std::list< std::pair< int, int > >::iterator jt = (*it).edge.begin(); jt != (*it).edge.end(); ++jt) // goes through the list for each edge
			{
				newAdjList[((*it).id) - 1].push_back((*jt).first);	//makes first link	v1 --> v2
				(*it).degree++;										// registering yet another edge(degree++)
				newAdjList[((*jt).first) - 1].push_back((*it).id);	//makes second link	v2 --> v1
				sourceGraph[(*jt).first - 1].degree++;				// registering yet another edge(degree++)
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
	std::vector<VERTEX> buffer = sortMaxToMin(adjListSource);
	//std::vector< std::list<int> > toPrint = buildAdjacencyList(buffer);
	try
	{
		for(std::vector<VERTEX>::iterator it = buffer.begin(); it != buffer.end(); ++it)
		{
			std::cout << "VERTEX " << (*it).id << "\t|-> DEGREE = " << (*it).degree << std::endl;
		}
		buffer.clear();
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

std::list<int> firstNthClique(int degree, std::vector< std::list<int> > &adjacencyVector)	//run bkSearch() until find the first maximal of degree n
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

std::vector< std::list<int> > maxClique(std::vector< std::list<int> > &adjacencyVector)
{
	int degree_inScope = 0;
	std::list<int> higherDegree;
	std::list<int> clique;
	std::list<int> allCandidates;
	std::list<int> alreadyVisited;
	std::vector< std::list<int> > maxClique;

	for(int i = 0; i < adjacencyVector.size(); ++i)
	{
		allCandidates = adjacencyVector[i];		// create a list with all adjacent vertices of vertice_in_scope
		allCandidates.push_front(i + 1);		// adds the vertice_in_scope to the list
		degree_inScope = bkSearch(adjacencyVector, allCandidates, alreadyVisited, clique);	//calls function to find a maximal clique from vertice_in_scope
		
		if(degree_inScope >= higherDegree.back())			// checks whether the new degree found is higher than the previous one
		{
			higherDegree.push_back(degree_inScope);			// if so, stack it
			maxClique.push_back(clique);					// and stack the clique;
		}

		allCandidates.clear();				// it clears the lists to start looking for an nth clique on the vertice next to the vertice_in_scope.
		alreadyVisited.clear();
		clique.clear();
		degree_inScope = 0;
	}
	return maxClique;	// at the end of the loop, the highest degree cliques are stacked and can be returned.
}

bool obeys_Ores(std::vector<std::list<int>> &adjacency_vector)
{
	std::list<int>::iterator jt;
	std::list<int> all_candidates, buffer;
	std::vector<std::list<int>> non_adjacent;
	std::vector<std::list<int>>::iterator it;

	// START_FIND non-adjacent list
	for(it = adjacency_vector.begin(); it != adjacency_vector.end(); ++it) 
	{
		for(int i = 1; i <= adjacency_vector.size(); ++i) // populates list with all possible vectors
		{
			if(std::find((*it).begin(), (*it).end(), i) == (*it).end())	// if vertice i is not found the adjacency list of current vertice
				buffer.push_back(i);
		}
		non_adjacent.push_back(buffer);
		buffer.clear();
	}
	// END_FIND non-adjacent list

	// START_CHECK Ore's Theorem | d|v1| + d|v2| >= Vn --> Hamiltonian Graph
	for(int i = 0; i < non_adjacent.size(); ++i)
	{
		jt = non_adjacent[i].begin();
		while(jt != non_adjacent[i].end())
		{
			if((adjacency_vector.size() > (adjacency_vector[i].size() + adjacency_vector[(*jt) - 1].size())) && (((*jt) - 1) != i))
			{
				std::cout << "\tOre's Theorem is broken between vertices " << (i + 1) << " and " << (*jt) << std::endl;
				return false;
			}
			jt++;
		}
		return true;
	}
}