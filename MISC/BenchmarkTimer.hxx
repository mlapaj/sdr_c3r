#pragma once
#include <ctime>

class BenchmarkTimer
{
public:
	BenchmarkTimer ();
	void print();
	void reset();
	virtual ~BenchmarkTimer (){};

private:
	/* data */
	time_t m_start;
};
