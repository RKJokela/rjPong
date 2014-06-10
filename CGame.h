#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include <SDL.h>
#include "CGamestate.h"
#include "CEvent.h"
#include "CPlayerPaddle.h"

extern const SDL_Color bgColor;
extern const SDL_Color fgColor;

class CGame : public CGameState, public CEvent
{
public:
	CGame();
	~CGame();

	// CGameState
	void handle_event(const SDL_Event* e);
	void update();
	void draw();
	void set_renderer(SDL_Renderer* r);
	// !CGameState

private:
	void OnKeyDown(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat);
	void OnKeyUp  (SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat);

	CRectEntity* _paddleLeft;
	CRectEntity* _paddleRight;
	SDL_Renderer* _r;
	GameInputs _inputs;
};

#endif // !CGAME_H_INCLUDED
