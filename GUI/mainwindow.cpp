#include "mainwindow.h"
#include "QSpectrum.hxx"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	connect(ui->checkBox, SIGNAL (released()), this, SLOT (handleCheckbox()));
	
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSpectrum(vector<complex<double>> spectrum){
	ui->qspectrum->addSpectrumData(spectrum);
}

void MainWindow::updateSpectrum2(vector<complex<double>> spectrum){
	ui->qspectrum2->addSpectrumData(spectrum);
}

void MainWindow::handleCheckbox(){
	if (!ui->checkBox->isChecked()){
		ui->qspectrum->setZeroAtCenter(true);
	}
	else
	{
		ui->qspectrum->setZeroAtCenter(false);
	}
	cout << "!!!" << endl;
}

void MainWindow::setMinMaxFrequency(long min, long max){
	ui->qspectrum->setMinMaxFrequency(min,max);
}

void MainWindow::setSelectedFrequency(long freq, long width){
	ui->qspectrum->setSelectedFrequencyAndWidth(freq,width);
}

void MainWindow::subscribeFrequencyChange(std::function<void(long,long)> callback){
	ui->qspectrum->subscribeFrequencyChange(callback);
}
