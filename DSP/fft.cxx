#include <iostream>
#include <cmath>
#include "fft.hxx"
#include <complex>
#include <array>
#include <fstream>
#include <iterator>
#include <sstream>


using namespace std;
fft::fft(int nPoints){
	this->nPoints = nPoints;
	w = exp(complex<double>(0,2*M_PI/(double)nPoints));	
	const int N = nPoints;
	nFFTIterations = log2(nPoints);
	sample_pos.reserve(nFFTIterations*N);
	fft_w.reserve(nFFTIterations*N);
	fft_inv_w.reserve(nFFTIterations*N);
	calculate_fft_ifft_matrix();
}



void fft::calculate_fft_ifft_matrix(){
/*
	auto print_array =[]( vector<vector<int>> t_tab)->void {
		cout << endl << "---------------" << endl;
		for (vector<int> x:t_tab){
			for (int y: x){
				cout << y << "\t";
			}
			cout << endl;
		}

		cout <<  "---------------" << endl;
	};
*/
	const int N = nPoints;

	vector<vector<int>> tab(N,vector<int>(nFFTIterations));

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
	for (int j=0;j<nFFTIterations-1;j++){
		if (rozmiar ==0) break;
		vector<int> mytab;
		
		for (int k=0;k<(N/rozmiar);k++)
		{
			for (int l=0;l<rozmiar/2 ;l++){ mytab.push_back(tab[even[l]+k*rozmiar][j]); }
			for (int l=0;l<rozmiar/2 ;l++){ mytab.push_back(tab[odd[l]+k*rozmiar][j]); }
		}
		
		for (int l=0;l<mytab.size();l++){ tab[l][j+1] = mytab[l];}
		rozmiar = rozmiar / 2;
	}


	vector<vector<int>> wsp(N,vector<int>(nFFTIterations));
	int i = 0;
	for (int cur_col=wsp[0].size()-1;cur_col>=0;--cur_col){
		int zeros_ones_num = pow(2,i);
		int cur_row = 0;
		while (cur_row < wsp.size()){
			for (int tmp_l = 0; tmp_l < zeros_ones_num && cur_row < wsp.size();++tmp_l,++cur_row){
				wsp[cur_row][cur_col] = 0;
			}
			for (int tmp_m = 1; tmp_m < zeros_ones_num+1 && cur_row < wsp.size();tmp_m++,++cur_row){
				wsp[cur_row][cur_col] = tmp_m;
			}
		}
		++i;
	}


	unsigned int pozX=0;
	unsigned int pozY=0;
	unsigned int doKtorej = 2;
	for (int j = nFFTIterations-1;j>=0;--j){
		for (int k=0;k<N-1;k+=2){
			pozX = tab[k][j];
			pozY = tab[k+1][j];
			if (j==nFFTIterations-1){
				int potega = wsp[k+1][j]-1;
				complex<double> omega = exp((complex<double>(0,float(-1 * 2 * M_PI * potega) / float(doKtorej))));
				fft_w[j*N+k] = omega;
				omega = exp((complex<double>(0,float(1 * 2 * M_PI * potega) / float(doKtorej))));
				fft_inv_w[j*N+k] = omega;
				sample_pos[j*N+k].x = pozX;
				sample_pos[j*N+k].y = pozY;
			}
			else
			{

				unsigned int ppozx;
				unsigned int ppozy;
				for (int i=0;i<tab.size();i++){
					if (tab[i][j+1] == pozX) {
						ppozx = i;
						break; }
				}
				for (int i=0;i<tab.size();i++){
					if (tab[i][j+1] == pozY) {
						ppozy = i;
						break; }
				}

				sample_pos[j*N+k].x = ppozx;
				sample_pos[j*N+k].y = ppozy;

				int potega = wsp[ppozy][j]-1;
				complex<double> omega = exp(complex<double>(0,float(-1 * 2 * M_PI * potega) / (float) doKtorej));
				fft_w[j*N+k] = omega;
				omega = exp(complex<double>(0,float(1 * 2 * M_PI * potega) / (float) doKtorej));
				fft_inv_w[j*N+k] = omega;

			}
		}
		doKtorej = doKtorej*2;
	}



}
