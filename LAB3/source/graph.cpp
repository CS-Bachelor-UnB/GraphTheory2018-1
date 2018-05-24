//bipartile_graph.cpp
//
#include <fstream>
#include <cstdio>
#include "graph.hpp"
//
#define NUM_TEACHERS 	100
#define NUM_SCHOOLS	50
#define INFINITE	1000

using namespace std;
//
//////////////////////////////////////////////////////////
//     SCHOOL Full Constructor:
SCHOOL::SCHOOL(int id, int teachers,int skills)
{
        this->id                = id;
        this->required_teachers = teachers;
        this->required_skillset = skills;
	vector<int> temp (teachers, INFINITE);
	this->assigned_teachers = temp;
}
//
/////////////////////////////////////////////////////////
//	SCHOOL Empty Constructor:
SCHOOL::SCHOOL()
{
	this->id		= INFINITE;
	this->required_teachers	= 0;
	this->required_skillset	= 0;
	this->assigned_teachers.reserve(2);
}
//
/////////////////////////////////////////////////////////
//	SCHOOL Destructor:
SCHOOL::~SCHOOL()
{
	vector<int>().swap (this->assigned_teachers);
}
//
////////////////////////////////////////////////////////
//      TEACHER Full Constructor:
TEACHER::TEACHER(int id, int skillset, std::vector<int> &availability)
{
        this->id                = id;
        this->skillset  	= skillset;
        this->availability.reserve (availability.size());
        this->availability      = availability;
	this->match		= INFINITE;
}
//
///////////////////////////////////////////////////////
//	TEACHER Empty Constructor:
TEACHER::TEACHER()
{
	this->id		= INFINITE;
	this->skillset		= 0;
	this->availability.reserve (5);
	this->match		= INFINITE;
}
//
///////////////////////////////////////////////////////
//	TEACHER Destructor
TEACHER::~TEACHER()
{
	vector<int>().swap (this->availability);
}
//
///////////////////////////////////////////////////////
// GRAPH METHODS_START	-------------------------------
//
//	Full Constructor:
GRAPH::GRAPH(const char* file_name)
{
	file_parser (file_name);
}
//
//////////////////////////////////////////////////////
//	File Parser:
void GRAPH::file_parser(const char* file_name)
{
	this->teacher.reserve (100);
	this->school.reserve (50);
	ifstream file (file_name, ifstream::in);

	if (file.is_open ())
	{
		string str_buf;
		char char_buf[3];
		while (!file.eof())
		{
			file.get (char_buf, 3);
			str_buf = string (char_buf);
			//
			//	TEACHER NODE FOUND:
			if (str_buf.compare (0, 2/*chars*/, "(P") == 0)
			{
				//	START_DATA_COLECTION:
				TEACHER temp_teacher;
				//
				//	GET TEACHER INDEX:
				getline (file, str_buf, ' ');
				str_buf = str_buf.substr (0, (str_buf.size() - 1));
				temp_teacher.id = atoi(str_buf.c_str());
				str_buf.clear();
				//
				//	GET TEACHER SKILLSET:
				getline (file, str_buf, ')');
				temp_teacher.skillset = atoi(str_buf.c_str());
				//
				//	GET PRIORITY QUEU:
				for (int i = 0; i < 5; ++i)
				{
					//	TRASH CHARS
					getline (file, str_buf, 'E');
					str_buf.clear();
					//
					//	GET PRIORITIES:
					if (i < 4)
						getline (file, str_buf, ',');
					else
						getline (file, str_buf, '\n');
					temp_teacher.availability.insert (temp_teacher.availability.begin(), atoi (str_buf.c_str()));	//	trying insert front, perhaps more trials for matching will run?
					str_buf.clear();
				}
				// END_DATA_COLECTION;
				//
				//	POPULATE NODE IN GRAPH:
				this->teacher.push_back (temp_teacher);
			}
			//
			//	SCHOOL NODE FOUND:
			else if (str_buf.compare (0, 2/*chars*/, "(E") == 0)	//	school node found!
			{
				//	START DATA COLECTION:
				SCHOOL temp_school;
				//
				//	GET SCHOOL INDEX:
				getline (file, str_buf, ')');
				temp_school.id = atoi (str_buf.c_str());
				str_buf.clear();
				//
				//	TRASH CHARS
				getline (file, str_buf, '(');
				str_buf.clear();
				//
				//	GET SCHOOL REQUIRED SKILLSET:
				getline (file, str_buf, ')');
				temp_school.required_skillset = atoi (str_buf.c_str());
				str_buf.clear();
				//
				//	TRASH CHARS
				getline (file, str_buf, '(');
				str_buf.clear();
				//
				//	GET SCHOOL REQUIRED TEACHERS:
				getline (file, str_buf, '\n');
				temp_school.required_teachers = atoi (str_buf.c_str());
				str_buf.clear();
				//	END DATA COLECTION;
				//
				//	POPULATE NODE IN GRAPH:
				this->school.push_back (temp_school);
				vector<int> temp (temp_school.required_teachers, INFINITE);
				this->school.back().assigned_teachers = temp;
			}
			//
			//	COMMENT (OR EMPTY LINE?)
			else
			{
				getline (file, str_buf, '\n');
				str_buf.clear();
			}
		}//	FILE.EOF
		file.close ();
		//
	}
	//	FILE.IS_OPEN
	else
	{
		cout << "File could not be open!" << endl;
		exit(2);
	}
}
//
////////////////////////////////////////////////////////////
//	STABLE MATCH - (GALE-SHAPELY) 
void GRAPH::stable_match(void)
{
	int current 		= 0;
	int vacancy		= 0;
	bool all_matched 	= true;
	bool first_run		= true;
	while (true)	{
		if ((vacancy <= this->school[current].required_teachers -1) && (this->school[current].assigned_teachers[vacancy] == INFINITE))	{
			all_matched = false;
			//	look for available teacher that meets skill requirement:
			bool next_teacher = true;
			for (int scope = 0; scope < NUM_TEACHERS; scope++)	{
				//	check if school is in teacher's priority queu:
				vector<int>::iterator it = find (this->teacher[scope].availability.begin(), this->teacher[scope].availability.end(), this->school[current].id);
				if (it != this->teacher[scope].availability.end())	{	
						//	check for previous matchings and define whether current school is more desirable:
					if (this->teacher[scope].match != INFINITE)	{
						if  (true)	{
						//	is current school more desirable?:
							if (it >  find (this->teacher[scope].availability.begin(), this->teacher[scope].availability.end(), this->teacher[scope].match) && !first_run) {
								this->school[this->teacher[scope].match -1].assigned_teachers[vacancy] = INFINITE;
								this->school[current].assigned_teachers[vacancy] = this->teacher[scope].id;
								this->teacher[scope].match = this->school[current].id;
								next_teacher = false;
							}
						}
						//
					} else	{	// teacher has no previous matching:
						this->teacher[scope].match = this->school[current].id;
						this->school[current].assigned_teachers[vacancy] = this->teacher[scope].id;
						next_teacher = false;
					}
				} // end: skillset requirement check;
					if (next_teacher == false)	{
						break;	}
			} // end: look for available teacher;
		}  // end: if school[current] has no teacher assigned;
		//	CONTROL UNIT:
			if (current < NUM_SCHOOLS -1)	{
				current++;	// go to next school;
			} else if (all_matched == true && vacancy == 0)	{
				vacancy++;	// fill up second vacancy in schools;
				current = 0;	// start next matching round;
				first_run = false;
			} else	if (all_matched != true)	{
				current = 0;
				all_matched = true;
				first_run = false;
			} else	{
				break;
			}

	}	
}
//	BIBLIOGRAPHY
//	[1] HOPCROFT KARP ALGORITHM - https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-1-introduction/
//	[2] GALE-SHAPELY ALGORITHM 	- https://en.wikipedia.org/wiki/Stable_marriage_problem
