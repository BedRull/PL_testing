#include "CFile.h"

File::File()
{
	m_FilePath = nullptr;
	m_vecNumbers.reserve(1000);
}


File::File(const char* filePath) 
	: m_FilePath(filePath)
{
	m_vecNumbers.reserve(1000);
}


File::~File()
{
}


void File::gen_array(size_t number)
{
	// random number generator
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<short> gen_number(-RAND_MAX - 1, RAND_MAX);

	ofstream file;

	file.open(m_FilePath);

	if(!file.is_open())
		throw runtime_error("File not found");
	
	for(size_t i = 0; i < number; ++i)
		file << gen_number(rng) << endl;

	file.close();
}


void File::read_array()
{
	ifstream file;

	file.open(m_FilePath);

	if(!file.is_open())
		throw runtime_error("File not found");

	double number;
	while(file >> number)
		m_vecNumbers.push_back(number);
	
	file.close();
}


void File::sort_array()
{
	std::sort(m_vecNumbers.begin(), m_vecNumbers.end());
}


double File::percentile_90th()
{
	return nth_percentile(90);
}


double File::median()
{
	return nth_percentile(50);
}


double File::max()
{
	return m_vecNumbers.back();
}


double File::min()
{
	return m_vecNumbers.front();
}


double File::avg()
{
	return (double) accumulate(m_vecNumbers.begin(), m_vecNumbers.end(), 0) / m_vecNumbers.size();
}


double File::nth_percentile(size_t pc)
{
	double idx = (double)(m_vecNumbers.size() - 1) * pc / 100;

	double remainder = idx - int(idx);

	if(remainder == 0)
		return m_vecNumbers[idx];

	return m_vecNumbers[floor(idx)] + (m_vecNumbers[ceil(idx)] - m_vecNumbers[floor(idx)]) * remainder;
}

