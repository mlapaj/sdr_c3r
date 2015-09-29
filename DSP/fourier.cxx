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

void fourier::do_fourier(vector<double> data,vector<complex<double>> &out){
	LOG4CPLUS_DEBUG(logger, "Doing normal fourier calculation for double");
	cout << "test" << endl;
	complex<double> wsp = 0;
	for (int k=0;k<(int) nPoints;++k){
		complex<double> wsp = 0;
		for (int n=0;n<nPoints;++n){
			wsp = wsp + data[n] * pow(w,(-k)*n);
		}
		out.push_back(wsp);
	}
	return;
}
