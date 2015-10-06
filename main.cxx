#include <iostream>

#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
#include <vector>


#include "DSP/fourier.hxx"
#include "IO/csv.hxx"

using namespace std;
using namespace log4cplus;

int main(){
	// log configuration
	SharedAppenderPtr append(new FileAppender("sdr_c3r.log"));
	auto_ptr<Layout> layout(new log4cplus::PatternLayout("%p [%d{%H:%M:%S}] [%c] - %m%n"));
	append->setLayout(layout);
	Logger log = Logger::getRoot();
	log.addAppender(append);
	// end of log configuration

	cout << "Starting app.." << endl;

	int nPoints = 4;
	for (nPoints=2;nPoints<=8192;nPoints = nPoints * 2)
	{
		cout << "calculating FFT for " << nPoints << " points." << fixed <<endl;
		fourier oFourier(nPoints);
		vector<double> dane;
		vector<complex<double>> out1;
		vector<double> out2;
		vector<complex<double>> out3;
		vector<double> out4;
		csv::read_double("test",dane,nPoints);
//		for (const double i : dane){
//			cout << i << " " << endl;
//		}

		oFourier.do_fourier(dane,out1);
//		    for (const complex<double> i : out1){
//				cout << fixed  << i << endl;
//			}

		oFourier.do_inv_fourier(out1,out2);
//		cout << "inv" << endl;
//		    for (const double i : out2){
//				cout << fixed  << i << endl;
//			}

		oFourier.do_fft(dane,out3);

//		for (const complex<double> i : out3){
//			cout << i << endl;
//		}

		oFourier.do_inv_fft(out3,out4);

//		for (const double i : out4){
//			cout << i << endl;
//		}
	}
	
	LOG4CPLUS_DEBUG(log, "This is a bool: " << true);

	cout << "Ending app.." << endl;
}
