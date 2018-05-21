//bipartile_graph.hpp
//
#ifndef	GRAPH_HPP
#define	GRAPH_HPP
#include "./teacher/teacher.hpp"
#include "./school/school.hpp"
#include <utility>
//
class GRAPH
{
public:
	std::vector<TEACHER> teacher;
	std::vector<SCHOOL> school;
	//
	GRAPH(const char* file_name);
	// std::vector<std::pair<int, int>> maximum_match(void);
	void stable_match(void);
	//
private:
	void file_parser(const char* file_name);
};
#endif