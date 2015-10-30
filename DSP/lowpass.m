pkg load signal
clear all
close all

fs=2000; % hz
cutoff = 460; % hz
length = 21;
M = length - 1;
ft = cutoff/fs;
w_lpf = zeros(1,M);
window = zeros(1,M);
for n=0:M
    if (n==M/2)
        w_lpf(n+1) = 2 * ft;
    else
        w_lpf(n+1) =  sin(2*pi*ft*(n-M/2))/(pi*(n-M/2));
    endif
endfor

w_lpf

x = [0:20]

alfa = 0.54
beta = 1 - alfa

for n=0:M
    window(n+1) = alfa - (beta * cos ((2*pi*(n))/M));
endfor
o_lpf = fir1(20,ft*2,"low","noscale");

figure(1);
plot(x,w_lpf);

figure(2);
plot(x,window);

w_lpf = w_lpf .* window;

figure(3);
plot(x,w_lpf);


figure(4);
plot(x,o_lpf);

figure(5)
freqz(w_lpf)
figure(6)
freqz(o_lpf)