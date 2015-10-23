#pragma once
#include <iostream>
#include "fourier.hxx"


class convolution{
	public:
	convolution(vector<double> response);
	void do_conv(vector<double> data);
	void do_fft_conv(vector<double> data);
	~convolution();
	private:
	vector<double> response;
	vector<complex<double>> fft_response;
};
