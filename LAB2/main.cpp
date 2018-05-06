//main.cpp
#include <cmath>
#include <ctime>
#include "toposort.hpp"
#include "gnuplot_i.hpp"

using namespace std;

// AUX FUNCTIONS //////////////////////////////////////////////////////////////////////
void save_to_file(vector<pair<int, int>> k_pair, vector<pair<int, int>> t_pair);	//
void wait_for_key (void);															//
vector<string> benchmark_toposort(void);														//
void plot_graph(void);																//
void show_toposort(vector<int> &source, const string title);						//
void eval_toposort(vector<string> &source);															//
//////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char **argv)
{	
	vector<string> best_performance;

	best_performance = benchmark_toposort ();
	eval_toposort (best_performance);
	plot_graph ();
	
	return 0;
}

// AUX FUNCTIONS - DEFINING ////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> benchmark_toposort(void)
{
	vector<vector<int>> khan;
	vector<vector<int>> tarjan;
	const char *file_name[] = {"./data/top_small.txt", "./data/top_med.txt","./data/top_large.txt","./data/top_huge.txt"};
	vector<string> files (file_name, end(file_name));
	vector<string> eval_toposort;
	
	int time_elapsed;
	clock_t time_end;
	clock_t time_start;
	vector<pair<int, int>> t_pair, k_pair;

	for(int i = 0; i < files.size(); ++i)
	{
		{
			GRAPH G(files[i]);
			
			time_start = clock();
			khan.push_back (G.khan_toposort ());
			time_end = clock();
			time_elapsed = (float)(((time_end - time_start) * 1000000)/ CLOCKS_PER_SEC);	// 10^(-6) seconds = microsecond
			k_pair.push_back (make_pair (khan[i].size(), time_elapsed));
			show_toposort (khan[i], "Khan's Algorithm");

			time_start = clock();
			tarjan.push_back (G.tarjan_toposort ());
			time_end = clock();
			time_elapsed = (float)(((time_end - time_start) * 1000000) / CLOCKS_PER_SEC);	// 10^(-6) seconds = microsecond
			t_pair.push_back (make_pair (tarjan[i].size(), time_elapsed));
			show_toposort (tarjan[i], "Tarjan's Algorithm");

			k_pair[i].second < t_pair[i].second ? (eval_toposort.push_back ("Khan's")) : (eval_toposort.push_back ("Tarjan's"));
		}	// scoping for instance of GRAPH;
	}
	save_to_file (k_pair, t_pair);
	return eval_toposort;
}

void plot_graph(void)
{
	const string k_to_plot = "./data/k_to_plot.dat";
	const string t_to_plot = "./data/t_to_plot.dat";

	cout << "Ploting Benchmark results for further reference... press any key.";
	cin.ignore ();
	
	string titleK = "Khan Toposort Benchmark";
	string titleT = "Tarjan Toposort Benchmark";
	Gnuplot plot("linespoints");
	plot.set_grid ();

	plot.set_xlabel ("Vertices");
	plot.set_xlogscale (10);
	plot.set_xrange (1, 150000);

	plot.set_ylabel ("Microseconds");
	plot.set_ylogscale (10);
	//plot.set_yrange (1, 1000000);
	
	plot.plotfile_xy (k_to_plot, 1, 2, titleK);
	plot.plotfile_xy (t_to_plot, 1, 2, titleT);

	wait_for_key ();
}

void save_to_file(vector<pair<int, int>> k_pair, vector<pair<int, int>> t_pair)
{	
	fstream out_file1 ("./data/k_to_plot.dat", fstream::out);
	fstream out_file2 ("./data/t_to_plot.dat", fstream::out);

	if (out_file1.is_open())
	{
		out_file1.precision (6);
		for (vector<pair<int, int>>::iterator it = k_pair.begin(); it != k_pair.end(); ++it)
		{
			out_file1 << fixed << (*it).first << "   " << fixed << (*it).second << endl;
		}
		out_file1.close();
	}
 	if (out_file2.is_open())
	{
		out_file2.precision (6);
		for (vector<pair<int, int>>::iterator it = t_pair.begin(); it != t_pair.end(); ++it)
		{
			out_file2 << fixed << (*it).first << "   " << fixed << (*it).second << endl;
		}
		out_file2.close();
	}
	else
		cout << "File could not be open!\n";
}


void eval_toposort(vector<string> &source)
{
	for (int i = 0; i < source.size(); i++)
	{
		cout << "\tThe best performing algorithm for " << pow(10.0, (i+1)) << " vertices was " << source[i] << endl;
	}
}

void show_toposort(vector<int> &source, const string title)
{
	char prompt = 'n';
	
	cout << title << "\n\tWould you like to display all " << source.size() << " sorted vertices?(y, [N]) ";
	cin >> prompt;

	if (prompt == 'y' || prompt == 'Y')
	{
		for (int i = 0; i < source.size(); ++i)
			if (i == source.size() - 1)
				cout << "V" << source[i] << endl;
			else
				cout << "V" << source[i] << "|-> ";
		cout << "\nSORTED VERTICES: " << source.size() << endl << endl;
	}
	else
		cout << "\nSORTED VERTICES: " << source.size() << endl << endl;
	cin.ignore ();
	cin.clear ();
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
