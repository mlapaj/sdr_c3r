#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <complex>

using namespace std;

class iq_data_reader
{
public:
	iq_data_reader(string fileName,long block_size, long data_speed = 0);
	int read_data(vector<complex<double>> &data);
	virtual ~iq_data_reader ();

private:
	long data_speed;
	time_t timer;
	unique_ptr<ifstream> file;
	int block_size;
	char *buffer;
	/* data */
};
