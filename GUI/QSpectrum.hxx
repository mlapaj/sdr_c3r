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
    QRgb *pixels1;
	QImage *image1;
    QRgb *pixels2;
	QImage *image2;
	void paintEvent(QPaintEvent *event);

signals:


public slots:
	void changeT();

private:
	/* data */
};
