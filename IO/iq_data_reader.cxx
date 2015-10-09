#include "iq_data_reader.hxx"


iq_data_reader::iq_data_reader(string fileName, int block_size){
	file.reset(new ifstream(fileName));
}
