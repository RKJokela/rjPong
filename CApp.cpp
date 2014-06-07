#include "CApp.h"

CApp::CApp() :
 _running(false),
 _window(NULL),
 _renderer(NULL) { }

int  CApp::Execute() {

	if (!init())
		return -1;

	while (_running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(&e);
	}

	cleanup();

	return 0;
}

bool CApp::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == false)
		return false;

	SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &_window, &_renderer);

	return true;
}
void CApp::handle_event(SDL_Event* Event) {
	CEvent::handle_event(Event);
}
void CApp::update() {

}
void CApp::draw() {

}
void CApp::cleanup() {
	SDL_Quit();
}

void CApp::OnExit() {
	_running = false;
}
