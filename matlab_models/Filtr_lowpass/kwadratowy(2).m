clc
clf
clear all
close all
format long



czysrodkowy = (isequal(fix(M),M));

audio = wavread('sound3.wav');
dspaudio = zeros(size(audio,1)+2*wspolczynniki,1);

M
omega_c
czysrodkowy
w = zeros(1,wspolczynniki);

% jak wyglada funkcja okna
for n=0:wspolczynniki-1
    w(n+1) = 1;
end


hd = zeros(1,wspolczynniki);


% oblicz wspolczynniki
for n=0:wspolczynniki-1

    if czysrodkowy && n==M hd(n+1);
        hd(n+1) = omega_c / pi;
    else
        hd(n+1) = sin (omega_c*((n)-M)) / (pi*((n)-M));
    end
        
end;

% sprawdz czy mieszcza sie w zakresie abs<1
for n=0:wspolczynniki-1
    if abs(hd(n+1))>=1 disp "blad"; end
end;

h = w .* hd;
h


wynik = 0;
for n=wspolczynniki:size(audio,1)
    wynik = 0;
    for k = 1:wspolczynniki
        wynik = wynik + h(k) * audio(n-k+1);
    end
    dspaudio(n) = wynik;
end

x = [0:255];
x = x./255*2 .* 44;
pierwfft = fft(audio,256);
drugfft = fft(dspaudio,256);

figure(1);
plot(x(1:128),abs(pierwfft(1:128)));
figure(2);
plot(x(1:128),abs(drugfft(1:128)));
