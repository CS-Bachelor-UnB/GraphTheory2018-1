//bipartile_graph.cpp
//
#include <fstream>
#include <cstdio>
#include "graph.hpp"
//
using namespace std;
//
// START_FUNCTIONS	--------------------------------------------------------------------------------------------
//
//////////////////////////////////////////////////////
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
		while (!file.eof())
		{
			getline (file, str_buf, ' ');
			//
			//	TEACHER NODE FOUND:
			if (str_buf.compare (0, 2/*chars*/, "(P") == 0)
			{
				//	START_DATA_COLECTION:
				TEACHER temp_teacher;
				//
				//	GET TEACHER INDEX
				str_buf = str_buf.substr (2, (str_buf.size() - 2));
				temp_teacher.id = atoi(str_buf.c_str());
				str_buf.clear();
				//
				//	GET TEACHER SKILLSET
				getline (file, str_buf, ')');
				temp_teacher.skillset = atoi(str_buf.c_str());
				//
				//	GET PRIORITY QUEU
				for (int i = 0; i < 5; ++i)
				{
					//	TRASH CHARS
					getline (file, str_buf, 'E');
					str_buf.clear();
					//
					//	GET PRIORITIES
					if (i < 4)
						getline (file, str_buf, ',');
					else
						getline (file, str_buf, '\n');
					temp_teacher.availability.push_back (atoi (str_buf.c_str()));
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
	}
	//	FILE.IS_OPEN
	else
	{
		cout << "File could not be open!" << endl;
		exit(2);
	}
}
//
//////////////////////////////////////////////////////