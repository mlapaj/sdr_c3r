#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"
#include <QGraphicsBlurEffect>
#include "../IO/iq_data_reader.hxx"
#include "../DSP/fourier.hxx"
#include <algorithm>
#include <cmath>

using namespace std;
void funk(QRgb *pixels);

QSpectrum::QSpectrum(){
	setAttribute(Qt::WA_OpaquePaintEvent);
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels,width(),height()*2, QImage::Format_RGB32);
	image2 = new QImage(width(),height(), QImage::Format_RGB32);
	prepareDisplay(pixels);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 5 );
	connect( &timer2, SIGNAL( timeout() ), SLOT( drawVideo() ) );
	timer2.start( 60 );
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
        cout << "i " << i  << " r " << (int)r << " g " << (int)g << " b " << (int)b << endl;
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


void QSpectrum::drawLine(QRgb *pixels,vector<int> data){
	static unsigned char col = 0;
		for (int x = 0; x < width() && x < data.size(); ++x) {
				pixels[x] = getColor(data[x]);
		}
	col++;
	if (col>=255) col = 0;
}

fourier oFourier(1024);
iq_data_reader iq("FMcapture1.dat",1024);

void QSpectrum::paintEvent(QPaintEvent *event){

	painter.begin(this);
    painter.fillRect(0, 0, width(), height(), Qt::green);
	painter.drawImage(0, 0, *image2,0,0);
	painter.end();

}

void QSpectrum::resizeEvent(QResizeEvent* event)
{
	cout << "resize!" << endl;
	timer2.stop();
	timer.stop();
	delete pixels;
	delete image;
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels,width(),height()*2, QImage::Format_RGB32);
	image2 = new QImage(width(),height(), QImage::Format_RGB32);
	prepareDisplay(pixels);
	timer.start(80);
	timer2.start(80);
	// trza dorzucic locka
	
	QWidget::resizeEvent(event);
}

void QSpectrum::changeT(){
	update();
}

void QSpectrum::drawVideo(){

	QTime time;
	time.start();
	vector<complex<double>> x;
	vector<complex<double>> out;
	vector<int> to_display;
	iq.read_data(x);
	oFourier.do_fft(x,out);
	for (int i=0;i<10;i++){
	iq.read_data(x);
	}
	
	double maxVal = abs(*(max_element(out.begin(),out.end(),abs_part)));
	int maxiVal = 0;
	for (complex<double> x: out){
        int val = (abs(x)/maxVal) * 254;
		//int val = abs(20 * log10(abs(x)/maxVal)); // *254;
		val *= 5; 
		if (val > 254) val = 254;
		if (abs(val)>maxiVal) maxiVal = val;
		to_display.push_back(val);
	}

	for (int i=0;i<to_display.size();i++){
	//	to_display[i] = abs(((float)to_display[i] / (float) maxiVal)) * 254;
	}

    for (int ja=0;ja<1;ja++)
	{
    drawLine(&pixels[dupa * width()],to_display);
	dupa+=1;
	if (dupa>=height()*2) {
		dupa = height();
		int pos_dst = 0;
		int pos_src = width() * height();
		memcpy(&pixels[pos_dst],&pixels[pos_src],width()*height()*sizeof(QRgb));
	}
	}
	if (!( dupa % 100))
	qDebug() << "drawImage time:" << time.elapsed() / (float) 1000 << " seconds.";
	
	painter.begin(image2);
	painter.drawImage(0, 0, *image,0,dupa-height());
	painter.end();

}
