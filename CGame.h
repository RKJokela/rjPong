#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include <SDL.h>
#include <vector>
#include "CGamestate.h"
#include "CEvent.h"
#include "CPlayerPaddle.h"
#include "CAiPaddle.h"
#include "CBall.h"
#include "Defines.h"

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

	void start_ball();

private:
	void OnKeyDown(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat);
	void OnKeyUp  (SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat);

	void _fill_rect(const SDL_Rect* rect);
	void _fill_rects(const SDL_Rect* first, int count);
	void _draw_digit(Uint8 digit, int x, int y, int pxSize = SCORE_PX_SIZE);
	void _handle_collisions(const SDL_Rect* oldBallPos);

	CRectEntity* _paddles[2];
	CBall _ball;
	std::vector<SDL_Rect> _drawRects;
	SDL_Renderer* _r;
	GameInputs _inputs;
	int _scores[2];

	bool _waiting;
	int _waitTicks;
};

#endif // !CGAME_H_INCLUDED
