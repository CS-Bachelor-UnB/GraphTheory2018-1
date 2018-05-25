//bipartile_graph.hpp
//
#ifndef	GRAPH_HPP
#define	GRAPH_HPP
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
//
using namespace std;
//
class SCHOOL
{
public:
        int id;
        int required_teachers;
        int required_skillset;
	vector<int> assigned_teachers;	// teachers' ids;
public:
        SCHOOL();
        SCHOOL(int id, int teachers,int skills);
        ~SCHOOL();
};
//
class TEACHER
{
public:
        int                     id;
        int                     skillset;		// == habilitações
	int 			match;			// school's id
        std::vector<int>	availability;           // == escolas onde gostaria de atuar
        //
public:
        TEACHER();
        TEACHER(int id, int skillset, std::vector<int> &availability);
        ~TEACHER();
};
//
class GRAPH
{
public:
	vector<TEACHER> teacher;
	vector<SCHOOL> school;
	//
	GRAPH(const char* file_name);
	void stable_match(void);
	void print(void);
	//
private:
	void file_parser(const char* file_name);
};
//
#endif
