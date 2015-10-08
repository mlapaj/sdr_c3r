#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"

using namespace std;

QSpectrum::QSpectrum(){
	pixels = new QRgb[1680*1050];
	image = new QImage((uchar*)pixels, 1680, 1050, QImage::Format_RGB32);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 1 );

}


void QSpectrum::paintEvent(QPaintEvent *event){

	QPainter painter(this);
	QTime time;
	time.start();
	for (int x = 0; x < 512; ++x) {
		for (int y = 0; y < 512; ++y) {
			pixels[x + y * 1680] = (0xffbd9527);// = static_cast<QRgb>(rand() % 1000000);  //(0xffbd9527);// qRgb(i+x+y);
		}
	}
	painter.drawImage(0, 0, *image);

	qDebug() << "drawImage time:" << time.elapsed() / (float) 1000 << " seconds.";


}

void QSpectrum::changeT(){
	update();
	// cout << "*";
}
