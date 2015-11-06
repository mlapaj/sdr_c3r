#include <gtest/gtest.h>
#include "DSP/fourier.hxx"
#include "DSP/fft.hxx"
#include "DSP/convolution.hxx"
#include "IO/csv.hxx"
#include "MISC/benchmark_timer.hxx"

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
		benchmark_timer t;
		oFourier.do_fourier(data,out);
		t.print();
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
		benchmark_timer t;
		oFourier.do_fourier(data,out);
		t.print();
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

		benchmark_timer t;
		oFourier.do_inv_fourier(data,out);
		t.print();
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

		benchmark_timer t;
		oFourier.do_inv_fourier(data,out);
		t.print();
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
		fft oFFT(nPoints);

		csv::read(samples_dir+complex_samples,data,nPoints);

		benchmark_timer t;
		oFFT.do_fft(data,out);
		t.print();
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
		fft oFFT(nPoints);

		csv::read(samples_dir+samples,data,nPoints);

		benchmark_timer t;
		oFFT.do_fft(data,out);
		t.print();
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
		fft oFFT(nPoints);

		stringstream ss;
		ss << samples_dir << complex_samples_dft << nPoints;
		csv::read(ss.str(),data,nPoints);

		benchmark_timer t;
		oFFT.do_inv_fft(data,out);
		t.print();
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
		fft oFFT(nPoints);

		stringstream ss;
		ss << samples_dir << samples_dft << nPoints;
		csv::read(ss.str(),data,nPoints);

		benchmark_timer t;
		oFFT.do_inv_fft(data,out);
		t.print();
		csv::read(samples_dir+samples,compare,nPoints);
		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i],compare[i],0.00001);
		}
	}
}

TEST(DSPTest, Convolution) {

	int nPoints = 2;
	for (nPoints = 2;nPoints <= 8192; nPoints = nPoints*2)
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
		ss << samples_dir << "impulse";
		cout << ss.str() << endl;
		csv::read(ss.str(),impulse);

		benchmark_timer t;
		convolution::do_conv(data,impulse,out);
		t.print();
		cout << endl;

		ss.str("");
		ss << samples_dir << "conv_" << nPoints;
		csv::read(ss.str(),compare);

		EXPECT_EQ(out.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out[i],compare[i],0.00001);
		}
		cout << "Done testing " << nPoints << " points."<<endl;
	}
}

TEST(DSPTest, Convolution_Segment) {

	int nPoints = 256;
	for (nPoints = 256;nPoints <= 8192; nPoints = nPoints*2)
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
		ss << samples_dir << "impulse";
		cout << ss.str() << endl;
		csv::read(ss.str(),impulse);

		benchmark_timer t;
		int j = 0;
		vector<double> overlap;
		vector<double> out_final;
		while (j<data.size()){
			vector<double> data_segment;		
			for (int i=0;i<128 && j < data.size();++i){
				data_segment.push_back(data[j++]);
			}
			convolution::do_segment_conv(overlap,data_segment,impulse,out);
			out_final.insert(out_final.end(),out.begin(),out.end());
		}
		out_final.insert(out_final.end(),overlap.begin(),overlap.end());

		t.print();
		cout << endl;

		ss.str("");
		ss << samples_dir << "conv_" << nPoints;
		csv::read(ss.str(),compare);

		EXPECT_EQ(out_final.size(), compare.size());
		for (int i=0;i<compare.size();i++){
			EXPECT_NEAR(out_final[i],compare[i],0.00001);
		}
		cout << "Done testing " << nPoints << " points."<<endl;

	}
}
int main(int argc, char **argv) {
	
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
