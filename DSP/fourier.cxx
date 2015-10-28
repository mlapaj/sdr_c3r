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
	const int N = nPoints;
	nFFTIterations = log2(nPoints);
	sample_pos.reserve(nFFTIterations*N);
	fft_w.reserve(nFFTIterations*N);
	fft_inv_w.reserve(nFFTIterations*N);
	calculate_fft_ifft_matrix();
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
/*
	stringstream ss;
	ss << "calculated_fourier_";
	ss << nPoints << ".dat";
	
	ofstream fout(ss.str(), ios::out | ios::binary);
    fout.write((char*)&fourier_w[0], fourier_w.size() * sizeof(complex<double>));
	fout.close();
*/
}


void fourier::calculate_inv_fourier_w(){
	fourier_w.reserve(nPoints*nPoints);
	for (int k=0;k<(int) nPoints;++k){
		for (int n=0;n<nPoints;++n){
			inv_fourier_w.push_back(pow(w,(k)*n));
		}
	}

}

void fourier::calculate_fft_ifft_matrix(){

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

void fourier::do_fourier(vector<double> data,vector<complex<double>> &out){
	complex<double> wsp = 0;
	out.resize(nPoints);
	for (int k=0;k<(int) nPoints;++k){
		complex<double> wsp = 0;
		for (int n=0;n<nPoints;++n){
			wsp = wsp + data.at(n) * fourier_w[k*nPoints+n]; // pow(w,(-k)*n);
		}
		out.at(k) = wsp;
	}
	return;
}


void fourier::do_fourier(vector<complex<double>> data,vector<complex<double>> &out){
	complex<double> wsp = 0;
	out.resize(nPoints);
	for (int k=0;k<(int) nPoints;++k){
		complex<double> wsp = 0;
		for (int n=0;n<nPoints;++n){
			wsp = wsp + data.at(n) * fourier_w[k*nPoints+n]; //  * pow(w,(-k)*n);
		}
		out.at(k) = wsp;
	}
	return;
}

void fourier::do_inv_fourier(vector<complex<double>> data,vector<double> &out){
	complex<double> wsp = 0;
	out.resize(nPoints);
	for (int k=0;k<(int) nPoints;++k){
		complex<double> wsp = 0;
		for (int n=0;n<nPoints;++n){
			wsp = wsp + data.at(n) * inv_fourier_w[k*nPoints+n]; // * pow(w,(k)*n);
		}
		out.at(k) = abs(wsp)/nPoints;
	}
	return;
}



void fourier::do_inv_fourier(vector<complex<double>> data,vector<complex<double>> &out){
	complex<double> wsp = 0;
	out.resize(nPoints);
	for (int k=0;k<(int) nPoints;++k){
		complex<double> wsp = 0;
		for (int n=0;n<nPoints;++n){
			wsp = wsp + data.at(n) * inv_fourier_w[k*nPoints+n]; //pow(w,(k)*n);
		}
		// todo 
		out.at(k) = wsp / (double) nPoints;
	}
	return;
}

void fourier::do_fft(vector<double> data,vector<complex<double>> &out){
	out.resize(nPoints);

	for (int j = nFFTIterations-1;j>=0;--j){
		for (int k=0;k<nPoints-1;k+=2){
			const int pos = j*nPoints+k;
			if (j==nFFTIterations-1){
				double a=data[sample_pos[pos].x];
				double b=data[sample_pos[pos].y];
				out[k] = a + (fft_w[pos]  * b);
				out[k+1] = a - (fft_w[pos]  * b);
			}
			else
			{
				unsigned int ppozx = sample_pos[pos].x;
				unsigned int ppozy = sample_pos[pos].y;
				complex<double> a = out[ppozx];
				complex<double> b = out[ppozy];

				out[ppozx] = a + (fft_w[pos] * b);
				out[ppozy] = a - (fft_w[pos] * b);
			}
		}
	}
	return;
}


void fourier::do_fft(vector<complex<double>> data,vector<complex<double>> &out){
	out.resize(nPoints);

	for (int j = nFFTIterations-1;j>=0;--j){
		for (int k=0;k<nPoints-1;k+=2){
			const int pos = j*nPoints+k;
			if (j==nFFTIterations-1){
				complex<double> a=data[sample_pos[pos].x];
				complex<double> b=data[sample_pos[pos].y];
				out[k] = a + (fft_w[pos]  * b);
				out[k+1] = a - (fft_w[pos]  * b);
			}
			else
			{
				unsigned int ppozx = sample_pos[pos].x;
				unsigned int ppozy = sample_pos[pos].y;
				complex<double> a = out[ppozx];
				complex<double> b = out[ppozy];

				out[ppozx] = a + (fft_w[pos] * b);
				out[ppozy] = a - (fft_w[pos] * b);
			}
		}
	}
	return;
}

void fourier::do_inv_fft(vector<complex<double>> data,vector<double> &out){

	vector<complex<double>> t_out;
	t_out.resize(nPoints);
	out.resize(nPoints);

	for (int j = nFFTIterations-1;j>=0;--j){
		for (int k=0;k<nPoints-1;k+=2){
			const int pos = j*nPoints+k;
			if (j==nFFTIterations-1){
				complex<double> a=data[sample_pos[pos].x];
				complex<double> b=data[sample_pos[pos].y];
				t_out[k] = a + (fft_inv_w[pos]  * b);
				t_out[k+1] = a - (fft_inv_w[pos]  * b);
			}
			else
			{
				unsigned int ppozx = sample_pos[pos].x;
				unsigned int ppozy = sample_pos[pos].y;
				complex<double> a = t_out[ppozx];
				complex<double> b = t_out[ppozy];

				t_out[ppozx] = a + (fft_inv_w[pos] * b);
				t_out[ppozy] = a - (fft_inv_w[pos] * b);
			}
		}
	}
	for (int i=0;i<out.size();i++){
		out[i] = abs(t_out[i] / (double) nPoints);
	}
	return;
}



void fourier::do_inv_fft(vector<complex<double>> data,vector<complex<double>> &out){
	vector<complex<double>> t_out;
	t_out.resize(nPoints);
	out.resize(nPoints);

	for (int j = nFFTIterations-1;j>=0;--j){
		for (int k=0;k<nPoints-1;k+=2){
			const int pos = j*nPoints+k;
			if (j==nFFTIterations-1){
				complex<double> a=data[sample_pos[pos].x];
				complex<double> b=data[sample_pos[pos].y];
				t_out[k] = a + (fft_inv_w[pos]  * b);
				t_out[k+1] = a - (fft_inv_w[pos]  * b);
			}
			else
			{
				unsigned int ppozx = sample_pos[pos].x;
				unsigned int ppozy = sample_pos[pos].y;
				complex<double> a = t_out[ppozx];
				complex<double> b = t_out[ppozy];

				t_out[ppozx] = a + (fft_inv_w[pos] * b);
				t_out[ppozy] = a - (fft_inv_w[pos] * b);
			}
		}
	}
	for (int i=0;i<out.size();i++){

		out[i] = t_out[i] / (double) nPoints;
	}
	return;
}
