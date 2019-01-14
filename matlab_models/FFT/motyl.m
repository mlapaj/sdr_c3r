close all;
clear all;

N = 1024;
disp('to jest motyl');
dane = rand(1,N);
wynik = zeros(1,N);

rozmiar = N;
ileIteracji = log2(N);
tab = zeros(N,ileIteracji);
tab(:,1) = 1:N';

for j=1:ileIteracji-1
	odd = 2:2:rozmiar;
	even = 1:2:rozmiar;
	mytab = []; % zoptymalizowac
	for k=0:(N/rozmiar)-1
        mytab = [mytab; tab(even + k*rozmiar,j); tab(odd  + k*rozmiar,j)];
	end
	tab(:,j+1) = mytab;
    rozmiar = rozmiar / 2;
end

wsp = zeros(N,ileIteracji);
wsp(:,1) = tab(:,1);
podzial = N / 2;
for j=1:ileIteracji
		doZapisu = []; % do zrobienia jutro
	if	j==1
		wsp(:,j) =[zeros(podzial,1); wsp(1:podzial,j)]; % bierzemy sobie pierwsza polowke
	else
	    % dzielimy to na parzyste i nieparzyste
		toAdd = wsp(size(wsp,1)+1-podzial:size(wsp,1),j-1);
		even = 1:2:size(toAdd,1);		
		dodanie = [];
		for k=1:N/podzial
			dodanie = [dodanie; zeros(podzial/2,1); toAdd(1:size(toAdd,1)/2) ];
		end		
		wsp(:,j) = dodanie;
		podzial = podzial / 2;
	end;
end


tic
doKtorej = 2;
wynik2 = fft(dane,N);
for j=ileIteracji:-1:1		
    for k=1:2:N
	   pozx = tab(k,j);
	   pozy = tab(k+1,j);
	   if (j==ileIteracji)           
           a = dane(pozx);
           b = dane(pozy);
           potega = (wsp(k+1,j)-1);
           omega = exp( (-1i * 2* pi * potega) / doKtorej);
           wynik(k) =  a + (omega * b);
           wynik(k+1) = a - (omega * b);
       else
           %ppozx = pozx;
           ppozx = find(tab(:,j+1) == pozx);
           ppozy = find(tab(:,j+1) == pozy);
           %ppozy = pozy;
           a = wynik(ppozx);
           b = wynik(ppozy);
	   	   potega = (wsp(ppozy,j)-1);
           omega = exp( (-1i * 2 * pi * potega) / doKtorej);
           w = a + (omega * b);
           wynik(ppozx) =  w;
           w = a - (omega * b);
           wynik(ppozy) = w;
       end
    end
    doKtorej = doKtorej*2;
end
toc


out = zeros(N,1);
tolerance = 0.0001;
for i = 1:N
	za = wynik(i);
	zb = wynik2(i);
	out(i) = abs(real(za-zb)) < tolerance && abs(imag(za - zb)) < tolerance ;
end

