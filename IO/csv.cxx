#include "csv.hxx"
#include <iostream>
#include <fstream>
Logger csv::logger = Logger::getInstance("fourier");
char csv::block[blockSize];

int csv::read(string filename,vector<int> &array){
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

int csv::read(string filename,vector<double> &array,int howMany){
	LOG4CPLUS_DEBUG(logger,"openning file: " << filename << " for reading");
	ifstream file(filename);
	if (file.is_open()){
			LOG4CPLUS_DEBUG(logger,"file oppened successfully");
			int timer = howMany;
			while (!file.eof()){
				double i = 0;
				char c;
				file >> i;
				file >> c;
				// cout << i << " " << c;
				if ((howMany > 0) && (--timer < 0)) break;
				array.push_back(i);
			}
	}
	return 0;
}



int csv::save(string filename,vector<double> &array,int howMany){
	LOG4CPLUS_DEBUG(logger,"openning file: " << filename << " for reading");
	ofstream file(filename);
	if (file.is_open()){
			LOG4CPLUS_DEBUG(logger,"file oppened successfully");
			int count = 0;
			while (count < array.size()){
				double i = array[count];
				char c = ',';
				file << i;
				if ((howMany > 0) && (++count >= howMany)) break;
				file << c;
			}
	}
	return 0;
}



int csv::read(string filename,vector<complex<double>> &array,int howMany){
	LOG4CPLUS_DEBUG(logger,"openning file: " << filename << " for reading");
	ifstream file(filename);
	if (file.is_open()){
			LOG4CPLUS_DEBUG(logger,"file oppened successfully");
			int timer = howMany;
			while (!file.eof()){
				double i = 0;
				double j = 0;
				char c;
				file >> i;
				file >> j;
				file >> c;
				if (c!='i') break;
				file >> c;
				if (c!=',') break;
				if ((howMany > 0) && (--timer < 0)) break;
				array.push_back(complex<double>(i,j));
			}
	}
	return 0;
}
