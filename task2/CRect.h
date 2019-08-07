#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

using TPoint = pair<float, float>;

struct SPoint
{
	float x, y;

	SPoint()
	{
		x = y = 0;
	}

	SPoint(float a, float b)
		: x(a), y(b)
	{
	}

	SPoint(const SPoint& obj)
		: x(obj.x),
		y(obj.y)
	{
	}

	inline bool operator== (SPoint ptSecond)
	{ 
		return x == ptSecond.x && y == ptSecond.y;
	}
};


class Rect
{
public:
	// data type
	enum { ON_TOP, ON_EDGE, INSIDE, OUTSIDE };

	// cons-s
	Rect();
	Rect(const char* RectFile, const char* PointsFile);
	~Rect();

	// read rect coords
	void read_rect(); 

	// read point coords
	void read_points();

	// common check
	void find_positions();

private:
	//methods
	int find_pos(SPoint point);
	bool is_on_top(SPoint point);

	//members
	const char* m_RectFile;
	const char* m_PointsFile;
	vector<SPoint> m_RectCoords;
	vector<SPoint> m_PointCoords;
};
