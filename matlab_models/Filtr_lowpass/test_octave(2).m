clc
clear all;
close all;
inSound = wavread('sound3.wav');
outSound = lowpass_filter([8000 15000],44100,20,inSound,'bs');

x = 0:255;
x = x./255 .* 44;
pierwfft = fft(inSound,256);
drugfft = fft(outSound,256);

figure(1);
plot(x(1:128),abs(pierwfft(1:128)));
figure(2);
plot(x(1:128),abs(drugfft(1:128)));
