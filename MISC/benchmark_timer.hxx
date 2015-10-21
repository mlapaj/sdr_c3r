#pragma once
#include <ctime>

class benchmark_timer
{
public:
	benchmark_timer ();
	void print();
	void reset();
	virtual ~benchmark_timer (){};

private:
	/* data */
	time_t m_start;
};
