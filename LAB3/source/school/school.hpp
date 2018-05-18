//school.hpp

#ifndef SCHOOL_HPP
#define SCHOOL_HPP
#include <iostream>

class SCHOOL
{
public:
	int required_teachers;
	int required_skillset;
public:
	SCHOOL();
	SCHOOL(int teachers,int skills);
	~SCHOOL();
};

#endif