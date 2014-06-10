#include "CRectEntity.h"
#include "Utilities.h"
#include <cmath>

using namespace std;

CRectEntity::CRectEntity(double maxVel) :
MAX_VELOCITY(maxVel),
_velocity(0.0),
_direction(0.0),
_x(0.0),
_y(0.0) {
	_drawColor.r = 0;
	_drawColor.g = 0;
	_drawColor.b = 0;
	_drawColor.a = SDL_ALPHA_OPAQUE;
	_boundingBox.x = 0;
	_boundingBox.y = 0;
	_boundingBox.w = 0;
	_boundingBox.h = 0;
}

void CRectEntity::update() {
	double vx = _velocity*cos(_direction);
	double vy = _velocity*sin(_direction);
	_x += vx;
	_y += vy;
	_update_bbox();
}

void CRectEntity::draw(SDL_Renderer* r) {
	// keep old color
	SDL_Color save;
	SDL_GetRenderDrawColor(r, &save.r, &save.g, &save.b, &save.a);
	// draw colored rectangle
	SDL_SetRenderDrawColor(r, _drawColor.r, _drawColor.g, _drawColor.b, _drawColor.a);
	SDL_RenderFillRect(r, &_boundingBox);
	// reset color
	SDL_SetRenderDrawColor(r, save.r, save.g, save.b, save.a);
}

void CRectEntity::change_vel(double amt, double dir) {
	// convert to radians
	dir = dir * M_PI / 180.0;
	// get x & y components
	double vx0 = _velocity*cos(_direction);
	double vy0 = _velocity*sin(_direction);
	double vx1 = amt*cos(dir);
	double vy1 = amt*sin(dir);
	// add new velocity
	vx1 += vx0;
	vy1 += vy0;
	// get new direction
	_direction = atan2(vy1, vx1);
	// get new velocity
	_velocity = sqrt(vx1*vx1 + vy1*vy1);
	// clamp to max vel
	_velocity = CLAMP(_velocity, 0.0, MAX_VELOCITY);
}

void CRectEntity::cancel_vel() {
	_velocity = 0.0;
}

void CRectEntity::accelerate(double amt) {
	_velocity = CLAMP(_velocity + amt, 0.0, MAX_VELOCITY);
}

void CRectEntity::decelerate(double amt) {
	_velocity = CLAMP(_velocity - amt, 0.0, MAX_VELOCITY);
}

double CRectEntity::get_vel() const {
	return _velocity;
}

void CRectEntity::set_color(Uint8 r, Uint8 g, Uint8 b) {
	_drawColor.r = r;
	_drawColor.g = g;
	_drawColor.b = b;
}

const SDL_Rect* CRectEntity::get_bounding_box() const {
	const SDL_Rect* pBB = &_boundingBox;
	return pBB;
}

void CRectEntity::_update_bbox() {
	_boundingBox.x = (int)round(_x);
	_boundingBox.y = (int)round(_y);
}
