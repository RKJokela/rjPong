#ifndef CRECTENTITY_H_INCLUDED
#define CRECTENTITY_H_INCLUDED

#include <SDL.h>
#include "Interfaces.h"

class CRectEntity : public IEntity, public IMover
{
public:
	CRectEntity(double maxVelocity);
	// IEntity
	virtual void update();
	void draw(SDL_Renderer* r);
	// !IEntity

	// IMover
	void change_vel(double amt, double degrees);
	void cancel_vel();
	void accelerate(double amt);
	void decelerate(double amt);
	double get_vel() const;
	// !IMover

	void set_color(Uint8 r, Uint8 g, Uint8 b);

	const SDL_Rect* get_bounding_box() const;

	const double MAX_VELOCITY;

protected:
	double    _x;
	double    _y;
	SDL_Rect  _boundingBox;

private:
	void _update_bbox();

	double    _velocity;
	// stored in radians
	double    _direction;
	SDL_Color _drawColor;
};

#endif // !CRECTENTITY_H_INCLUDED
