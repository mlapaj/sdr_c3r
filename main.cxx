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

	SDL_Window* window = NULL;
    window = SDL_CreateWindow
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


    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

    // Clear winow
    SDL_RenderClear( renderer );

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

for (int i=0;i<10;i++){
 // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = 50;
    r.y = i;
    r.w = 50;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
//    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
//    SDL_RenderFillRect( renderer, &r );
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
cout << "*" << endl;
    // Render rect
}
    // Wait for 5 sec

/* or using the default masks for the depth: */
SDL_Surface *surface;
SDL_Surface *screenSurface;
screenSurface = SDL_GetWindowSurface(window);
surface = SDL_CreateRGBSurface(0,D_WIDTH,D_HEIGHT,32,0,0,0,0);

SDL_Rect source_rect;
source_rect.x = 0;
source_rect.y = 0;
source_rect.w = D_WIDTH;
source_rect.h = D_HEIGHT;


int i = 1;
    while(i){

SDL_LockSurface(surface);
for (int i=0;i<surface->w;i++){
	for (int j=0;j<surface->h;j++){
		((Uint32 *)surface->pixels)[ ( j * surface->w ) + i ] = rand() % 0xFFFFFFFF; 
	}
}
SDL_UnlockSurface(surface);
		SDL_BlitSurface(surface, &source_rect, screenSurface, NULL);    
		SDL_UpdateWindowSurface(window);
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

}


    SDL_DestroyWindow(window);
	SDL_FreeSurface(surface);
    SDL_Quit();

	//QApplication app(argc, argv);
	//QSpectrum spectrum;
    //QLabel hello("Hello world!");

	//hello.show();
	//spectrum.show();

    //return app.exec();

	cout << "Ending app.." << endl;
}
