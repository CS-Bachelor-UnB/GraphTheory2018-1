//teacher.cpp
//
#include "teacher.hpp"
//
using namespace std;
//
// START_FUNCTIONS	--------------------------------------------------------------------------------------------
//
//	Empty Constructor:
TEACHER::TEACHER()
{
	this->skillset			=	 0;
	this->availability.reserve	(0);
	this->evaluations.reserve	(0);
}
//
///////////////////////////////////////////////////////////////
//	Full Constructor:
TEACHER::TEACHER(int skillset, std::vector<int> &availability)
{
	this->skillset = skillset;
	this->availability.reserve (availability.size());
	this->availability	= availability;
}
//
/////////////////////////////////////////////////////////////
//	Destructor:
TEACHER::~TEACHER()
{
	this->availability.clear ();
	this->availability.shrink_to_fit ();

	this->evaluations.clear ();
	this->evaluations.shrink_to_fit ();
}
//
/////////////////////////////////////////////////////////////
// END_FUNCTIONS  	--------------------------------------------------------------------------------------------