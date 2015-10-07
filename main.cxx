#include <iostream>

#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
#include <vector>
#include <limits>


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

	int nPoints;
	cout << "Starting app.." << endl;
	for (int nPoints=2;nPoints<8192;nPoints = nPoints *2)
	{
		cout << "********** fourier complex " << nPoints << " points **********************" << fixed  << endl;
		vector<complex<double>> data_complex;
		vector<complex<double>> out1_complex;
		vector<complex<double>> out2_complex;
		vector<complex<double>> out3_complex;
		vector<complex<double>> out4_complex;
		csv::read("testcx",data_complex,nPoints);
	//		for (const complex<double> i : data_complex){
	//			cout << i << " " << endl;
	//		}
		fourier ocFourier(nPoints);
		cout << "fourier" << endl;
		ocFourier.do_fourier(data_complex,out1_complex);
	//	for (const complex<double> i : out1_complex){
	//		cout << i << " " << endl;
	//	}

		cout << "inv_fourier" << endl;
		ocFourier.do_inv_fourier(out1_complex,out2_complex);
	//	for (const complex<double> i : out2_complex){
	//		cout << i << " " << endl;
	//	}
		for (int x=0;x<data_complex.size();x++)
		{
			if (abs(data_complex[x]-out2_complex[x]) > 0.00001 ){
				cout << "!error! ";
				cout << "dane: " << data_complex[x] << " out2: " << out2_complex[x] << endl;
				return -1;
			}
		}

		cout << "fft" << endl;
		ocFourier.do_fft(data_complex,out3_complex);
	//	for (const complex<double> i : out3_complex){
	//		cout << i << " " << endl;
	//	}

		cout << "inv_fft" << endl;
		ocFourier.do_inv_fft(out3_complex,out4_complex);
	//	for (const complex<double> i : out4_complex){
	//		cout << i << " " << endl;
	//	}

		for (int x=0;x<data_complex.size();x++)
		{
			if (abs(data_complex[x]-out4_complex[x]) > 0.00001 ){
				cout << "!error! ";
				cout << "dane: " << data_complex[x] << " out2: " << out4_complex[x] << endl;
				return -1;
			}
		}
	}

	return 0;




	for (nPoints=2;nPoints<=4096;nPoints = nPoints * 2)
	{
		cout << "calculating FFT for " << nPoints << " points." << fixed <<endl;
		fourier oFourier(nPoints);
		vector<double> dane;
		vector<complex<double>> out1;
		vector<double> out2;
		vector<complex<double>> out3;
		vector<double> out4;
		csv::read("test",dane,nPoints);
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

		for (int x=0;x<dane.size();x++)
		{
			if (abs(dane[x]-out2[x]) > 0.00001 ){
				cout << "!error! ";
				cout << "dane: " << dane[x] << " out2: " << out2[x] << endl;
				return -1;
			}
		}

		oFourier.do_fft(dane,out3);

//		for (const complex<double> i : out3){
//			cout << i << endl;
//		}

		oFourier.do_inv_fft(out3,out4);


		for (int x=0;x<dane.size();x++)
		{
			if (abs(dane[x]-out4[x]) > 0.00001 ){
				cout << "!error! ";
				cout << "dane: " << dane[x] << " out2: " << out2[x] << endl;
				return -1;
			}
		}

//		for (const double i : out4){
//			cout << i << endl;
//		}
	}
	
	LOG4CPLUS_DEBUG(log, "This is a bool: " << true);

	cout << "Ending app.." << endl;
}
