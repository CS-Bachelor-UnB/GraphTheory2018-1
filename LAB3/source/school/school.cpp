//school.cpp

#include "school.hpp"

// START_FUNCTIONS	--------------------------------------------------------------------------------------------
//
//	Empty Constructor:
SCHOOL::SCHOOL()
{
	this->required_teachers	=	0;
	this->required_skillset	=	0;
}
//
//////////////////////////////////////////////////////////
//	Full Constructor:
SCHOOL::SCHOOL(int teachers,int skills)
{
	this->required_teachers	=	teachers;
	this->required_skillset	=	skills;
}
//
/////////////////////////////////////////////////////////
//	Destructor:
SCHOOL::~SCHOOL()
{
	//	do nothing?
}
//
////////////////////////////////////////////////////////
// END_FUNCTIONS	--------------------------------------------------------------------------------------------