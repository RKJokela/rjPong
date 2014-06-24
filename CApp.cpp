#include "CApp.h"

CApp::CApp() :
 _running(true),
 _window(NULL),
 _renderer(NULL),
 _currentState(NULL),
 _game() { }

int  CApp::Execute() {

	if (!init())
		return -1;

	double ticks = 0;

	while (_running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(&e);

		update();
		draw();

		// wait for frame
		double elapsed = SDL_GetTicks() - ticks;
		while (elapsed < MS_PER_FRAME) {
			elapsed = SDL_GetTicks() - ticks;
		}
		ticks += elapsed;
	}

	cleanup();

	return 0;
}

bool CApp::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(_renderer, GETR(COLOR_BG), GETG(COLOR_BG), GETB(COLOR_BG), SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	_game.set_renderer(_renderer);
	_currentState = &_game;

	return true;
}
void CApp::handle_event(SDL_Event* Event) {
	if (Event->type == SDL_QUIT)
		CEvent::handle_event(Event);
	else // pass to gamestate
		_currentState->handle_event(Event);
}
void CApp::update() {
	_currentState->update();
}
void CApp::draw() {
	_currentState->draw();
}
void CApp::cleanup() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void CApp::OnExit() {
	_running = false;
}
