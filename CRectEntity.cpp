#include "CRectEntity.h"
#include "Utilities.h"
#include "Defines.h"
#include <cmath>

using namespace std;

CRectEntity::CRectEntity(double maxVel) :
MAX_VELOCITY(maxVel),
_vx(0.0),
_vy(0.0),
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
	_x += _vx;
	_y += _vy;
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
	double vx1 = amt*cos(dir);
	double vy1 = amt*sin(dir);
	// add new velocity
	_vx += vx1;
	_vy += vy1;
	// get new direction
	_direction = atan2(_vy, _vx);
	// get new velocity
	double velocity = sqrt(_vx*_vx + _vy*_vy);
	// clamp to max vel
	if (velocity > 0) {
		double vClamp = CLAMP(velocity, 0.0, MAX_VELOCITY);
		_vx *= vClamp / velocity;
		_vy *= vClamp / velocity;
	}
}

void CRectEntity::cancel_vel() {
	_vx = _vy = 0.0;
	_update_bbox();
}

void CRectEntity::accelerate(double amt) {
	change_vel(amt, _direction*180.0/M_PI);
}

void CRectEntity::decelerate(double amt) {
	// get old vels
	double velocity = sqrt(_vx*_vx + _vy*_vy);
	// check if stopped
	if (amt < velocity)
		change_vel(-amt, _direction*180.0 / M_PI);
	else {
		_vx = 0.0;
		_vy = 0.0;
	}
}

double CRectEntity::get_vel() const {
	return sqrt(_vx*_vx + _vy*_vy);
}

double CRectEntity::get_direction() const {
	return _direction;
}

double CRectEntity::get_x() const {
	return _x;
}
double CRectEntity::get_y() const {
	return _y;
}

double CRectEntity::get_vx() const {
	return _vx;
}
double CRectEntity::get_vy() const {
	return _vy;
}

void CRectEntity::set_color(Uint8 r, Uint8 g, Uint8 b) {
	_drawColor.r = r;
	_drawColor.g = g;
	_drawColor.b = b;
}
void CRectEntity::set_color(Uint32 color) {
	set_color(GETR(color), GETG(color), GETB(color));
}

const SDL_Rect* CRectEntity::get_bounding_box() const {
	const SDL_Rect* pBB = &_boundingBox;
	return pBB;
}

void CRectEntity::_update_bbox() {
	_boundingBox.x = (int)round(_x);
	_boundingBox.y = (int)round(_y);
}
