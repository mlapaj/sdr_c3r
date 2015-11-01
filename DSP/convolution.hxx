#pragma once
#include <iostream>
#include "fourier.hxx"
#include <algorithm>
#include <complex>

namespace convolution{
	template<typename T> void do_conv(vector<T> data, vector<double> &response,vector<T> &out){

		out.resize(data.size()+response.size()-1);
		int datalength =data.size();
		int retlength = out.size();
		int responselength = response.size();
		for (int i=0;i<retlength;i++){
			T val = 0;
			for(int j=0;j<responselength;j++)
			{
				if (i-j>=0 && i-j < datalength){
					val += data[i-j] * response[j];
				}
			}
			out[i] = val;	
		}
	}
}

namespace convolution{
	template<typename T> void do_segment_conv
		(vector<T> &overlap,vector<T> data, vector<double> &response,vector<T> &out){
		if (response.size() > data.size()){
			cout << "response size > data size !!!! wrong" << endl;
		}
		vector<T> copy_overlap = overlap;
		out.resize(data.size());
		int datalength =data.size();
		int retlength = out.size() + response.size() -1;
		int responselength = response.size();

		overlap.resize(response.size()-1);
		for (int i=0;i<retlength;i++){
			T val = 0;
			for(int j=0;j<responselength;j++)
			{
				if (i-j>=0 && i-j < datalength){
					val += data[i-j] * response[j];
				}
			}
			if (i<out.size()){
				out[i] = val;	
			}
			else if (i-out.size()<overlap.size())
			{
				overlap[i-out.size()] = val;
			}
			
		}

		for (int i=0;i<copy_overlap.size() && i < out.size();i++){
			out[i] += copy_overlap[i];
		}
	}
}
