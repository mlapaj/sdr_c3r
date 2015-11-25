#include "glog/logging.h"
#include "IqDataReader.hxx"

IqDataReader::IqDataReader(string fileName, long block_size,bool repeat):
	file(new ifstream(fileName,ifstream::binary)),block_size(block_size),repeat(repeat)
{
	DLOG(INFO) << "constructor";
	buffer = new char[block_size * 2];
}


int IqDataReader::readData(vector<complex<double>> &data,int count){
	int toRead = block_size;
	if (count){
		toRead = count;
	}

	if (file->eof()){
		if (repeat){
			file->clear();
			file->seekg(0,ios::beg);
		}
		else
		{
			return -1;
		}
	}

	vector<complex<double>> sample;
	complex<double> cnumber;
	unsigned char d_real,d_imag;
	file->read(buffer,toRead * 2);
	int complexRead = 0;
	for (int i=0;i<toRead*2;i+=2){
 	    d_real = buffer[i];
		d_imag = buffer[i+1];
		cnumber.real((double)d_real-127.5);
		cnumber.imag((double)d_imag-127.5);
		data.push_back(cnumber);
		complexRead++;
	}
	return complexRead;
}

IqDataReader::~IqDataReader(){
	DLOG(INFO) << "dectructor";
}
