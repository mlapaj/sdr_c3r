#include <gtest/gtest.h>
#include "DSP/fourier.hxx"
#include "IO/csv.hxx"
#include <vector>
#include <sstream>
const string samples_dir = "./test_data/";
const string complex_samples = "random_complex_8192";
const string complex_samples_dft = "random_complex_dft_";

using namespace std;
TEST(MathTest, Fourier_Complex) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data_complex;
		vector<complex<double>> out_complex;
		vector<complex<double>> compare_complex;
		fourier oFourier(nPoints);

		csv::read(samples_dir+complex_samples,data_complex,nPoints);

		oFourier.do_fourier(data_complex,out_complex);
		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),compare_complex,nPoints);
		EXPECT_EQ(out_complex.size(), compare_complex.size());
		for (int i=0;i<compare_complex.size();i++){
			EXPECT_NEAR(out_complex[i].real(),compare_complex[i].real(),0.00001);
			EXPECT_NEAR(out_complex[i].imag(),compare_complex[i].imag(),0.00001);
		}
	}
}


TEST(MathTest, FFT_Complex) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data_complex;
		vector<complex<double>> out_complex;
		vector<complex<double>> compare_complex;
		fourier oFourier(nPoints);

		csv::read(samples_dir+complex_samples,data_complex,nPoints);

		oFourier.do_fft(data_complex,out_complex);
		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),compare_complex,nPoints);
		EXPECT_EQ(out_complex.size(), compare_complex.size());
		for (int i=0;i<compare_complex.size();i++){
			EXPECT_NEAR(out_complex[i].real(),compare_complex[i].real(),0.0001);
			EXPECT_NEAR(out_complex[i].imag(),compare_complex[i].imag(),0.0001);
		}
	}
}

int main(int argc, char **argv) {
	// log configuration
	SharedAppenderPtr append(new FileAppender("sdr_c3r.log"));
	auto_ptr<Layout> layout(new log4cplus::PatternLayout("%p [%d{%H:%M:%S}] [%c] - %m%n"));
	append->setLayout(layout);
	Logger log = Logger::getRoot();
	log.addAppender(append);
	
	// end of log configuration
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
