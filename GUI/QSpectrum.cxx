#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"

using namespace std;

QSpectrum::QSpectrum(){
	pixels = new unsigned char[1680*1050];
	image = new QImage((uchar*)pixels, 1680, 1050, QImage::Format_Indexed8);
	for(int i=0;i<256;++i) {
		image->setColor(i, qRgb(0,i,i));
	}
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 16 );

}


void QSpectrum::paintEvent(QPaintEvent *event){
//    return;
	QTime time;
	time.start();
	for (int x = 0; x < 1680; ++x) {
		for (int y = 0; y < 1050; ++y) {
			pixels[x + y * 1680] = static_cast<unsigned char>(rand() % 255);  //(0xffbd9527);// qRgb(i+x+y);
		}
	}
	painter.begin(this);
	painter.drawImage(0, 0, *image);
	painter.end();

	qDebug() << "drawImage time:" << time.elapsed() / (float) 1000 << " seconds.";


}

void QSpectrum::changeT(){
	update();
	// cout << "*";
}
