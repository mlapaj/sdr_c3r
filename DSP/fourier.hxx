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
		int nFFTIterations; 
		complex<double> w;
		vector<complex<double>>  fft_w;
		vector<complex<double>>  fft_inv_w;
		struct pos{
			int x;
			int y;
		};
		vector<struct pos> sample_pos;

			;
		// other
		Logger logger = Logger::getInstance("fourier");
		void calculate_fft_ifft_matrix();
	public:
		fourier(int nPoints);
		void do_fourier(vector<double> data,vector<complex<double>> &out);
		void do_inv_fourier(vector<complex<double>> data,vector<double> &out);
		void do_fft(vector<double> data,vector<complex<double>> &out);
		void do_inv_fft(vector<complex<double>> data,vector<double> &out);
};
