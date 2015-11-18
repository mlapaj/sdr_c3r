#include "glog/logging.h"
#include "iq_data_reader.hxx"

iq_data_reader::iq_data_reader(string fileName, int block_size):
	file(new ifstream(fileName,ifstream::binary)),block_size(block_size)
{
	DLOG(INFO) << "constructor";
	buffer = new char[block_size * 2];
}


int iq_data_reader::read_data(vector<complex<double>> &data){
	data.clear();
	if (file->eof()) return 0;
	data.resize(block_size);
	vector<complex<double>> sample;
	complex<double> cnumber;
	unsigned char d_real,d_imag;
	file->read(buffer,block_size * 2);
	int j=0;
	for (int i=0;i<block_size*2;i+=2){
 	    d_real = buffer[i];
		d_imag = buffer[i+1];
		cnumber.real((double)d_real-127.5);
		cnumber.imag((double)d_imag-127.5);
		data[j++] = cnumber;
	}
}

iq_data_reader::~iq_data_reader(){
	DLOG(INFO) << "dectructor";
}
