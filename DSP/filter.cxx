#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#include "filter.hxx"
vector<double> filter::fir_lowpass(int length,long fs,long cutoff){
	int M = length -1;
	double ft = (cutoff / double(fs));
	vector<double> w;
	vector<double> window = filter::hamming(length);
	w.resize(length);
	for (int n=0;n<length;n++){
		if (n==M/2){
			w[n] = 2 * ft;
		}else{
			w[n] = sin(2.0*M_PI*ft*(n-M/2.0))/(M_PI*(n-M/2.0));
		}
		w[n] *= window[n];
	}
	return w;
}

vector<double> filter::hamming(int length){
	vector<double> w;
	w.resize(length);
	double alfa = 0.54;
	double beta = 1-alfa;
	for (int n=0;n<w.size();n++){
		w[n] = alfa - (beta * cos((2*M_PI*n)/(double)(length-1)));
	}
	return w;
}

