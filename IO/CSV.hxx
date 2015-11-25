#pragma once
#include <iomanip>
#include <string>
#include <complex>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

namespace CSV{
	template <typename T>
		int read(string filename,vector<complex<T>> &array,int howMany = 0){
			ifstream file(filename);
			if (file.is_open()){
				int timer = howMany;
				while (!file.eof()){
					T i = 0;
					T j = 0;
					char c;
					file >> i;
					file >> j;
					file >> c;
					file >> c;
					if ((howMany > 0) && (--timer < 0)) break;
					array.push_back(complex<T>(i,j));
				}
			}
			return 0;
		}

	template <typename T>
		int read(string filename,vector<T> &array,int howMany = 0){
			ifstream file(filename);
			if (file.is_open()){
				int timer = howMany;
				while (!file.eof()){
					T i;
					char c;
					file >> i;
					file >> c;
					if ((howMany > 0) && (--timer < 0)) break;
					array.push_back(i);
				}
			}
			return 0;
		}


	template <typename T>
		int save(string filename,vector<complex<T>> &array,int howMany = 0){
			ofstream file(filename);
			if (file.is_open()){
				int count = 0;
				while (count < array.size()){
					T real = array[count].real();
					T imag = array[count].imag();

					char c = ',';
					file << real;
					file << showpos << imag << "i";
					if ((howMany > 0) && (++count >= howMany)) break;
					file << c;
				}
			}
			return 0;
		}

	template <typename T>
		int save(string filename,vector<T> &array,int howMany = 0){
			ofstream file(filename);
			if (file.is_open()){
				int count = 0;
				while (count < array.size()){
					T i = array[count];
					char c = ',';
					file << i;
					if ((howMany > 0) && (++count >= howMany)) break;
					file << c;
				}
			}
			return 0;
		}


}


