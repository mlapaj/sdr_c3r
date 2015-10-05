#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
#include <complex>
#include <vector>
#include "../MISC/benchmark_timer.hxx"

using namespace std;
using namespace log4cplus;

class fourier{
	private:
		// for fourier math
		int nPoints;
		complex<double> w;
		// other
		Logger logger = Logger::getInstance("fourier");
	public:
		fourier(int nPoints);
		void do_fourier(vector<double> data,vector<complex<double>> &out);
		void do_fft(vector<double> data,vector<complex<double>> &out);
};
