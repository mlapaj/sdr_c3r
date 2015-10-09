#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"

using namespace std;
void funk(QRgb *pixels);

QSpectrum::QSpectrum(){
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels, width(), height()*2, QImage::Format_ARGB32);

	prepareDisplay(pixels);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 32 );
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

void QSpectrum::drawLine(QRgb *pixels){
	static unsigned char col = 0;
		for (int x = 0; x < width(); ++x) {
				pixels[x] = getColor(col);
		}
	col++;
	if (col>=255) col = 0;
}

void QSpectrum::paintEvent(QPaintEvent *event){
	QTime time;
	time.start();

	if (dupa>=height()*2) {
		dupa = height();
		int pos_dst = 0;
		int pos_src = width() * height();
		memcpy(&pixels[pos_dst],&pixels[pos_src],width()*height()*sizeof(QRgb));
	}
    drawLine(&pixels[dupa * width()]);	
	dupa+=1;
	painter.begin(this);
	painter.drawImage(0, 0, *image,0,dupa-height());
	painter.end();

	if (!( dupa % 100))
	qDebug() << "drawImage time:" << time.elapsed() / (float) 1000 << " seconds.";


}

void QSpectrum::resizeEvent(QResizeEvent* event)
{
	cout << "resize!" << endl;
	timer.stop();
	delete pixels;
	delete image;
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels,width(),height()*2, QImage::Format_RGB32);
	prepareDisplay(pixels);
	timer.start(32);
	// trza dorzucic locka
	
	QWidget::resizeEvent(event);
}

void QSpectrum::changeT(){
	update();
}
