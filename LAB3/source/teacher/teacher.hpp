//Teacher.hpp

#ifndef TEACHER_HPP
#define TEACHER_HPP
#include <iostream>
#include <vector>
#include <string>

class TEACHER
{
public:
	int 										id;
	int											skillset;			// == habilitações
	std::vector<int>							availability;		// == escolas onde gostaria de atuar
	// std::vector<std::pair<int, std::string>> 	evaluations;		// pair(int grade, string date)

public:
	TEACHER();
	TEACHER(int id, int skillset, std::vector<int> &availability);
	~TEACHER();
	
};
#endif