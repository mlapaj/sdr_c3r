#include <iostream>
#include <cmath>
#include "fourier.hxx"
#include <complex>
#include <array>
#include <fstream>
#include <iterator>
#include <sstream>


using namespace std;
fourier::fourier(int nPoints){
	this->nPoints = nPoints;
	w = exp(complex<double>(0,2*M_PI/(double)nPoints));	
	calculate_fourier_w();
	calculate_inv_fourier_w();
}

void fourier::calculate_fourier_w(){
	fourier_w.reserve(nPoints*nPoints);
	for (int k=0;k<(int) nPoints;++k){
		for (int n=0;n<nPoints;++n){
			fourier_w.push_back(pow(w,(-k)*n));
		}
	}
}


void fourier::calculate_inv_fourier_w(){
	fourier_w.reserve(nPoints*nPoints);
	for (int k=0;k<(int) nPoints;++k){
		for (int n=0;n<nPoints;++n){
			inv_fourier_w.push_back(pow(w,(k)*n));
		}
	}

}





