add_library(RADIO radio.cxx FMdecoder.cxx)
target_link_libraries (RADIO GUI IO DSP MISC) 
