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
	iq_data_reader(string fileName,int block_size);
	int read_data(vector<complex<double>> &data);
	virtual ~iq_data_reader (){};

private:
	unique_ptr<ifstream> file;
	int block_size;
	/* data */
};
