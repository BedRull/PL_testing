#include "CRect.h"
#include <string>

int main(int argc, char* argv[])
{
	string RectFile;
	string PointsFile;
	
	if(argc == 3)
	{
		RectFile = argv[1];
		PointsFile = argv[2];
	}
	else
	{
		RectFile = "rect.txt";
		PointsFile = "points.txt";
	}
	

	Rect rRect(RectFile.c_str(), PointsFile.c_str());
	
	try
	{
		// read from rect file
		rRect.read_rect();
		
		// read from points file
		rRect.read_points();
		
		// loop through points and define its position
		rRect.find_positions();
	}
	catch (std::exception &ex)
	{
		cout << ex.what() << endl;
	}

	return 0;
};