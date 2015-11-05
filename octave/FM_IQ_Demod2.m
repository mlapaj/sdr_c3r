function [y_FM_demodulated] = FM_IQ_Demod2(y)
%This function demodualtes an FM signal. It is assumed that the FM signal
%is complex (i.e. an IQ signal) centered at DC and occupies less than 90%
%of total bandwidth. 


b = csvread("firls.txt");
d=y./abs(y);%normalize the amplitude (i.e. remove amplitude variations) 
rd=real(d); %real part of normalized siganl. 
id=imag(d); %imaginary part of normalized signal.  

convid = conv(id,b);
del_part = (size(convid,2) - size(id,2)) / 2
convid = convid(del_part+1:end-(del_part));

convrd = conv(rd,b);
del_part = (size(convrd,2) - size(rd,2)) / 2
convrd = convrd(del_part+1:end-(del_part));
y_FM_demodulated=(rd.*convid-id.*convrd)./(rd.^2+id.^2); %demodulate! 

end

