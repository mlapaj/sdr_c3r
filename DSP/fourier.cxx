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
	const int N = data.size();
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

	print_array(tab);



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

	print_array(wsp);

	int pozX;
	int pozY;
	int doKtorej = 2;
	for (int j = ileIteracji-1;j>=0;--j){
		for (int k=0;k<N-1;k+=2){
			pozX = tab[k][j];
			pozY = tab[k+1][j];
			if (j==ileIteracji-1){
				double a=data[pozX];
				double b=data[pozY];
				int potega = wsp[k+1][j]-1;
				complex<double> omega = exp((complex<double>(0,float(-1 * 2 * M_PI * potega) / float(doKtorej))));
				out[k] = a + (omega * b);
				out[k+1] = a - (omega * b);
			}
			else
			{
				int ppozx = -1;
				int ppozy = -1;
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
				complex<double> a = out[ppozx];
				complex<double> b = out[ppozy];

				int potega = wsp[ppozy][j]-1;
				complex<double> omega = exp(complex<double>(0,float(-1 * 2 * M_PI * potega) / (float) doKtorej));

				out[ppozx] = a + (omega * b);
				out[ppozy] = a - (omega * b);
			}
		}
		doKtorej = doKtorej*2;
	}

	return;


}


/*

	for (int x=0;x<N;x++){ wsp[x][0] = x+1; }
	cout << "wsp" << endl;
	for (vector<int> x:wsp){
		cout << x[0] << " ";
	}
	cout << endl;

	int podzial = N / 2;

	for (int j=0;j<ileIteracji;j++){
		if (j == 0){
			vector<int> zeros(podzial);
			vector<int> t;
			t.insert(t.end(),zeros.begin(),zeros.end());
			for (int l=0;l<podzial;l++){
				for (int n=0;n<wsp.size();n++){
					t.push_back(wsp[n][j]);
				}
			}

			for(int k=0;k<wsp.size();k++){
				wsp[k][j] = t[k];
			}
		}
		else
		{
			int start = wsp.size()-podzial;
			int koniec = wsp.size();
			vector<int> toAdd;
			for (int l=start;l<koniec;++l)
			{
				toAdd.push_back(wsp[l][j-1]);
			}
			cout << "toAdd";
			for (int x: toAdd){
				cout << x << " ";
			}
			cout << endl;
			// even = 1:2:size(toAdd,1);
			vector<int> even;
			for (int i=0;i<toAdd.size();i+=2){
				even.push_back(i);
			}
			vector<int> dodanie;
			for (int k=0;k<N/podzial;k++){
				for (int l=0;l<(podzial/2);l++){
					dodanie.push_back(0);
				}
				cout << "zeros" << dodanie.size() << endl; 
				for (int l=0;l<(toAdd.size()/2);l++){
					dodanie.push_back(toAdd[l]);
				}
				cout << "dodanie" << dodanie.size() << endl; 
			}
			cout << "dodanie size: " << dodanie.size() << endl;
			for (int l=0;l<dodanie.size();l++){ wsp[l][j] = dodanie[l];}
			podzial = podzial / 2;
		}
	}


	for (vector<int> x:wsp){
		for (int y: x){
			cout << y << "\t";
		}
		cout << endl;
	}

*/
