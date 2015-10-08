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
    QRgb *pixels;
	QImage *image;
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

signals:


public slots:
	void changeT();

private:
	void prepare_display(QRgb *pixels);
	/* data */
};
