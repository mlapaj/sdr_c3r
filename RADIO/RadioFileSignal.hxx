#pragma once
#include <memory>
#include "RadioSignal.hxx"
#include "../IO/IqDataReader.hxx"

#include <string>
using namespace std;

class RadioFileSignal: public RadioSignal{
public:
	RadioFileSignal(string fileName,int bufferSize);
	void setThrottle(long sampleRate);
	virtual int getSignal(vector<complex<double>> &out);
	virtual long getSamplingRate();
	virtual long getSignalFrequency();
	virtual bool isTunable();
	virtual ~RadioFileSignal ();

private:
	/* for iq data reader */
	unique_ptr<IqDataReader> iq;
	long currentBlockSize;
	string currentFileName;

	bool throttle = false;
	/* for throttle */
	time_t timer;
	int sampleRate = 0; /* for sample speed settings */
	int dataSent = 0;
	int dataToSend = 0;
	/* data */
};
