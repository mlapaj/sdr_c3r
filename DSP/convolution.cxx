#include "convolution.hxx"
#include <algorithm>

convolution::convolution(vector<double> impulse):response(impulse){
//	reverse(response.begin(),response.end());
}


convolution::~convolution(){

}

void convolution::do_conv(vector<double> data,vector<double> &out){
/*
	for (double d: data){
		cout << d << " " << endl;
	}
	cout << endl;
	for (double d: response){
		cout << d << " " << endl;
	}
*/
	out.resize(data.size()+response.size()-1);
	int dataLength =data.size();
	int retLength = out.size();
	int responseLength = response.size();
	cout << "data size: " << dataLength << " response size: " << responseLength << "out size:" << retLength << endl;
	for (int i=0;i<retLength;i++){
		double val = 0;
		for(int j=0;j<responseLength;j++)
		{
			if (i-j>=0 && i-j < dataLength){
				val += data[i-j] * response[j];
			}
		}
		out[i] = val;	
	}


}
	



void convolution::do_fft_conv(vector<double> data,vector<double> &out){

}
