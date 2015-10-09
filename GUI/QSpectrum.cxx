#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"

using namespace std;
void funk(QRgb *pixels);

QSpectrum::QSpectrum(){
	pixels = new QRgb[width()*height()*2];
	image = new QImage((uchar*)pixels, width(), height()*2, QImage::Format_ARGB32);

	prepare_display(pixels);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 32 );

}

int dupa;
void QSpectrum::prepare_display(QRgb *pixels){
	dupa = height();
}

void QSpectrum::draw_line(QRgb *pixels){
		for (int x = 0; x < width(); ++x) {
				pixels[x] = 0xf0f0f0f;
		}
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
    draw_line(&pixels[dupa * width()]);	
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
	prepare_display(pixels);
	timer.start(32);
	// trza dorzucic locka
	
	QWidget::resizeEvent(event);
}

void QSpectrum::changeT(){
	update();
}
