//MAIN
#include "LAB1.hpp"

int main(int argc, char** argv)
{
	int s_case = 0;
	std::list<int> nDegreeClique;
	NETWORK G("karate.gml");	
	std::vector< std::list<int> > adjacencyV;
	std::vector< std::list<int> > maximumCliques;
	
	 adjacencyV = buildAdjacencyList(G.vertex);
	 //maximalCliques = maxClique(adjacencyV);
	// for(auto v : nDegreeClique)
	// 	std::cout << v << " ";
	// std::cout << std::endl;
//	printAdjacencyList(adjacencyV);
	
	std::cout << "\t\tGRAPH THEORY - CLIQUES\n1. PRINT adjacency list\t\t\t2. PRINT highest to lowest degree vertices\n";
	std::cout << "3. PRINT (all) maximum clique(s)\t4. PRINT first nth degree clique\n";
	std::cin >> s_case;
	switch(s_case)
	{
		default:
			return 0;
		
		case 1:
			printAdjacencyList(adjacencyV);
			break;
		
		case 2:
			printMaxToMinDegree(G.vertex);
			break;

		case 3:
			maximumCliques = maxClique(adjacencyV);
			std::cout << "\n\t\tALL MAXIMUM CLIQUES\n";
			for(std::vector< std::list<int> >::iterator it = maximumCliques.begin(); it != maximumCliques.end(); ++it)
			{
				std::cout << "\tDegree " << (*it).size() << " |-->  ";
				for(auto c : (*it))
					std::cout << c << "  ";
				std::cout << std::endl;
			}
			break;

		case 4:
			int desiredDegree = 0;
			std::cout << "\n\t\tNth DEGREE CLIQUE\nWhich degree should be found? -> ";
			std::cin >> desiredDegree;
			
			nDegreeClique = firstNthClique(desiredDegree, adjacencyV);
			if(nDegreeClique.size() == 0)
				std::cout << "\nDEGREE NOT FOUND!";
			else
				for(auto c : nDegreeClique)
					std::cout << c << " ";
			std::cout << "\n";
			break;

	}


	return 0;
}
