#pragma once
#include "filter.hxx"
#include "convolution.hxx"

#include <iostream>
#include <vector>
#include <complex>
using namespace std;

namespace decimate{
	void decimate(const vector<complex<double>> &in,vector<complex<double>> &out, int factor);

	template<typename T>
	class segment_decimate{
		public:
			segment_decimate(int factor):factor(factor)
			{
				filter_coeff = filter::fir_lowpass(16,1/double(factor*4));
			}
			void decimate(vector<T> &in,vector<T> &out){
				convolution::do_segment_conv(overlap,in,filter_coeff,out,factor);
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

