#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"
#include "../IO/iq_data_reader.hxx"
#include "../DSP/fourier.hxx"
#include <array>
#include <algorithm>
#include <cmath>
#include <complex>

#include <glog/logging.h>
using namespace std;
void funk(QRgb *pixels);

QSpectrum::QSpectrum(QWidget *parrent){
	DLOG(INFO) << "constructor started";
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels, width(), height()*2, QImage::Format_ARGB32);

	prepareDisplay(pixels);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 30 );
    CreatePalete();
}

int dupa;
void QSpectrum::prepareDisplay(QRgb *pixels){
	dupa = height();
}

uint8_t calcCol(int i){
	if (i<170 && i > 0)
		return sin( (i/(float)(170)) * 180 * M_PI /  (float) 180) * 255;
	else
		return 0;
}

void QSpectrum::CreatePalete(){
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	for (int i=0;i<(int) palette.size();++i){
		r = calcCol(i-170);
		g = calcCol(i-60);
		b = calcCol(i);
        //cout << "i " << i  << " r " << (int)r << " g " << (int)g << " b " << (int)b << endl;
		palette[i] = QColor(r,g,b).rgb();
	}
}

QRgb QSpectrum::getColor(unsigned char val){
	return palette.at(val);
}


bool abs_part ( const std::complex<double> & lhs ,
		const std::complex<double> & rhs)
{
	return abs(lhs) < abs(rhs);
}

vector<int> ppp_data(1024);
vector<int> pp_data(1024);
vector<int> p_data(1024);
void QSpectrum::drawLine(QRgb *pixels,vector<int> data){
		for (int x = 0; x < width() && x < data.size(); ++x) {
			int ccol = (1*data[x] + 1 * p_data[x] + 1 *pp_data[x] + 1 * ppp_data[x])/4;
			if (ccol>254) ccol=254;
//			data[x] = ccol; //dirty hack
			pixels[x] = getColor(ccol);
		}
    ppp_data = pp_data;
	pp_data = p_data;
	p_data = data;
}

fourier oFourier(1024);
iq_data_reader iq("test_data/FMcapture1.dat",1024);

long probka=0;
void QSpectrum::paintEvent(QPaintEvent *event){
	cout << "paint" << endl;
	QTime time;
	time.start();


	vector<complex<double>> x;
	vector<complex<double>> out;
	vector<int> to_display;

	for (int i=0;i<1;i++){
	iq.read_data(x);
	probka=probka+x.size();
	x.clear();
	}


	iq.read_data(x);

	for (int ii=0;ii<x.size();ii++)
	{
	   x[ii] = x[ii] * exp(complex<double>(0,-2*M_PI*(double)(178000*probka)/2500000));	
	   probka++;
	}


	oFourier.do_fft(x,out);

    rotate(out.begin(),out.begin()+out.size()/2,out.end());
	
	double maxVal = abs(*(max_element(out.begin(),out.end(),abs_part)));
	int maxiVal = 0;
	for (complex<double> x: out){
        //int val = 20 * log10(abs(x)/maxVal);
		//int val = abs(20 * log10(abs(x)/maxVal)); // *254;
		int val = (abs(x)/maxVal) *254;
		val = (val * 2) + 50;
		if (val > 254) val = 254;
//		val += 100; 
		if (abs(val)>maxiVal) maxiVal = val;
		to_display.push_back(val);
	}

	for (int i=0;i<to_display.size();i++){
	//	to_display[i] = abs(((float)to_display[i] / (float) maxiVal)) * 254;
	}


	if (dupa>=height()*2) {
		dupa = height();
		int pos_dst = 0;
		int pos_src = width() * height();
		memcpy(&pixels[pos_dst],&pixels[pos_src],width()*height()*sizeof(QRgb));
	}
    drawLine(&pixels[dupa * width()],to_display);	
	dupa+=1;
	painter.begin(this);
	painter.drawImage(0, 0, *image,0,dupa-height());
	painter.end();

	if (!( dupa % 100))
	qDebug() << "drawImage time:" << time.elapsed() / (float) 1000 << " seconds.";


}

void QSpectrum::resizeEvent(QResizeEvent* event)
{
	LOG(INFO) << "got resize event";
	timer.stop();
	delete pixels;
	delete image;
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels,width(),height()*2, QImage::Format_RGB32);
	prepareDisplay(pixels);
	timer.start(30);
	// trza dorzucic locka
	
	QWidget::resizeEvent(event);
}

void QSpectrum::changeT(){
	update();
}
