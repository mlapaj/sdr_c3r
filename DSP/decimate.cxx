#include "decimate.hxx"
#include "filter.hxx"
#include "convolution.hxx"

void decimate::decimate(vector<complex<double>> in,vector<complex<double>> &out, int factor){
	vector<double> filter_coeff = filter::fir_lowpass(20,1/(double)factor,10000);
	vector<complex<double>> after_conv;
	vector<complex<double>> after_dec;
	convolution::do_conv(in,filter_coeff,after_conv);
	for (int i=0;i<after_conv.size();i+=factor){
		after_dec.push_back(after_conv[i]);
	}
	out = after_dec;
}

