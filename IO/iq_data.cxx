#include "iq_data.hxx"

iq_data::iq_data(string fileName){
	file.reset(new ifstream(fileName));

}
