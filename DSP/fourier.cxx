#include <iostream>
#include <cmath>
#include "fourier.hxx"
#include <complex>
#include <array>
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


void fourier::do_fft(vector<double> data,vector<complex<double>> &out){
	const int N = data.size();
	const int ileIteracji = log2(N);
	vector<vector<int>> tab(N,vector<int>(ileIteracji));

	// fill first row with (1..n) values (first iteration):
	for (int x=0;x<N;x++){ tab[x][0] = x; }


	// create even and odd auxilary vectors
	vector<int> odd;
	vector<int> even;
	for (int k=1;k<N;k+=2){
		odd.push_back(k);
		even.push_back(k-1);
	}

    //radix next iterations
	int rozmiar = N;
	for (int j=0;j<ileIteracji-1;j++){
		vector<int> mytab;
		for (int k=0;k<(N/rozmiar);k++)
		{
			for (int l=0;l<rozmiar/2 ;l++){ mytab.push_back(tab[even[l]+k*rozmiar][j]); }
			for (int l=0;l<rozmiar/2 ;l++){ mytab.push_back(tab[odd[l]+k*rozmiar][j]); }
		}
		for (int l=0;l<mytab.size();l++){ tab[l][j+1] = mytab[l];}
		rozmiar = rozmiar / 2;
	}

    for (vector<int> x:tab){
		for (int y: x){
			cout << y << "\t";
		}
		cout << endl;
	}

}
