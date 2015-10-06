#include "benchmark_timer.hxx"
#include <iostream>

benchmark_timer::benchmark_timer(){
	m_start = clock();
}

void benchmark_timer::reset(){
	m_start = clock();
}

void benchmark_timer::print(){
	const int clocks = clock()-m_start;
	std::cout<<"Time elapsed: "<< clocks/float(CLOCKS_PER_SEC)<< " ( " << clocks << " clocks)"<<std::endl;
}
