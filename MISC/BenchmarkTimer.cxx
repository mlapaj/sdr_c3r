#include "BenchmarkTimer.hxx"
#include <iostream>

BenchmarkTimer::BenchmarkTimer(){
	m_start = clock();
}

void BenchmarkTimer::reset(){
	m_start = clock();
}

void BenchmarkTimer::print(){
	const int clocks = clock()-m_start;
	std::cout<<"Time elapsed: "<< clocks/float(CLOCKS_PER_SEC)<< " ( " << clocks << " clocks)"<<std::endl;
}
