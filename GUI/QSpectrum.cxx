#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <complex>

#include <glog/logging.h>
using namespace std;
void funk(QRgb *pixels);
#define D_WIDTH 1024
QSpectrum::QSpectrum(QWidget *parent):QWidget(parent){
	DLOG(INFO) << "constructor started";
	pixels = new QRgb[D_WIDTH*height()*2];
	image = new QImage((uchar*)pixels, D_WIDTH, height()*2, QImage::Format_ARGB32);

	prepareDisplay(pixels);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 10 );
    CreatePalete();
	zeroAtCenter = true;
	selectedFreqPos = 0;
	selectedFreqWidth = 0;
	canChangeSelectedFrequency = false;
}


void QSpectrum::setZeroAtCenter(bool param){
	zeroAtCenter = param;
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
		for (int x = 0; x < D_WIDTH && x < data.size(); ++x) {
			int ccol = (1*data[x] + 1 * p_data[x] + 1 *pp_data[x] + 1 * ppp_data[x])/4;
			if (ccol>254) ccol=254;
			pixels[x] = getColor(ccol);
		}
    ppp_data = pp_data;
	pp_data = p_data;
	p_data = data;
}


void QSpectrum::paintEvent(QPaintEvent *event){
	QTime time;
	if (!data.empty()){
	time.start();
	if (dupa>=height()*2) {
		dupa = height();
		int pos_dst = 0;
		int pos_src = D_WIDTH * height();
		memcpy(&pixels[pos_dst],&pixels[pos_src],D_WIDTH*height()*sizeof(QRgb));
	}
	if (zeroAtCenter)
	{
		rotate(data.front().begin(),data.front().begin()+data.front().size()/2,data.front().end());
	}
    drawLine(&pixels[dupa * D_WIDTH],data.front());	
	dataMutex.lock();
	data.pop_front();
	dataMutex.unlock();
	dupa+=1;
	}
	painter.begin(this);
	painter.scale(width()/(float)1024,1);
	painter.drawImage(0, 0, *image,0,dupa-height());
	painter.fillRect(selectedFreqPos,0,selectedFreqWidthSize,height(),QBrush(QColor(50, 50, 255, 128)));
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
	pixels = new QRgb[D_WIDTH*height()*2];
	memset(pixels,0x00,sizeof(QRgb)*D_WIDTH*height()*2);
	image = new QImage((uchar*)pixels,D_WIDTH,height()*2, QImage::Format_RGB32);
	
	updateFreqPos();
	prepareDisplay(pixels);
	timer.start(10);
	// trza dorzucic locka
	
	QWidget::resizeEvent(event);
}

void QSpectrum::changeT(){
	update();
}



void QSpectrum::addSpectrumData(vector<complex<double>> spectrumData){
	vector<int> preparedData;
	preparedData.reserve(spectrumData.size());


	double maxVal = abs(*(max_element(spectrumData.begin(),spectrumData.end(),abs_part)));
	int maxiVal = 0;
	for (complex<double> x: spectrumData){
		int val = (abs(x)/maxVal) *254;
		val = (val * 2) + 50;
		if (val > 254) val = 254;
		if (abs(val)>maxiVal) maxiVal = val;
		preparedData.push_back(val);
	}



	dataMutex.lock();
	data.push_back(preparedData);
	
	dataMutex.unlock();
	// update();
}
void QSpectrum::mousePressEvent(QMouseEvent *e){

	if(e->buttons() == Qt::LeftButton){
		int val = e->x() / (double)width() * 1024;
		if ((val > selectedFreqPos) && (val < (selectedFreqPos + selectedFreqWidthSize)))
		{
			canChangeSelectedFrequency = true;

		}
	}

}

void QSpectrum::mouseReleaseEvent(QMouseEvent *e){
	canChangeSelectedFrequency = false;
}
void QSpectrum::mouseMoveEvent(QMouseEvent *e)
{
	if (canChangeSelectedFrequency){
		int val = minFrequency + (e->x() / (double)width() * (maxFrequency-minFrequency));
		qDebug() << "!val:"<<val<<endl;
		if (freqChangeCallback)
			freqChangeCallback(val,selectedFreqWidth);
		selectedFreq = val;
		updateFreqPos();
	}
}


