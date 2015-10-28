#pragma once
#include <iomanip>
#include <complex>
#include <vector>
#include "../MISC/benchmark_timer.hxx"

using namespace std;

class fourier{
	private:
		// for fourier math
		int nPoints;
		int nFFTIterations; 
		complex<double> w;
		vector<complex<double>> fourier_w;
		vector<complex<double>> inv_fourier_w;
		vector<complex<double>>  fft_w;
		vector<complex<double>>  fft_inv_w;
		struct pos{
			int x;
			int y;
		};
		vector<struct pos> sample_pos;

			;
		// other
		void calculate_fft_ifft_matrix();
		void calculate_fourier_w();
		void calculate_inv_fourier_w();
	public:
		fourier(int nPoints);
		void do_fourier(vector<double> data,vector<complex<double>> &out);
		void do_fourier(vector<complex<double>> data,vector<complex<double>> &out);
		void do_inv_fourier(vector<complex<double>> data,vector<double> &out);
		void do_inv_fourier(vector<complex<double>> data,vector<complex<double>> &out);
		void do_fft(vector<double> data,vector<complex<double>> &out);
		void do_fft(vector<complex<double>> data,vector<complex<double>> &out);
		void do_inv_fft(vector<complex<double>> data,vector<double> &out);
		void do_inv_fft(vector<complex<double>> data,vector<complex<double>> &out);
};
