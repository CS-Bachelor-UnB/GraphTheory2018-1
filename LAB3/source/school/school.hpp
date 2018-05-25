//school.hpp

#ifndef SCHOOL_HPP
#define SCHOOL_HPP
#include <iostream>

class SCHOOL
{
public:
	int id;
	int required_teachers;
	int required_skillset;
public:
	SCHOOL();
	SCHOOL(int id, int teachers,int skills);
	~SCHOOL();
};

#endif