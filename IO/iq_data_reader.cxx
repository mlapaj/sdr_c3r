#include "glog/logging.h"
#include "iq_data_reader.hxx"

iq_data_reader::iq_data_reader(string fileName, int block_size,long data_speed):
	file(new ifstream(fileName,ifstream::binary)),block_size(block_size),data_speed(data_speed)
{
	DLOG(INFO) << "constructor";
	buffer = new char[block_size * 2];
	timer = 0;
}

const int sampleRate = 2500000;
int dataSent = 0;
int dataToSend = 2500000;
int iq_data_reader::read_data(vector<complex<double>> &data){
	if (dataSent > sampleRate) dataSent = 0;
	int tmpToSent = 0;
	if (timer == 0){
		timer =  clock();
		return 0;
	}
	else
	{
		double val = abs((clock()-timer)/double(CLOCKS_PER_SEC));


		if (val < 1){
			tmpToSent = sampleRate * val;
			dataToSend = abs(tmpToSent - dataSent); 
			dataSent = tmpToSent;
		}
		else
		{
			if (dataSent < sampleRate){
				dataToSend = abs(sampleRate - dataSent);
			}
			// clear and starts from begining
			dataSent = 0;
			timer = clock();
		}
	}


//	data.clear();
	if (file->eof()){
		file->clear();
		file->seekg(0,ios::beg);
	}

	vector<complex<double>> sample;
	complex<double> cnumber;
	unsigned char d_real,d_imag;
	file->read(buffer,dataToSend * 2);
	// iint j=0;
	for (int i=0;i<dataToSend*2;i+=2){
 	    d_real = buffer[i];
		d_imag = buffer[i+1];
		cnumber.real((double)d_real-127.5);
		cnumber.imag((double)d_imag-127.5);
		data.push_back(cnumber);
	}
	return dataToSend;
}

iq_data_reader::~iq_data_reader(){
	DLOG(INFO) << "dectructor";
}
