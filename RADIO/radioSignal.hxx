#pragma once
#include <vector>
#include <complex>
using namespace std;

class radioSignal
{
public:
	virtual vector<complex<double>> getSignal() = 0;
	virtual bool isTunable() = 0;
	virtual ~radioSignal () {};

private:
	/* data */
};
