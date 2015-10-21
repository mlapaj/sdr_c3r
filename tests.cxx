#include <gtest/gtest.h>
#include "DSP/fourier.hxx"
#include "DSP/convolution.hxx"
#include "IO/csv.hxx"
#include <vector>
#include <sstream>
const string samples_dir = "./test_data/";
const string complex_samples = "random_complex_8192";
const string samples = "random_8192";
const string complex_samples_dft = "random_complex_dft_";
const string samples_dft = "random_dft_";

using namespace std;
TEST(DSPTest, Fourier_Complex) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data;
		vector<complex<double>> out;
		vector<complex<double>> compare;
		fourier oFourier(nPoints);

		csv::read(samples_dir+complex_samples,data,nPoints);

		oFourier.do_fourier(data,out);
		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i].real(),compare[i].real(),0.00001);
			EXPECT_NEAR(out[i].imag(),compare[i].imag(),0.00001);
		}
	}
}



TEST(DSPTest, Fourier) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<double> data;
		vector<complex<double>> out;
		vector<complex<double>> compare;
		fourier oFourier(nPoints);
		csv::read(samples_dir+samples,data,nPoints);
		oFourier.do_fourier(data,out);
		stringstream ss;
		ss << samples_dir << samples_dft << nPoints;
		csv::read(ss.str(),compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i].real(),compare[i].real(),0.0001);
			EXPECT_NEAR(out[i].imag(),compare[i].imag(),0.0001);
		}
	}
}


TEST(DSPTest, Inv_Fourier_Complex) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data;
		vector<complex<double>> out;
		vector<complex<double>> compare;
		fourier oFourier(nPoints);

		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),data,nPoints);

		oFourier.do_inv_fourier(data,out);
		csv::read(samples_dir+complex_samples,compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i].real(),compare[i].real(),0.00001);
			EXPECT_NEAR(out[i].imag(),compare[i].imag(),0.00001);
		}
	}
}



TEST(DSPTest, Inv_Fourier) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data;
		vector<double> out;
		vector<double> compare;
		fourier oFourier(nPoints);

		stringstream ss;
		ss << samples_dir << samples_dft << nPoints;
		csv::read(ss.str(),data,nPoints);

		oFourier.do_inv_fourier(data,out);
		csv::read(samples_dir+samples,compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i],compare[i],0.00001);
		}
	}
}


TEST(DSPTest, FFT_Complex) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data;
		vector<complex<double>> out;
		vector<complex<double>> compare;
		fourier oFourier(nPoints);

		csv::read(samples_dir+complex_samples,data,nPoints);

		oFourier.do_fft(data,out);
		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i].real(),compare[i].real(),0.0001);
			EXPECT_NEAR(out[i].imag(),compare[i].imag(),0.0001);
		}
	}
}


TEST(DSPTest, FFT) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<double> data;
		vector<complex<double>> out;
		vector<complex<double>> compare;
		fourier oFourier(nPoints);

		csv::read(samples_dir+samples,data,nPoints);

		oFourier.do_fft(data,out);
		stringstream ss;
		ss << samples_dir << samples_dft << nPoints;
		csv::read(ss.str(),compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i].real(),compare[i].real(),0.0001);
			EXPECT_NEAR(out[i].imag(),compare[i].imag(),0.0001);
		}
	}
}

TEST(DSPTest, Inv_FFT_Complex) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data;
		vector<complex<double>> out;
		vector<complex<double>> compare;
		fourier oFourier(nPoints);

		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),data,nPoints);

		oFourier.do_inv_fft(data,out);
		csv::read(samples_dir+complex_samples,compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i].real(),compare[i].real(),0.00001);
			EXPECT_NEAR(out[i].imag(),compare[i].imag(),0.00001);
		}
	}
}


TEST(DSPTest, Inv_FFT) {
	int nPoints = 2;
	for (nPoints = 2;nPoints < 8192;nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<complex<double>> data;
		vector<double> out;
		vector<double> compare;
		fourier oFourier(nPoints);

		stringstream ss;
		ss << samples_dir << samples_dft << nPoints;
		csv::read(ss.str(),data,nPoints);

		oFourier.do_inv_fft(data,out);
		csv::read(samples_dir+samples,compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i],compare[i],0.00001);
		}
	}
}

TEST(DSPTest, Convolution) {

	int nPoints = 2;
	for (nPoints = 2;nPoints < 1024; nPoints = nPoints*2)
	{
		cout << "Testing " << nPoints << " points."<<endl;
		vector<double> data;
		vector<double> impulse;
		vector<double> out;
		vector<double> compare;

		stringstream ss;
		ss << samples_dir << samples;
		csv::read(ss.str(),data,nPoints);

		ss.str("");
		cout << ss.str() << endl;
		csv::read(ss.str(),impulse);

		convolution oConvolution(impulse);
		cout << endl;
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
