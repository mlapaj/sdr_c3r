#pragma once
#include <iostream>
#include "fourier.hxx"
#include <algorithm>
#include <complex>

namespace convolution{
	template<typename T> void do_conv(const vector<T> &data,const vector<double> &response,vector<T> &out){

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
		(vector<T> &overlap,const vector<T> &data,const vector<double> &response,vector<T> &out,int every_sample=1){
		if (response.size() > data.size()){
			cout << "response size > data size !!!! wrong" << endl;
		}
		vector<T> copy_overlap = overlap;
		out.reserve(data.size()/every_sample);
		int datalength =data.size();
		int retlength = data.size() + response.size() -1;
		int responselength = response.size();

		overlap.resize(response.size()-1);
		int end = 0;
		if (every_sample == 1)
		{
			end = retlength;
		}
		else
		{
			end = data.size();
		}
			
		for (int i=0;i<end;i+=every_sample){
			T val = 0;
			for(int j=0;j<responselength;j++)
			{
				if (i-j>=0 && i-j < datalength){
					val += data[i-j] * response[j];
				}
			}
			if (out.size()<data.size()){
				out.push_back(val);
			}
			else if (i-out.size()<overlap.size())
			{
				overlap[i-out.size()] = val;
			}
			
		}

		if (every_sample != 1){
			for (int i=data.size();i<retlength;i++){
				T val = 0;
				for(int j=0;j<responselength;j++)
				{
					if (i-j>=0 && i-j < datalength){
						val += data[i-j] * response[j];
					}
				}
				if (i-out.size()<overlap.size())
				{
					overlap[i-data.size()] = val;
				}

		}

		}

		for (int i=0;i<copy_overlap.size() && i < out.size();i++){
			out[i] += copy_overlap[i];
		}
	}
	
	template<typename T> void do_segment_conv_same
		(vector<T> &overlap,const vector<T> &data,const vector<double> &response,vector<T> &out){
		if (response.size() > data.size()){
			cout << "response size > data size !!!! wrong" << endl;
		}
		vector<T> copy_overlap = overlap;
		out.clear();
		out.reserve(data.size());
		long datalength =data.size();
		long retlength = data.size() + response.size() -1;
		long responselength = response.size();

		int toDel = abs(retlength - data.size()) / 2;

		overlap.resize(response.size()-1);
		for (int i=0;i<retlength;i++){
			T val = 0;
			for(int j=0;j<responselength;j++)
			{
				if (i-j>=0 && i-j < datalength){
					val += data[i-j] * response[j];
				}
			}
			if (out.size()<data.size()){
				if (i>toDel){
					out.push_back(val);
				}
			}
			
			if (((i-data.size())>0) && (i-data.size()<overlap.size()))
			{
				overlap[data.size()-out.size()] = val;
			}
			
		}

		for (int i=0;i<copy_overlap.size() && i < out.size();i++){
			if (i>toDel){				
				out[i] += copy_overlap[i];
			}
		}
	}
}
