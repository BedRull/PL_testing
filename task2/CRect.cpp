#include "CRect.h"

Rect::Rect()
	: m_RectFile(nullptr),
	m_PointsFile(nullptr)
{
	m_RectCoords.reserve(4);
	m_PointCoords.reserve(100);
}


Rect::Rect(const char* RectFile, const char* PointsFile)
	: m_RectFile(RectFile),
	m_PointsFile(PointsFile)
{
	m_RectCoords.reserve(4);
	m_PointCoords.reserve(100);
}


Rect::~Rect()
{
}


void Rect::read_rect()
{
	ifstream InputFile;

	InputFile.open(m_RectFile);

	if(!InputFile.is_open())
		throw runtime_error("Rectangle file not found");

	for(size_t i = 0; i < 4; ++i)
	{
		float x, y;
		if(InputFile >> x >> y)
			m_RectCoords.push_back(SPoint(x, y));
		else
			throw runtime_error("Invalid data format");
	}

	InputFile.close();
}


void Rect::read_points()
{
	ifstream InputFile;

	InputFile.open(m_PointsFile);

	if(!InputFile.is_open())
		throw runtime_error("Points file not found");
	
	float x, y;
	while(InputFile >> x >> y)
		m_PointCoords.push_back(SPoint(x,y));

	InputFile.close();
}


void Rect::find_positions()
{
	for(auto itCurr = m_PointCoords.begin(), itEnd = m_PointCoords.end(); itCurr != itEnd; ++itCurr)
		cout << find_pos(*itCurr) << endl;
}


int Rect::find_pos(SPoint point)
{
	// check if points at any of top
	if(is_on_top(point))
		return ON_TOP;

	int count_of_zeros = 0;
	int count_of_negative = 0;

	auto itNext = m_RectCoords.begin() + 1;
	auto itCurr = m_RectCoords.begin();
	auto itEnd = m_RectCoords.end();
	for(; itCurr != itEnd; ++itCurr, ++itNext)
	{
		if(itNext == itEnd)
			itNext -= 4;		// peek first top

		float A = itCurr->y - itNext->y;
		float B = itNext->x - itCurr->x;
		float C = B * itCurr->y - A * itCurr->x;

		int D = B * (point.y - itCurr->y) - (point.x - itCurr->x) * (itNext->y - itCurr->y);

		// if D = 0 then point on the line
		// if D > 0 then point on the left
		// if D < 0 then point on the right
		if(!D)
			++count_of_zeros;
		else if(D < 0)
			++count_of_negative;
	}

	if(count_of_zeros && count_of_negative == 3)	// if 1 on edge and 3 on the right then point definitely on edge
		return ON_EDGE;
	else if(count_of_negative == 4)					// if 4 on the right then point inside the rect
		return INSIDE;
	else
		return OUTSIDE;								// any other option - outside
}


bool Rect::is_on_top(SPoint point)
{
	return find(m_RectCoords.begin(), m_RectCoords.end(), point) != m_RectCoords.end();
}

