#include "csv.hxx"
#include <iostream>
#include <fstream>
char csv::block[blockSize];

int csv::read(string filename,vector<int> &array){
	ifstream file(filename);
	if (file.is_open()){
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
	ifstream file(filename);
	if (file.is_open()){
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
	ofstream file(filename);
	if (file.is_open()){
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
	ifstream file(filename);
	if (file.is_open()){
			int timer = howMany;
			while (!file.eof()){
				double i = 0;
				double j = 0;
				char c;
				file >> i;
				file >> j;
				file >> c;
				file >> c;
				if ((howMany > 0) && (--timer < 0)) break;
				array.push_back(complex<double>(i,j));
			}
	}
	return 0;
}
