#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include <SDL.h>

class IMover
{
public:
	virtual void change_vel(double amt, double degrees) = 0;
};

class ITakesInput
{
public:
	virtual void handle_input() = 0;
};

class IGameState
{
public:
	virtual void handle_event(const SDL_Event* e) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void set_renderer(SDL_Renderer* r) = 0;
};

#endif // !INTERFACES_H_INCLUDED
