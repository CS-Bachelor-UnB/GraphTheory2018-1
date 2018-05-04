//main.cpp

#include <ctime>
#include "toposort.hpp"
#include "timer.hpp"

using namespace std;

int main (int argc, char **argv)
{	
	vector<vector<int>> khan;
	vector<vector<int>> tarjan;
	const char *file_name[] = {"./data/top_small.txt", "./data/top_med.txt","./data/top_large.txt","./data/top_huge.txt"};
	vector<string> files (file_name, end(file_name));
	
	clock_t time_end;
	clock_t time_start;
	pair<int, int> t_pair;
	int k_time_elapsed, t_time_elapsed;
	vector<pair<double, double>> time_elapsed;

	for(int i = 0; i < files.size(); ++i)
	{
		{
			GRAPH G(files[i]);
			time_start = clock();
			khan.push_back (G.khan_toposort ());
			time_end = clock();
			k_time_elapsed = (int)(((time_end - time_start) * 1000) / CLOCKS_PER_SEC);
	
			time_start = clock();
			tarjan.push_back (G.tarjan_toposort ());
			time_end = clock();
			t_time_elapsed = (int)(((time_end - time_start) * 1000) / CLOCKS_PER_SEC);
	
			t_pair = make_pair (k_time_elapsed, t_time_elapsed);
			time_elapsed.push_back (t_pair);
		}
	}
}