#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <complex>

using namespace std;

class IqDataReader
{
public:
	IqDataReader(string fileName,long block_size,bool repeat = false);
	int readData(vector<complex<double>> &data,int bytes = 0);
	virtual ~IqDataReader ();

private:
	unique_ptr<ifstream> file;
	int block_size;
	char *buffer;
	bool repeat;
	/* data */
};
