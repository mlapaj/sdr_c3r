#pragma once
#include <vector>
#include <complex>
using namespace std;

class radioSignal
{
public:
	virtual void getSignal(vector<complex<double>> &out) = 0;
	virtual bool isTunable() = 0;
	virtual ~radioSignal () {};

private:
	/* data */
};
