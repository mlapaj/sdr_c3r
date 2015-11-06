#pragma once
#include <iomanip>
#include <complex>
#include <vector>
#include "../MISC/benchmark_timer.hxx"

using namespace std;

class fft{
	private:
		// for fourier math
		int nPoints;
		int nFFTIterations; 
		complex<double> w;
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
	public:
		fft(int nPoints);

		template <typename T_in,typename T_out>
		void do_fft(vector<T_in> data,vector<T_out> &out){

			out.resize(nPoints);

			for (int j = nFFTIterations-1;j>=0;--j){
				for (int k=0;k<nPoints-1;k+=2){
					const int pos = j*nPoints+k;
					if (j==nFFTIterations-1){
						T_in a=data[sample_pos[pos].x];
						T_in b=data[sample_pos[pos].y];
						out[k] = a + (fft_w[pos]  * b);
						out[k+1] = a - (fft_w[pos]  * b);
					}
					else
					{
						unsigned int ppozx = sample_pos[pos].x;
						unsigned int ppozy = sample_pos[pos].y;
						T_out a = out[ppozx];
						T_out b = out[ppozy];

						out[ppozx] = a + (fft_w[pos] * b);
						out[ppozy] = a - (fft_w[pos] * b);
					}
				}
			}
			return;		
		}

		template <typename T>
		void do_inv_fft(vector<complex<T>> &data,vector<T> &out){

			vector<complex<T>> t_out;
			t_out.resize(nPoints);
			out.resize(nPoints);

			for (int j = nFFTIterations-1;j>=0;--j){
				for (int k=0;k<nPoints-1;k+=2){
					const int pos = j*nPoints+k;
					if (j==nFFTIterations-1){
						complex<T> a=data[sample_pos[pos].x];
						complex<T> b=data[sample_pos[pos].y];
						t_out[k] = a + (fft_inv_w[pos]  * b);
						t_out[k+1] = a - (fft_inv_w[pos]  * b);
					}
					else
					{
						unsigned int ppozx = sample_pos[pos].x;
						unsigned int ppozy = sample_pos[pos].y;
						complex<T> a = t_out[ppozx];
						complex<T> b = t_out[ppozy];

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

		template <typename T>
			void do_inv_fft(vector<complex<T>> &data,vector<complex<T>> &out)		
			{
				vector<complex<T>> t_out;
				t_out.resize(nPoints);
				out.resize(nPoints);

				for (int j = nFFTIterations-1;j>=0;--j){
					for (int k=0;k<nPoints-1;k+=2){
						const int pos = j*nPoints+k;
						if (j==nFFTIterations-1){
							complex<T> a=data[sample_pos[pos].x];
							complex<T> b=data[sample_pos[pos].y];
							t_out[k] = a + (fft_inv_w[pos]  * b);
							t_out[k+1] = a - (fft_inv_w[pos]  * b);
						}
						else
						{
							unsigned int ppozx = sample_pos[pos].x;
							unsigned int ppozy = sample_pos[pos].y;
							complex<T> a = t_out[ppozx];
							complex<T> b = t_out[ppozy];

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
};
