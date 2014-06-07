#ifndef CGAME_H_INCLUDED
#define CGAME_H_INCLUDED

#include <SDL.h>
#include "Interfaces.h"

class CGame : public IGameState
{
public:
	CGame();
	~CGame();

	void handle_event(const SDL_Event& e);
	void update();
	void draw();

private:

};

#endif // !CGAME_H_INCLUDED
