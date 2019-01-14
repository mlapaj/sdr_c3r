bod = 20;
fs = 44100; %100KHz sampling frequency
f1 = 800; %1KHz signal frequency
f2 = 600; %1KHz signal frequency
t1 = fs / bod; % czas trwania jednego symbolu modulacji
t1_sek = 1 / 20;

dane = dlmread ("myfile.csv", ",");
nsamples = size(dane,2) * t1;
t = 1:nsamples;
x = zeros(size(t,2),1);
%x = sin(2*pi*f1*(0:1/fs:1))';
for i = 0 : size(dane,2) - 1
	if (dane(i+1) == 0) 
		x((t1 * i) +1 : (t1 *(i+1))) = sin(2*pi*f1*(0:t1_sek/(t1-1):t1_sek))';
	else
		x((t1 * i) +1 : (t1 *(i+1))) = sin(2*pi*f1*(0:t1_sek/(t1-1):t1_sek) + pi)';
	end
end

wavwrite(x, fs, "out.wav")
% sin(2*pi*f*t1);
% sin(2*pi*f*t1);
%x = sin(2*pi*f*t);
plot(t,x)