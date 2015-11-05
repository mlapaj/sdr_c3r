clear all
close all
d = csvread("shifted");
plot_FFT_IQ(d,1,.002*2.5E6/8,2.5/8,100.122,'Spectrum of decimated signal'); 