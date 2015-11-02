#include "glog/logging.h"
#include "iq_data_reader.hxx"

iq_data_reader::iq_data_reader(string fileName, int block_size):
	file(new ifstream(fileName,ifstream::binary)),block_size(block_size)
{
	DLOG(INFO) << "constructor";
}


int iq_data_reader::read_data(vector<complex<double>> &data){
	data.clear();
	if (file->eof()) return 0;
	data.resize(block_size);
	vector<complex<double>> sample;
	complex<double> cnumber;
	unsigned char d_real,d_imag;
	for (int i=0;i<block_size;i++){
		file->read((char *)&d_real,sizeof(char));
		file->read((char *)&d_imag,sizeof(char));
		cnumber.real((double)d_real-127.5);
		cnumber.imag((double)d_imag-127.5);
		data[i] = cnumber;
	}
}

iq_data_reader::~iq_data_reader(){
	DLOG(INFO) << "dectructor";
}
