#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;
using TTime = pair<size_t, size_t>;

int main(int argc, char* argv[])
{
	ifstream input_file;
	
	try
	{
		if(argc == 2)
			input_file.open(argv[1]);
		else
			throw runtime_error("Not enough parameters");

		if(!input_file.is_open())
			throw runtime_error("File not found");
	}
	catch(exception &ex)
	{
		cout << ex.what();
		return 0;
	}
	
	vector<TTime> Enter_Times;			// here we store enter value in format first = hours, second = minutes
	vector<TTime> Exit_Times;			// the same
	vector<TTime> Times;				// here we store exit time in format first = visitor left time in minutes from bank opening, second = visitor spent time in bank

	string enter_time;
	string exit_time;

	while(input_file >> enter_time >> exit_time)
	{
		size_t pos = 0;
		int enter_hours = 0;
		int enter_minutes = 0;
		int exit_hours = 0;
		int exit_minutes = 0;

		if((pos = enter_time.find(':') != string::npos))
		{
			enter_hours = stoi(enter_time.substr(0, pos));
			enter_minutes = stoi(enter_time.erase(0, pos + 1));
		}

		if((pos = exit_time.find(':')) != string::npos)
		{
			exit_hours = stoi(exit_time.substr(0, pos));
			exit_minutes = stoi(exit_time.erase(0, pos + 1));
		}
		
		size_t left_time = (exit_hours - 8) * 60 + exit_minutes;								// remember time when visitor left the bank in minutes form 8:00
		size_t time_spent = (exit_hours - enter_hours) * 60 + (exit_minutes - enter_minutes);	// and spent time in bank in minutes

		Enter_Times.push_back(TTime(enter_hours, enter_minutes));
		Exit_Times.push_back(TTime(exit_hours, exit_minutes));
		Times.push_back(TTime(left_time, time_spent));
	}

	input_file.close();

	auto itCurr = Times.begin();
	auto itEnd = Times.end();

	vector<int> Visitors;
	for(; itCurr != itEnd; ++itCurr)
	{
		auto itNext = itCurr + 1;
		auto itPrev = itCurr;
		int number_of_visitors = 0;

		// check if current enter time smaller than previous comers exit time
		while(itPrev != Times.begin() && (*itCurr).first - (*itCurr).second < (*itPrev).first)
		{
			--itPrev;				// move left
			++number_of_visitors;
		}

		// check if current exit_time bigger than next comers enter time
		while(itNext != itEnd && (*itCurr).first > (*itNext).first - (*itNext).second)
		{
			++itNext;				// move right
			++number_of_visitors;
		}
		
		Visitors.push_back(number_of_visitors);
	}

	size_t idx = distance(Visitors.begin(), max_element(Visitors.begin(), Visitors.end()));

	char buf[100];
	sprintf_s(buf, sizeof buf, "%d:%d %d:%d", Enter_Times[idx].first, Enter_Times[idx].second, Exit_Times[idx].first, Exit_Times[idx].second);
	cout << buf << endl;

	return 0;
};