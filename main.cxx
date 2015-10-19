#include <iostream>

#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
#include <vector>
#include <limits>

#include <qapplication.h>
#include <qlabel.h>

#include "DSP/fourier.hxx"
#include "IO/csv.hxx"
#include "IO/iq_data_reader.hxx"

#include <SDL2/SDL.h>
#include "GUI/QSpectrum.hxx"
#include <QTimer>

#define D_WIDTH 1024
#define D_HEIGHT 768


using namespace std;
using namespace log4cplus;



std::array<Uint32, 255> palette;

uint8_t calcCol(int i){
	if (i<170 && i > 0)
		return sin( (i/(float)(170)) * 180 * M_PI /  (float) 180) * 255;
	else
		return 0;
}


void CreatePalete(SDL_PixelFormat *fmt){
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	for (int i=0;i<(int) palette.size();++i){
		r = calcCol(i-170);
		g = calcCol(i-60);
		b = calcCol(i);
        cout << "i " << i  << " r " << (int)r << " g " << (int)g << " b " << (int)b << endl;
		palette[i] = SDL_MapRGB(fmt,r,g,b);
		cout << "i: " << i << " val:" << palette[i] << " r: " << r <<" g:"<<g<<" b:"<<b;
	}
}

void drawLine(Uint32 *pixels,vector<int> data){
	static unsigned char col = 0;
		for (unsigned long x = 0; x < D_WIDTH && x < data.size(); ++x) {
				pixels[x] = palette[data[x]];
		}
	col++;
	if (col>=255) col = 0;
}

bool abs_part ( const std::complex<double> & lhs ,
		const std::complex<double> & rhs)
{
	return abs(lhs) < abs(rhs);
}

int main(int argc,char **argv){
	// log configuration
	SharedAppenderPtr append(new FileAppender("sdr_c3r.log"));
	auto_ptr<Layout> layout(new log4cplus::PatternLayout("%p [%d{%H:%M:%S}] [%c] - %m%n"));
	append->setLayout(layout);
	Logger log = Logger::getRoot();
	log.addAppender(append);
	// end of log configuration

	int nPoints;
	cout << "Starting app.." << endl;

	SDL_Window* window = SDL_CreateWindow
		(
		 "Jeu de la vie", SDL_WINDOWPOS_UNDEFINED,
		 SDL_WINDOWPOS_UNDEFINED,
		 D_WIDTH,
		 D_HEIGHT,
		 SDL_WINDOW_SHOWN
		);
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	}


	SDL_Renderer* renderer = SDL_CreateRenderer( window, -1,
			SDL_RENDERER_ACCELERATED );

	SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			D_WIDTH, D_HEIGHT*2);
	Uint32 *myPixels = new Uint32[D_WIDTH * D_HEIGHT*2];

   SDL_PixelFormat *fmt = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
   CreatePalete(fmt);
/*
	SDL_RenderClear(renderer);
	for (int x = 0; x < D_WIDTH;x++){
		for (int y = 0; y < D_HEIGHT; y++)
		{
			myPixels[y*D_WIDTH+x] = rand() % 0xFFFFFFFF;
		}
	}
*/
	SDL_UpdateTexture(sdlTexture, NULL, myPixels, D_WIDTH * sizeof (Uint32));
	SDL_Rect rect;
	rect.x=0;
	rect.y=0;
	rect.w=D_WIDTH;
	rect.h=1;

	int i = 1;
	int j = 0;


	SDL_Rect rect2;
	rect2.x=0;
	rect2.y=0;
	rect2.w=D_WIDTH;
	rect2.h=D_HEIGHT;
	int dupa = 0;


	fourier oFourier(1024);
	iq_data_reader iq("FMcapture1.dat",1024);
	vector<complex<double>> x;
	vector<complex<double>> out;
	vector<int> to_display;

    j=D_HEIGHT-1;
	while(i){
		SDL_RenderClear(renderer);
		x.clear();
		iq.read_data(x);
		oFourier.do_fft(x,out);
		for (int i=0;i<10;i++){
			iq.read_data(x);
		}

		double maxVal = abs(*(max_element(out.begin(),out.end(),abs_part)));
		int maxiVal = 0;

		for (complex<double> x: out){
			int val = (abs(x)/maxVal) * 254;
			//int val = abs(20 * log10(abs(x)/maxVal)); // *254;
			val *= 5; 
			if (val > 254) val = 254;
			if (abs(val)>maxiVal) maxiVal = val;
			to_display.push_back(val);
		}

		Uint32 *pixels;
		int pitch;
		j++;
		dupa++;
		if (j>=D_HEIGHT*2) j = 0;
		if (dupa>=D_HEIGHT) {
			dupa = 0;
		}
		rect2.y=dupa;
		rect2.h=D_HEIGHT;

		rect.y = j;
		SDL_LockTexture(sdlTexture, &rect ,(void **)&pixels,&pitch);
		
		drawLine(pixels,to_display);
		to_display.clear();
		SDL_UnlockTexture(sdlTexture);
		SDL_RenderCopy(renderer, sdlTexture, &rect2, NULL);
		SDL_RenderPresent(renderer);
		SDL_Event event;
		while (i && SDL_PollEvent(&event)) {
			// handle your event here
			switch( event.type ){
				case SDL_KEYDOWN:
					printf( "Key press detected\n" );i =0 ;
					break;
					break;
			}


		}
		SDL_Delay(200);
	}


	SDL_DestroyWindow(window);
	SDL_Quit();



	cout << "Ending app.." << endl;
}
