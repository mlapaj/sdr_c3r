#include "csv.hxx"
#include <iostream>
#include <fstream>
Logger csv::logger = Logger::getInstance("fourier");
char csv::block[blockSize];

int csv::read_int(string filename,vector<int> &array){
	LOG4CPLUS_DEBUG(logger,"openning file: " << filename << " for reading");
	ifstream file(filename);
	if (file.is_open()){
			LOG4CPLUS_DEBUG(logger,"file oppened successfully");
			while (!file.eof()){
				int i = 0;
				char c;
				file >> i;
				file >> c;
				// cout << i << " " << c;
				array.push_back(i);
			}
	}
	return 0;
}

int csv::read_double(string filename,vector<double> &array){
	LOG4CPLUS_DEBUG(logger,"openning file: " << filename << " for reading");
	ifstream file(filename);
	if (file.is_open()){
			LOG4CPLUS_DEBUG(logger,"file oppened successfully");
			while (!file.eof()){
				double i = 0;
				char c;
				file >> i;
				file >> c;
				// cout << i << " " << c;
				array.push_back(i);
			}
	}
	return 0;
}

