#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <random>
#include <math.h>
#include <numeric>
using namespace std;

class File
{
public:
	// cons-s
	File();
	File(const char* filePath);
	~File();

	// generate numbers and write to file
	void gen_array(size_t number);

	// read from file
	void read_array();

	// sort array for a sake of efficiency
	void sort_array();

	// count functions
	double percentile_90th();
	double median();
	double max();
	double min();
	double avg();

private:
	// methods
	double nth_percentile(size_t pc);

	// attributes
	const char* m_FilePath;
	vector<double> m_vecNumbers;
};
