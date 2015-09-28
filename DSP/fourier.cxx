#include <iostream>
#include <cmath>
#include "fourier.hxx"
#include <complex>

using namespace std;
fourier::fourier(int nPoints){
	LOG4CPLUS_DEBUG(logger, "Starting constructor...");
	this->nPoints = nPoints;
	w = exp(complex<double>(0,2*M_PI/(double)nPoints));
	cout << w << endl;
}

void fourier::do_fourier(vector<int> data){
	LOG4CPLUS_DEBUG(logger, "Doing normal fourier calculation");
	return;
}

void fourier::do_fourier(vector<double> data){
	LOG4CPLUS_DEBUG(logger, "Doing normal fourier calculation for double");
	complex<double> wsp = 0;
	int k=0;
	for (const double sample: data){
		wsp = 0;
		for (int n=0;n<nPoints;n++){
			wsp = wsp +  sample*  pow(w,-k * (n-1));
		}
		cout << wsp << endl;
		k++;
	}
	return;
}
