#pragma once
#include <vector>
#include <complex>
using namespace std;

class RadioSignal
{
public:
	virtual int getSignal(vector<complex<double>> &out) = 0;
	virtual bool isTunable() = 0;
	virtual long getSamplingRate() = 0;
	virtual long getSignalFrequency() = 0;
	virtual ~RadioSignal () {};

private:
	/* data */
};
