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
}

void fourier::do_fourier(vector<double> data,vector<complex<double>> &out){
	LOG4CPLUS_DEBUG(logger, "Doing normal fourier calculation for double");
	complex<double> wsp = 0;
	out.resize(nPoints);
	benchmark_timer btimer;
	for (int k=0;k<(int) nPoints;++k){
		complex<double> wsp = 0;
		for (int n=0;n<nPoints;++n){
			wsp = wsp + data.at(n) * pow(w,(-k)*n);
		}
		out.at(k) = wsp;
	}
	btimer.print();
	return;
}


void fourier::do_fft(vector<double> data,vector<complex<double>> &out){
	auto print_array =[]( vector<vector<int>> tab)->void {
		cout << endl << "---------------" << endl;
		for (vector<int> x:tab){
			for (int y: x){
				cout << y << "\t";
			}
			cout << endl;
		}

		cout <<  "---------------" << endl;
	};
	const int N = nPoints;
	out.resize(N);
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

	// print_array(tab);



	vector<vector<int>> wsp(N,vector<int>(ileIteracji));
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

	// print_array(wsp);

	vector<complex<double>>  test(ileIteracji*N);	
    vector<int>  tppozx(ileIteracji*N);	
    vector<int>  tppozy(ileIteracji*N);	
	unsigned int pozX=0;
	unsigned int pozY=0;
	unsigned int doKtorej = 2;


	for (int j = ileIteracji-1;j>=0;--j){
		for (int k=0;k<N-1;k+=2){
			pozX = tab[k][j];
			pozY = tab[k+1][j];
			if (j==ileIteracji-1){
				int potega = wsp[k+1][j]-1;
				complex<double> omega = exp((complex<double>(0,float(-1 * 2 * M_PI * potega) / float(doKtorej))));
				test[j*N+k] = omega;

				tppozx[j*N+k] = pozX;
				tppozy[j*N+k] = pozY;
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

				tppozx[j*N+k] = ppozx;
				tppozy[j*N+k] = ppozy;

				int potega = wsp[ppozy][j]-1;
				complex<double> omega = exp(complex<double>(0,float(-1 * 2 * M_PI * potega) / (float) doKtorej));
				test[j*N+k] = omega;
			}
		}
		doKtorej = doKtorej*2;
	}

	pozX=0;
	pozY=0;
	doKtorej = 2;
	benchmark_timer btimer;
	for (int j = ileIteracji-1;j>=0;--j){
		for (int k=0;k<N-1;k+=2){
			const int pos = j*N+k;
			if (j==ileIteracji-1){
				double a=data[tppozx[pos]];
				double b=data[tppozy[pos]];
				out[k] = a + (test[pos]  * b);
				out[k+1] = a - (test[pos]  * b);
			}
			else
			{
				unsigned int ppozx = tppozx[pos];
				unsigned int ppozy = tppozy[pos];
				complex<double> a = out[ppozx];
				complex<double> b = out[ppozy];

				out[ppozx] = a + (test[pos] * b);
				out[ppozy] = a - (test[pos] * b);
			}
		}
	}
	btimer.print();
	return;


}


