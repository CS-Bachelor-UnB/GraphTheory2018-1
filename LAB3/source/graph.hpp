//bipartile_graph.hpp
//
#ifndef	GRAPH_HPP
#define	GRAPH_HPP
#include "./teacher/teacher.hpp"
#include "./school/school.hpp"
//
class GRAPH
{
public:
	std::vector<TEACHER> teacher;
	std::vector<SCHOOL> school;
	//
	GRAPH(const char* file_name);
	//
private:
	void file_parser(const char* file_name);
};
#endif