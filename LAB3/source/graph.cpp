//bipartile_graph.cpp
//
#include <fstream>
#include <cstdio>
#include "graph.hpp"
//
#define NUM_TEACHERS 	100
#define NUM_SCHOOLS		50
#define INFINITE		1000

using namespace std;
//
// START_FUNCTIONS	--------------------------------------------------------------------------------------------
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
					// temp_teacher.availability.push_back (atoi (str_buf.c_str()));
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
////////////////////////////////////////////////////////////
//	EXTENDED STABLE MATCH (with indiference) - (GALE-SHAPELY) IRVING'S ALGORITHM[2]:
//	(Weakly Stable)
void GRAPH::stable_match(void)
{
	//	START:
	vector<vector<pair<bool, int>>> school_match (50);		// 	flags which teacher the school has been matched with, teacher's id(not the index in vector) is pair.second
	vector<vector<pair<bool, int>>> teacher_match (100);	//	flags which school the teacher has been matched with, school's id(not the index) is pair.second
	//	PREPARE DATA STRUCTURES:
	prep_data(school_match, teacher_match);
	//
	//	MATCH-MAKING:
	bool all_schools_matched;
	int round = 0;
	for (int i = 0; i < NUM_SCHOOLS; ++i)
	{
		//	> control whether all schools have been matched with 1 teacher (for now):
		//	if one unmatched school is found, it sets the flag to false.
		if (i == 0)
			all_schools_matched = true;
		//
		// if a school still has no teacher assigned:
		if (school_match[i][0].first == false)
		{
			//	> set the control flag:
			all_schools_matched = false;
			//	> find a teacher to whom the school still hasn't made an offer:
			for (int j = 1; j < school_match[i].size(); ++j)
			{
				bool next_teacher = true;
				if (school_match[i][j].first == false)	// has this teacher been proposed to?
				{
					int teacher_index = school_match[i][j].second - 1;
					//
					//	> check and remove any previous match to the current teacher if the current school is more desirable:
					//	  (also, if only one teacher has given availability, make him a match and move on)
					if (teacher_match[teacher_index][0].first == true && round > 0)	//	has a previous matching?
					{
						// bool is_more_desirable 		= true;
						bool is_more_desirable 		= false;	// trying priority queu inversion;
						int current_match_school 	= teacher_match[teacher_index][0].second;
						//
						//	> find out if the school in scope is more desirable than the previous match:
						if (school_match[i].size() < 2)	// if only one teacher has made himself available:
							is_more_desirable = true;
						for (int k = 1; k < teacher_match[teacher_index].size(); ++k)
						{
							//	dealing with the current match:
							if (teacher_match[teacher_index][k].second == current_match_school && is_more_desirable == false)
							{
								is_more_desirable = true;
							}
							else if (teacher_match[teacher_index][k].second == current_match_school && is_more_desirable == true)
							{
								int prev_school_index = current_match_school - 1;
								school_match[prev_school_index][0].first	= false; 
								school_match[prev_school_index][0].second	= 0;
								//	trying - set the teachers flag back to false:
								for (int w = 0; w < school_match[prev_school_index].size(); ++w)
								{
									if (school_match[prev_school_index][w].second == (teacher_index+1))
									{
										school_match[prev_school_index][w].first = false;
										break;
									}
								}
								if (school_match[i].size() > 2)
								break;	
							}
							//
							//	dealing with the new match:
							if ((teacher_match[teacher_index][k].second == (i+1)/*== id of school in scope*/) && (is_more_desirable == false))
								break;
							else if ((teacher_match[teacher_index][k].second == (i+1)) && (is_more_desirable == true))
							{
								//	> set school in scope as the match for the teacher:
								teacher_match[teacher_index][0].first	= true;
								teacher_match[teacher_index][0].second	= (i+1);
								for (int w = 1; w < teacher_match[teacher_index].size(); ++w)
									if (teacher_match[teacher_index][w].second == (i+1))
									{
										teacher_match[teacher_index][w].first = true;
										break;
									}
								//
								//	> flag the current node:	
								teacher_match[teacher_index][k].first	= true;
								//
								// > flag the teacher candidacy in school_match:
								school_match[i][j].first = true;
								//
								//	> flag and point the stability flag in school_match for the current school to the current teacher:
								school_match[i][0].first	= true;
								school_match[i][0].second	= school_match[i][j].second;
								//
								//	> set is_more_desirable as false since a more desirable match has been found:
								is_more_desirable = true;
								next_teacher = false;	
							}
							//
							/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//	IF the PRIORITY QUEU is not inverted by the parser:
							// if ((teacher_match[teacher_index][k].second == current_match_school) && (is_more_desirable == false /*originally true*/))
							// 	break;	// go to next candidate teacher in school_match;
							// //
							// else if ((teacher_match[teacher_index][k].second == current_match_school) && (is_more_desirable == true /*orig. false*/))
							// {
							// 	//	> undo the previous, less desirable match:
							// 	int prev_school_index = current_match_school - 1;
							// 	school_match[prev_school_index][0].first	= false; 
							// 	school_match[prev_school_index][0].second	= 0;
							// 	//	trying - set the teachers flag back to false:
							// 	for (int w = 0; w < school_match[prev_school_index].size(); ++w)
							// 	{
							// 		if (school_match[prev_school_index][w].second == (teacher_index+1))
							// 			school_match[prev_school_index][w].first = false;
							// 	}
							// 	break;
							// }
							// //
							// //
							// if ((teacher_match[teacher_index][k].first == false) && (teacher_match[teacher_index][k].second == (i+1)/*== id of school in scope*/) && (is_more_desirable == false /*orig. true*/))
							// {
							// 	//	> set school in scope as the match for the teacher:
							// 	teacher_match[teacher_index][0].first	= true;
							// 	teacher_match[teacher_index][0].second	= (i+1);
							// 	for (int w = 1; w < teacher_match[teacher_index].size(); ++w)
							// 		if (teacher_match[teacher_index][w].second == (i+1))
							// 		{
							// 			teacher_match[teacher_index][w].first = true;
							// 			break;
							// 		}
							// 	//
							// 	//	> flag the current node:	
							// 	teacher_match[teacher_index][k].first	= true;
							// 	//
							// 	// > flag the teacher candidacy in school_match:
							// 	school_match[i][j].first = true;
							// 	//
							// 	//	> flag and point the stability flag in school_match for the current school to the current teacher:
							// 	school_match[i][0].first	= true;
							// 	school_match[i][0].second	= school_match[i][j].second;
							// 	//
							// 	//	> set is_more_desirable as false since a more desirable match has been found:
							// 	is_more_desirable = true /*orig. false*/;
							// 	next_teacher = false;
							// }
							/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						}// end_of - is school in scope more desirable;
					}// end_of - check and remove any previous....;
					else if (teacher_match[teacher_index][0].first == false)
					{
						//	> set school in scope as the match for the teacher:
						teacher_match[teacher_index][0].first	= true;
						teacher_match[teacher_index][0].second	= (i+1);
						for (int w = 1; w < teacher_match[teacher_index].size(); ++w)
							if (teacher_match[teacher_index][w].second == (i+1))
							{
								teacher_match[teacher_index][w].first = true;
								break;
							}
						//
						// > flag the teacher candidacy in school_match:
						school_match[i][j].first = true;
						//
						//	> flag and point the stability flag in school_match for the current school to the current teacher:
						school_match[i][0].first	= true;
						school_match[i][0].second	= school_match[i][j].second;
						//
						//	> set flag to end the search for a teacher that the school hasn;t made and offer to yet:
						next_teacher = false;
					}
				}// end_of - has the teacher been proposed to;
				if (next_teacher == false)
					break;
			}// end_of - find a teacher to whom the school...;
		}// end_of - if a school still has no teacher assigned;
		//	> check whether all schools have been matched at the end of the round:
		if ((i == (NUM_SCHOOLS - 1)) && (all_schools_matched == true))
			break;
		else if (i == (NUM_SCHOOLS - 1) && (all_schools_matched == false))
		{
			i = 0;	//	go to next round;
			round++;
		}
	}// end_of - bigger loop
}//	end_stable_match();
//
///////////////////////////////////////////////////////////
//	PREPARING DATA STRUCTURES FOR MATCH-MAKING:
void GRAPH::prep_data(vector<vector<pair<bool, int>>> &school_match, vector<vector<pair<bool, int>>> &teacher_match)
{
	//		>populate the vectors to be used in the match-making:
	pair<bool, int> temp_flag (false, INFINITE);
	for (int i = 0; i < NUM_TEACHERS; ++i)
	{
		//	the first node of each teacher will be a flag for stable match found.
		//	> reserving space and setting flag:
		teacher_match[i].reserve(6);
		teacher_match[i].push_back (temp_flag);
		//	> done setting flag;
		//	
		for (int j = 0; j < this->teacher[i].availability.size()/*list of priority*/; ++j)
		{
			// > check whether the teacher in scope meets the criteria to be a canditade for school j:
			if (this->teacher[i].skillset >= this->school[(this->teacher[i].availability[j])-1].required_skillset)
			{
				//	create candidacy for teacher in scope with school j.
				pair<bool, int>	temp_t (false, this->teacher[i].availability[j]);
				teacher_match[i].push_back (temp_t);
				//
				//	since the teachers has interest in some schools in particular, we add the teacher to the list
				//	of possible candidates for the school j. If it's the first addition to the vector,
				//	we also set the stability flag for it.
				//	> check and set flag:
				if (school_match[(this->teacher[i].availability[j])-1/*(school's id)-1 == index in vector*/].empty())
					school_match[(this->teacher[i].availability[j])-1/*(school's id)-1 == index in vector*/].push_back (temp_flag);
				//	> populate school vector if teacher meets criteria:
					pair<bool, int> temp_s (false, i + 1/*(teacher's id) == index in vector + 1*/);
					school_match[(this->teacher[i].availability[j])-1/*(school's id)-1 == index in vector*/].push_back (temp_s);
			}
		}
	}
	//	> instantiate empty nodes (to avoid segmentation fault):
	for (int i = 0; i < NUM_SCHOOLS; ++i)
	{
		if (school_match[i].empty())
		{
			temp_flag.first		= false;
			temp_flag.second	= INFINITE;
			school_match[i].push_back (temp_flag);
		}
	}
	//
	//	SORTING SCHOOL_MATCH based on the number of teachers that have given availability:
	//	- DO SORTING HERE -
	//
	//		at this point, we know that every node in both school_match and teacher_match
	//		has been checked for the skillset criteria, which means that no further checking is
	//		necessary. Furthermore, the priority order in teacher_match has been kept (but inverted for now).
}
///////////////////////////////////////////////////////////
//	MIXIMUM_MATCH - HOPCROFT KARP ALGORITHM[1]:
// https://github.com/vermagav/hopcroft-karp
// vector<pair<int, int>> GRAPH::maximum_match(void)
// {
// 	vector<pair<int, int>> maximum_match;	
// }
//
//////////////////////////////////////////////////////////
//	AUXILIARY METHODS:
//
//	BFS - returns true if there is an augmenting path
// bool GRAPH::bfs(void)
// {

// }
//
//	DFS - adds augmenting path if there is one
// bool GRAPH::dfs(int alpha)
// {

// }
//
//////////////////////////////////////////////////////////
//	BIBLIOGRAPHY
//	[1] HOPCROFT KARP ALGORITHM - https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-1-introduction/
//	[2] GALE-SHAPELY ALGORITHM 	- https://en.wikipedia.org/wiki/Stable_marriage_problem