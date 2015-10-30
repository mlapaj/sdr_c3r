#pragma once
#include <iostream>
#include "fourier.hxx"


class convolution{
	public:
	convolution(vector<double> response);
	void do_conv(vector<double> data,vector<double> &out);
	void do_conv(vector<complex<double>> data,vector<complex<double>> &out);
	void do_fft_conv(vector<double> data,vector<double> &out);
	~convolution();
	private:
	vector<double> response;
	vector<complex<double>> fft_response;
};
