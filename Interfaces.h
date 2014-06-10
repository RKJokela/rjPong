#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

#include <SDL.h>
union GameInputs;

class IMover
{
public:
	virtual void change_vel(double amt, double degrees) = 0;
	virtual void cancel_vel() = 0;
	virtual void accelerate(double amt) = 0;
	virtual void decelerate(double amt) = 0;

	virtual double get_vel() const = 0;
};

class IEntity
{
public:
	virtual void update() = 0;
	virtual void draw(SDL_Renderer* r) = 0;
};


class ITakesInput
{
public:
	virtual void handle_input(const GameInputs&) = 0;
};

#endif // !INTERFACES_H_INCLUDED
