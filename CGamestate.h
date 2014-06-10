#ifndef CGAMESTATE_H_INCLUDED
#define CGAMESTATE_H_INCLUDED

#include <SDL.h>
#include "Interfaces.h"

union GameInputs {
	struct menu {
		bool confirm;
		bool cancel;
	} menu;
	struct game {
		bool l_up;
		bool l_down;
		bool r_up;
		bool r_down;
	} game;
};

class CGameState
{
public:
	typedef struct _inputNode {
		ITakesInput* entity;
		_inputNode*  next;
	} inputNode, *inputNodePtr;

	virtual void handle_event(const SDL_Event* e) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void set_renderer(SDL_Renderer* r) = 0;

protected:
	inputNodePtr _listInputHandlers;
};

#endif // !CGAMESTATE_H_INCLUDED
