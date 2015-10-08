#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"

using namespace std;
void funk(QRgb *pixels);

QSpectrum::QSpectrum(){
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels, width(), height()*2, QImage::Format_RGB32);

	prepare_display(pixels);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 32 );

}

int dupa;
void QSpectrum::prepare_display(QRgb *pixels){

	for (int y = 0; y < width()*2; ++y) {
		for (int x = 0; x < height(); ++x) {
			pixels[x + y * height()] = y+dupa++;
		}
	}
}

void QSpectrum::paintEvent(QPaintEvent *event){

	QTime time;
	time.start();
	dupa+=5;	
	painter.begin(this);
	painter.drawImage(0, 0, *image,0,dupa);
	if (dupa>500) dupa = 0;
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
	prepare_display(pixels);
	timer.start(32);
	// trza dorzucic locka
	
	QWidget::resizeEvent(event);
}

void QSpectrum::changeT(){
	update();
}
