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
			;
		// other
		void calculate_fourier_w();
		void calculate_inv_fourier_w();
	public:
		fourier(int nPoints);
		template <typename T_in, typename T_out>
			void do_fourier(vector<T_in> data,vector<complex<T_out>> &out){
				out.resize(nPoints);
				for (int k=0;k<(int) nPoints;++k){
					complex<T_out> wsp = 0;
					for (int n=0;n<nPoints;++n){
						//wsp = wsp + data.at(n) * fourier_w[k*nPoints+n];
						wsp = wsp + data.at(n) * pow(w,(-k)*n);
					}
					out.at(k) = wsp;
				}
				return;
			}
		template <typename T_in, typename T_out>
			void do_inv_fourier(const vector<complex<T_in>> &data,vector<complex<T_out>> &out){
				out.resize(nPoints);
				for (int k=0;k<(int) nPoints;++k){
					complex<T_out> wsp = 0;
					for (int n=0;n<nPoints;++n){
						// wsp = wsp + data.at(n) * inv_fourier_w[k*nPoints+n]; // * pow(w,(k)*n);
						wsp = wsp + data.at(n) * pow(w,(k)*n);
					}
					out.at(k) = wsp / (T_out) nPoints;
				}
				return;
			}

		template <typename T_in, typename T_out>
			void do_inv_fourier(const vector<complex<T_in>> &data,vector<T_out> &out){
				out.resize(nPoints);
				for (int k=0;k<(int) nPoints;++k){
					complex<T_out> wsp = 0;
					for (int n=0;n<nPoints;++n){
						// wsp = wsp + data.at(n) * inv_fourier_w[k*nPoints+n]; // * pow(w,(k)*n);
						wsp = wsp + data.at(n) * pow(w,(k)*n);
					}
					out.at(k) = abs(wsp)/nPoints;
				}
				return;
			}
};
