#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <complex>
#include <functional>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	void updateSpectrum(vector<complex<double>> spectrum);
	void updateSpectrum2(vector<complex<double>> spectrum);
	void setMinMaxFrequency(long min, long max);
	void setSelectedFrequency(long freq, long width);
    void subscribeFrequencyChange(std::function<void(long,long)> callback);
    void getSelectedWidth();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
	void handleCheckbox();
};

#endif // MAINWINDOW_H
