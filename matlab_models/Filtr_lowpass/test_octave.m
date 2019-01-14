clc
clear all;
close all;
inSound = wavread('sound3.wav');
Fs = 44100;
N = 10;
params = [8000]
paramsForFir = params ./ (Fs/2)

filtr = fir1 (N, paramsForFir, "low", ones(N+1,1)); % "noscale"
freqz(filtr);
outSound = lowpass_filter(params,Fs,N,inSound,'l');

x = 0:255;
x = x./255 .* 44;
pierwfft = fft(inSound,256);
drugfft = fft(outSound,256);

figure(2);
plot(x(1:128),abs(pierwfft(1:128)));
figure(3);
plot(x(1:128),abs(drugfft(1:128)));
