#include <iostream>
#include <cstdlib>
#include "QSpectrum.hxx"

using namespace std;
void funk(QRgb *pixels);

QSpectrum::QSpectrum(){
	pixels1 = new QRgb[1680*1050];
	image1 = new QImage((uchar*)pixels1, 1680, 1050, QImage::Format_RGB32);

	pixels2 = new QRgb[1680*1050];
	image2 = new QImage((uchar*)pixels2, 1680, 1050, QImage::Format_RGB32);
    funk(pixels1);
	funk(pixels2);
	connect( &timer, SIGNAL( timeout() ), SLOT( changeT() ) );
	timer.start( 32 );

}

int dupa;
void funk(QRgb *pixels){

	for (int y = 0; y < 1050; ++y) {
		for (int x = 0; x < 1680; ++x) {
			pixels[x + y * 1680] = y+dupa++; // = static_cast<unsigned char>(rand() % 255);  //(0xffbd9527);// qRgb(i+x+y);
		}
	}
}

void QSpectrum::paintEvent(QPaintEvent *event){
//    return;
	QTime time;
	time.start();
	dupa++;	
    memcpy(pixels2,pixels1,1680*1050*4);
	painter.begin(this);
	if (dupa % 2){
	painter.drawImage(0, 0, *image1);
	}else{
	painter.drawImage(0, 0, *image2);
	}

	painter.end();

	if (!( dupa % 100))
	qDebug() << "drawImage time:" << time.elapsed() / (float) 1000 << " seconds.";


}

void QSpectrum::changeT(){
	update();
	// cout << "*";
}
