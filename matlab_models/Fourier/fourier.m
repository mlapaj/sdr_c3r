clear all;
close all;
nn = 1024
Nfft = 1024;
a = rand(1,nn);
N = size(a,2);

wynik = zeros(N,1);
w = e^(i*(2*pi/Nfft));
wsp = 0;
tic
for k=1:N
	wsp = 0;
	for n=1:Nfft
		wsp = wsp +  a(n) * w ^ (-k * (n-1));
	end
	wynik(N+1-k) = wsp;
end
toc
wynik2 = fft(a,Nfft);
wynik2 = wynik2';

out = zeros(Nfft,1);
tolerance = 0.0001;

for i = 1:Nfft
	za = wynik(i);
	zb = wynik2(i);
	out(i) = abs(real(za-zb)) < tolerance && abs(imag(za - zb)) < tolerance ;
end
