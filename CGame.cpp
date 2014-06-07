#include "CGame.h"
#include "Defines.h"

const SDL_Color bgColor = MAKE_SDL_COLOR(COLOR_BG);
const SDL_Color fgColor = MAKE_SDL_COLOR(COLOR_FG);

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::handle_event(const SDL_Event* e) {
	CEvent::handle_event(e);
}

void CGame::update() {

}

void CGame::draw() {
	// fill background
	SDL_SetRenderDrawColor(_r, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_r);

	// show onscreen
	SDL_RenderPresent(_r);
}

void CGame::set_renderer(SDL_Renderer* r) {
	_r = r;
}

void CGame::OnKeyDown(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat) {
	switch (key) {
	case SDLK_q:
	case SDLK_ESCAPE:
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		SDL_PeepEvents(&quitEvent, 1, SDL_ADDEVENT, 0, 0);
		break;
	default:
		break;
	}
}
