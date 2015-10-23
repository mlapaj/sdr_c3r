#include "convolution.hxx"
#include <algorithm>

convolution::convolution(vector<double> impulse):response(impulse){
}


convolution::~convolution(){

}

void convolution::do_conv(vector<double> data){
	data = {1,2,3};
	response = {1,2,3,4};
	for (double d: data){
		cout << d << " " << endl;
	}
	cout << endl;
	for (double d: response){
		cout << d << " " << endl;
	}
	vector<double> ret(data.size()+response.size()-1);
	int dataLength =data.size();
	int retLength = ret.size();
	int responseLength = response.size();
	cout << "data size: " << dataLength << " response size: " << responseLength << endl;
	for (int i=0;i<retLength;i++){
		double val = 0;
		for(int j=0;j<responseLength;j++)
		{
			if (i-j>=0 && i-j < dataLength){
				val += data[i-j] * response[j];
			}
		}
		cout << val << endl;
	}


}
	



void convolution::do_fft_conv(vector<double> data){

}
