//main.cpp

#include <ctime>
#include "toposort.hpp"
#include "gnuplot_i.hpp"

using namespace std;

void save_to_file(vector<pair<int, int>> source);
void wait_for_key (void);

int main (int argc, char **argv)
{	
	vector<vector<int>> khan;
	vector<vector<int>> tarjan;
	const char *file_name[] = {"./data/top_small.txt", "./data/top_med.txt","./data/top_large.txt","./data/top_huge.txt"};
	vector<string> files (file_name, end(file_name));
	
	clock_t time_end;
	clock_t time_start;
	pair<int, int> t_pair;
	const string to_plot = "./to_plot.dat";
	float k_time_elapsed, t_time_elapsed;
	vector<pair<int, int>> time_elapsed;

	for(int i = 0; i < files.size(); ++i)
	{
		{
			GRAPH G(files[i]);
			time_start = clock();
			khan.push_back (G.khan_toposort ());
			time_end = clock();
			k_time_elapsed = (float)(((time_end - time_start) * 1000000)/ CLOCKS_PER_SEC);	// 10^(-6) seconds = microsecond
			t_pair = make_pair (khan[i].size(), k_time_elapsed);
			time_elapsed.push_back (t_pair);

			time_start = clock();
			tarjan.push_back (G.tarjan_toposort ());
			time_end = clock();
			t_time_elapsed = (float)(((time_end - time_start) * 1000000) / CLOCKS_PER_SEC);	// 10^(-6) seconds = microsecond
			t_pair = make_pair (tarjan[i].size(), t_time_elapsed);
			time_elapsed.push_back (t_pair);
		}
	}
	save_to_file (time_elapsed);

	string title = "Toposort Benchmark - Otto von Sperling";
	Gnuplot plot("points");
	
	//plot.set_xlogscale (10);
	//plot.set_xrange (1000, 100000);

	//plot.set_ylogscale (10);
	//plot.set_yrange (1, 1000000);
	
	plot.plotfile_xy (to_plot, 1, 2, title);

	wait_for_key ();
	return 0;
}

void save_to_file(vector<pair<int, int>> source)
{	
	fstream out_file ("to_plot.dat", fstream::out);

	if (out_file.is_open())
	{
		out_file.precision (6);
		for (vector<pair<int, int>>::iterator it = source.begin(); it != source.end(); ++it)
		{
			out_file << fixed << (*it).first << "   " << fixed << (*it).second << endl;
		}
		out_file.close();
	}
	else
		cout << "File could not be open!\n";
}

void wait_for_key (void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}