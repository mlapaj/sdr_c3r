#include "convolution.hxx"

convolution::convolution(vector<double> impulse):response(impulse){

}


convolution::~convolution(){

}

void convolution::do_conv(vector<double> data){
	vector<double> ret(data.size()+response.size()-1);
	int n = 0;
	int M = response.size()/2;
	for (int n=0;n<ret.size();n++)
	{
		//cout << "!";
		for (int m=-M;m<=M;m++){
//			cout<< m << " ";
			int index = n - m;
			cout << index << " ";
			if ((index) < ( data.size()) && ((index) >= 0)){
				ret[n] += data[index] * response[m]; 			
				cout << "*";
			}
		}
		cout << "!!!!!!!!!!!!!!!!!!!!!! n: " << n << "out: "<< ret[n] << endl<< endl;
	}
}



void convolution::do_fft_conv(vector<double> data){

}
