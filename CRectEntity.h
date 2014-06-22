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
	virtual void draw(SDL_Renderer* r);
	// !IEntity

	// IMover
	void change_vel(double amt, double degrees);
	void cancel_vel();
	void accelerate(double amt);
	void decelerate(double amt);
	double get_vel() const;
	// !IMover
	double get_direction() const;

	double get_x() const;
	double get_y() const;

	double get_vx() const;
	double get_vy() const;

	void set_color(Uint8 r, Uint8 g, Uint8 b);
	void set_color(Uint32 color);

	const SDL_Rect* get_bounding_box() const;

	const double MAX_VELOCITY;

protected:
	double    _x;
	double    _y;
	double    _vx;
	double    _vy;
	// stored in radians
	double    _direction;
	SDL_Rect  _boundingBox;
	SDL_Color _drawColor;

private:
	void _update_bbox();
};

#endif // !CRECTENTITY_H_INCLUDED
