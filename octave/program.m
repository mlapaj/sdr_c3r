clear all
close all

pkg load signal;
y=loadFile('FMcapture1.dat');
y = y(1:130000);
y_shifted=y.*transpose(exp(-j*2*pi*0.178E6*[1:1:length(y)]/2.5E6));  
%size(y)
plot_FFT_IQ(y,1,.002*2.5E6,2.5,100.122);
title("test");
figure(2)
plot_FFT_IQ(y_shifted,1,.002*2.5E6,2.5,100.122);
d1 = decimate(y_shifted,8,'fir'); 
figure(3)
plot_FFT_IQ(d1,1,.002*2.5E6/8,2.5/8,100.122,'Spectrum of decimated signal'); 

d2 = csvread("shifted");
figure(4)
plot_FFT_IQ(d2,1,.002*2.5E6/8,2.5/8,100.122,'Spectrum of decimated signal'); 

b = csvread("firls.txt");
figure(5)
[y_FM_demodulated1] = FM_IQ_Demod(d1); %d is the decimated signal
plot_FFT_IQ(y_FM_demodulated1,1,.05*2.5E6/8,2.5/8,0,'Spectrum of demodulated signal');

figure(6)
[y_FM_demodulated2] = FM_IQ_Demod2(d2); %d is the decimated signal
plot_FFT_IQ(y_FM_demodulated2,1,.05*2.5E6/8,2.5/8,0,'Spectrum of demodulated signal');
