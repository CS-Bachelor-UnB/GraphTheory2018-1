//CLASS NETWORK DEFINITION

#ifndef NETWORK_H
#define NETWORK_H

class NETWORK;

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <utility>
	
typedef struct
	{
		int id;
		int degree;
		std::list<std::pair<int, int> > edge;
	}VERTEX;

class NETWORK
{
	public:	//FOR DEBUGGING - CHANGE LATER
		int nvertices;
		int directed;	// 0 = not directed || 1 = directed
		std::vector<VERTEX> vertex;

	public:
		NETWORK(void);
		NETWORK(const char* fileName);
		~NETWORK();
		

	private:
		int findVertices(const char* fileName);
		int findEdges(const char* fileName, std::vector<VERTEX>::iterator vertexIt);//, int vertexId, VERTEX &newNode);
		void populateGraph(const char* fileName);

};

#endif