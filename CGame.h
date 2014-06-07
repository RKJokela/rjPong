#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include <SDL.h>
#include "Interfaces.h"
#include "CEvent.h"

extern const SDL_Color bgColor;
extern const SDL_Color fgColor;

class CGame : public IGameState, public CEvent
{
public:
	CGame();
	~CGame();

	// IGameState
	void handle_event(const SDL_Event* e);
	void update();
	void draw();
	void set_renderer(SDL_Renderer* r);
	// !IGameState

private:
	void OnKeyDown(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat);

	SDL_Renderer* _r;
};

#endif // !CGAME_H_INCLUDED
