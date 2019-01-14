function out = lowpass_filter (pfgraniczna,pfprobkowania,pNF,data,typ)
  disp('test');
  Nf = pNF; % filter order
  M = Nf / 2;
  wspolczynniki = Nf +1;
  fprobkowania = pfprobkowania; % 20 KHz
  fgraniczna = pfgraniczna; % 2.5 KHz
  h = zeros(1,wspolczynniki);
  
  czysrodkowy = (isequal(fix(M),M));
  h = obliczWspolczynniki(wspolczynniki,M,fgraniczna,fprobkowania,czysrodkowy,typ);
  out = filtruj(data,h,wspolczynniki);  
end

function out = obliczWspolczynniki(wspolczynniki,M,fgraniczna,fprobkowania,czysrodkowy,typ)            
    omega_c = 2 * pi * fgraniczna(1) / fprobkowania;
	h = zeros(1,wspolczynniki);
    if typ=='l'
		hd = lowPass(wspolczynniki,M,omega_c,czysrodkowy);
	end
    if typ=='h'
		hd = highPass(wspolczynniki,M,omega_c,czysrodkowy);
	end	
	
	 if typ=='b'
		
		omega2_c = 2 * pi * fgraniczna(2) / fprobkowania;
		hd = bandPass(wspolczynniki,M,omega_c,omega2_c,czysrodkowy);
     end		
    if typ=='bs'		
		omega2_c = 2 * pi * fgraniczna(2) / fprobkowania;
		hd = bandStop(wspolczynniki,M,omega_c,omega2_c,czysrodkowy);
	end	
	
    w = windowTriangle(wspolczynniki);                        
    
    %w= windowHann(wspolczynniki);
    out = w .* hd;
end

function hd = lowPass(wspolczynniki,M,omega_c,czysrodkowy)
    hd = zeros(1,wspolczynniki);
    for n=0:wspolczynniki-1
        if (n==M) && (1 == czysrodkowy)
            hd(n+1) = omega_c / pi;
        else
            hd(n+1) = sin (omega_c*((n)-M)) / (pi*((n)-M));
        end
    end;
end

function hd = highPass(wspolczynniki,M,omega_c,czysrodkowy)
    hd = zeros(1,wspolczynniki);
    for n=0:wspolczynniki-1
        if (n==M) && (1 == czysrodkowy)
            hd(n+1) = 1 - (omega_c/pi);
        else
            hd(n+1) = - (sin(omega_c*((n)-M))) / (pi * ((n)-M));
        end
    end;
end


function hd = bandPass(wspolczynniki,M,omega_c,omega2_c,czysrodkowy)
    hd = zeros(1,wspolczynniki);
    for n=0:wspolczynniki-1
        if (n==M) && (1 == czysrodkowy)
			hd(n+1) = (omega2_c - omega_c)/pi;
        else
            hd(n+1) =  ((sin(omega2_c*((n)-M))) / (pi * ((n)-M))) - ((sin(omega_c*((n)-M))) / (pi * ((n)-M)));			
            
        end
    end;
end

function hd = bandStop(wspolczynniki,M,omega_c,omega2_c,czysrodkowy)
    hd = zeros(1,wspolczynniki);
    for n=0:wspolczynniki-1
        if (n==M) && (1 == czysrodkowy)
			
			hd(n+1) = 1 - (omega2_c - omega_c)/pi;
        else
            hd(n+1) =  ((sin(omega_c*((n)-M))) / (pi * ((n)-M))) - ((sin(omega2_c*((n)-M))) / (pi * ((n)-M)));
        end
    end;
end


function w = windowTriangle(wspolczynniki)
    w = zeros(1,wspolczynniki);
    for n=0:wspolczynniki-1
        w(n+1) = 1;
    end

end

function w = windowHann(wspolczynniki)
    w = zeros(1,wspolczynniki);
    for n=0:wspolczynniki-1
        w(n+1) = 0.5*(1-cos((2*pi*n)/(wspolczynniki-1)));
    end

end


function out = filtruj(probki,h,wspolczynniki)
    figure(2);
    freqz(h);
    in = [zeros(wspolczynniki,1); probki ; zeros(wspolczynniki,1)];
    size(in,1)
	wspolczynniki
	out = zeros(size(in,1)+2*wspolczynniki,1);
	
    for n=wspolczynniki:size(in,1)
        wynik = 0;
        for k = 1:wspolczynniki
            wynik = wynik + h(k) * in(n-k+1);
        end
    out(n) = wynik;
    end
end
