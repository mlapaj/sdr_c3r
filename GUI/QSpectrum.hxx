#include <QtGui>
#include <QWidget>
#include <QObject>
#include <memory>
// http://www.kuqin.com/qtdocument/designer-manual-6.html

using namespace std;

class QSpectrum: public QWidget
{
	Q_OBJECT
public:
	QSpectrum ();
	virtual ~QSpectrum (){
	}

protected:
	QPainter painter;
	QTimer timer;
	QTimer timer2;
    QRgb *pixels;
	QImage *image;
	QImage *image2;
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void CreatePalete();
	QRgb getColor(unsigned char val);

signals:


public slots:
	void changeT();
	void drawVideo();

private:
	std::array<QRgb, 255> palette;
	void prepareDisplay(QRgb *pixels);
	void drawLine(QRgb *pixels,vector<int> data);
	/* data */
};
