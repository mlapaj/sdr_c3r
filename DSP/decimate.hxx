#pragma once
#include "filter.hxx"
#include "convolution.hxx"

#include <iostream>
#include <vector>
#include <complex>
using namespace std;

namespace decimate{
	void decimate(vector<complex<double>> in,vector<complex<double>> &out, int factor);
	template<typename T>
	class segment_decimate{
		public:
			segment_decimate(int factor):factor(factor)
			{
				filter_coeff = filter::fir_lowpass(32,1/double(factor*8));
			}
			void decimate(vector<T> &in,vector<T> &out){
				vector<T> filtered;
				convolution::do_segment_conv(overlap,in,filter_coeff,filtered);
				out.clear();
				for (int i=0;i<in.size();i+=factor){
					out.push_back(filtered[i]);
				}
			}
			void clear_overlap(){
				overlap.clear();
			}
		private:
			vector<double> filter_coeff;
			vector<T> overlap;
			int factor;
	};
}

