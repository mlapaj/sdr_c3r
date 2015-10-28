#pragma once
#include <memory>
#include "radioSignal.hxx"
#include "../IO/iq_data_reader.hxx"

#include <string>
using namespace std;

class radioFileSignal: public radioSignal{
public:
	radioFileSignal(string fileName,int bufferSize);
	virtual void getSignal(vector<complex<double>> &out);
	virtual bool isTunable();
	virtual ~radioFileSignal ();

private:
	unique_ptr<iq_data_reader> iq;
	/* data */
};
