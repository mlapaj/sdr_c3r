classdef filtr
    %FILTR Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        Nf; % filter order
        M;
        wspolczynniki;
        fprobkowania;
        fgraniczna;
        omega_c;
        czysrodkowy;
        h;
    end
    
    methods
        function obj = filtr(fgraniczna,fprobkowania,Nf)
            obj.Nf = Nf; % filter order
            obj.M = Nf / 2;
            obj.wspolczynniki = Nf +1;
            obj.fprobkowania = fprobkowania; % 20 KHz
            obj.fgraniczna = fgraniczna; % 2.5 KHz
            obj.h = zeros(1,obj.wspolczynniki);
            obj.omega_c = 2 * pi * fgraniczna / fprobkowania;
            obj.czysrodkowy = (isequal(fix(obj.M),obj.M));
            obj.h = obj.obliczWspolczynniki();
        end
        
        function out = filtruj(obj,probki)
            in = [zeros(obj.wspolczynniki,1); probki ; zeros(obj.wspolczynniki,1)];
            out = zeros(size(in,1)+2*obj.wspolczynniki,1);
            for n=obj.wspolczynniki:size(in,1)
                wynik = 0;
                for k = 1:obj.wspolczynniki
                    wynik = wynik + obj.h(k) * in(n-k+1);
                end
            out(n) = wynik;
            end
        end
        
    end
    
    methods (Access = protected)
        function obj = splot(obj,probki)
        
        end
        
        function out = obliczWspolczynniki(obj)            
            obj.h = zeros(1,obj.wspolczynniki);
            hd = obj.lowPass();
            w = obj.windowTriangle;                        
            out = w .* hd;
        end
        
        function hd = lowPass(obj)
            hd = zeros(1,obj.wspolczynniki);
            for n=0:obj.wspolczynniki-1
                if (n==obj.M) && (1 == obj.czysrodkowy)
                    hd(n+1) = obj.omega_c / pi;
                else
                    hd(n+1) = sin (obj.omega_c*((n)-obj.M)) / (pi*((n)-obj.M));
                end
            end;
        end
        
        
        function w = windowTriangle(obj)
            w = zeros(1,obj.wspolczynniki);
            for n=0:obj.wspolczynniki-1
                w(n+1) = 1;
            end

        end
        
    end
    
end

