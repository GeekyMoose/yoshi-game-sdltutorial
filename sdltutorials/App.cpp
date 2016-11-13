#include "App.h"

using namespace std;

App::App(){
	clog<<"[INFO] Create application."<<endl;
	isRunning = false;
	screen_width = 640;
	screen_height = 480;
}

App::~App(){
	clog<<"[INFO] Destroye application."<<endl;
}

int App::executeApp(){
	clog<<"[INFO] Start running application..."<<endl;

	//Initialize application
	if(initApp()==false){
		clog<<"[ERR] Unbale to run application (Init failed)..."<<endl;
		return -1;
	}

	//Main execution loop
	SDL_Event sdlevent;
	while(isRunning){
		while(SDL_PollEvent(&sdlevent)){
			doEvent(&sdlevent);
		}
		doLoop();
		doRender();
	}

	//Stop application
	doCleanup();
	return 0;
}

bool App::initApp(){
	//Init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)<0){
		clog<<"[ERR] :: Unable to init App. SDL_Error: "<<SDL_GetError()<<endl;
		cerr<<"Unable to init App..."<<endl;
		return false;
	}

	//Create SDL window for screen
	window = SDL_CreateWindow(
		WINDOWS_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screen_width,
		screen_height,
		SDL_WINDOW_SHOWN
	);
	if(window==NULL){
		clog<<"[ERR] :: Unable to start window. SDL_Error: "<<SDL_GetError()<<endl;
		cerr<<"Unable to init App..."<<endl;
		return false;
	}

	//Load SDL_Surface from the window
	screen = SDL_GetWindowSurface(window);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	return true;
}

void App::doEvent(SDL_Event* sdlevent){
	if(sdlevent->type==SDL_QUIT){
		isRunning = false;
	}
}

void App::doLoop(){
}

void App::doRender(){
}

void App::doCleanup(){
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
