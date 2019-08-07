#include "CFile.h"
#include <iomanip>

int main(int argc, char* argv[])
{
	File Numbers((argc == 2) ? argv[1] : "numbers.txt");

	try
	{
		//Numbers.gen_array(1000);	// generate random numbers !ALERT! rewrites file's data
		Numbers.read_array();
		Numbers.sort_array();

		cout.precision(2);
		cout << fixed;
		cout << Numbers.percentile_90th() << endl;
		cout << Numbers.median() << endl;
		cout << Numbers.max() << endl;
		cout << Numbers.min() << endl;
		cout << Numbers.avg() << endl;
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	
	return 0;
}