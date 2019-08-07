#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

const int INTERVALS = 16;
const int FILES = 5;

void read_data(char* files[], float arr[][FILES])
{
	for(size_t i = 0; i < FILES; ++i)
	{
		ifstream file;
		file.open(files[i]);

		if(!file.is_open())
		{
			char buf[100];
			sprintf_s(buf, sizeof buf, "%s file not found", files[i]);
			throw runtime_error(buf);
		}

		for(size_t j = 0; j < INTERVALS; ++j)
		{
			float number;
			if(file >> number)
				arr[j][i] = number;
			else
			{
				char buf[100];
				sprintf_s(buf, sizeof buf, "%s, %d line: invalid data format", files[i], j + 1);
				throw runtime_error(buf);
			}
		}
	}
}


int find_largest(float arr[][FILES])
{
	float largest = 0;
	int interval_num = 0;

	for(size_t i = 0; i < INTERVALS; i++)
	{
		float sum = 0;
		for(size_t j = 0; j < FILES; j++)
			sum += arr[i][j];

		if(sum > largest)
		{
			largest = sum;
			interval_num = i + 1;
		}
	}

	return interval_num;
}


int main(int argc, char* argv[])
{
	float arr[INTERVALS][FILES];

	try
	{
		if(argc < FILES)
			throw runtime_error("Not enough parameters");
		
		// read data
		read_data(&argv[1], arr);
		
		// find largest sum between rows
		cout << find_largest(arr);
	}
	catch(exception &ex)
	{
		cout << ex.what();
	}

	return 0;
};