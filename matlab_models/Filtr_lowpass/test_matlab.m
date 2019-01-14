clc
clear all;
close all;
inSound = audioread('spectrum.wav');
Fs=44100;
x = [600 1000];
outSound1 = lowpass_filter(x,Fs,20,inSound,'b');
wavwrite(outSound1,Fs,'out1.wav')

x = [1950 2400];
outSound2 = lowpass_filter(x,Fs,60,inSound,'b');
wavwrite(outSound2,Fs,'out2.wav')

x = 0:512;
x = x./512 .* 44;
inFFT = fft(inSound,512);
pierwOutFFT = fft(outSound1,256);
drugOutFFT = fft(outSound2,256);



figure(1);
plot(x(1:128),abs(inFFT(1:128)));
figure(2);
plot(x(1:128),abs(pierwOutFFT(1:128)));
figure(3);
plot(x(1:128),abs(drugOutFFT(1:128)));
