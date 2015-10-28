#pragma once
#include <iomanip>
#include <string>
#include <iostream>
#include <complex>
#include <vector>

using namespace std;

class csv{
	private:
		static const int blockSize = 1024;
		static char block[blockSize];
	public:
		static int read(string filename,vector<int> &array);
		static int read(string filename,vector<double> &array,int howMany = 0);
		static int read(string filename,vector<complex<double>> &array,int howMany = 0);
		static int save(string filename,vector<double> &array,int howMany = 0);
};
