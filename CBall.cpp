#include "CBall.h"
#include "Defines.h"

CBall::CBall() : CRectEntity(BALL_VEL_MAX) {
	reset();
	CRectEntity::update();
	set_color(BALL_COLOR);
	_boundingBox.w = BALL_SIZE;
	_boundingBox.h = BALL_SIZE;
}

void CBall::reset() {
	scoredLeft = scoredRight = false;
	_x = 0.5*(SCREEN_W -BALL_SIZE);
	_y = 0.5*(SCREEN_H - BALL_SIZE);
	cancel_vel();
}

void CBall::update() {
	// bounce off screen edges
	CRectEntity::update();
	if (_x + BALL_SIZE < 0.0) {
		scoredLeft = true;
	}
	else if (_x > SCREEN_W) {
		scoredRight = true;
	}

	if (_y < 0.0) {
		// reflect y
		bounce_y(0);
	}
	else if (_y > SCREEN_H - BALL_SIZE) {
		// reflect y
		bounce_y(SCREEN_H - BALL_SIZE);
	}

	_update_direction();
}

void CBall::bounce_x(double reflect) {
	double diff = _x - reflect;
	_x -= 2 * diff;
	_vx = -_vx;
	_update_direction();
}

void CBall::bounce_y(double reflect) {
	double diff = _y - reflect;
	_y -= 2 * diff;
	_vy = -_vy;
	_update_direction();
}

void CBall::change_vel_x(double dv) {
	_vx += dv;
	_update_direction();
}
void CBall::change_vel_y(double dv) {
	_vy += dv;
	_update_direction();
}

/*
IDEA FOR BALL DRAWING:
SINCE EVERYTHING IS DRAWN WITH RECTS:
CREATE A VENEER FOR THE RENDERFILLRECT FUNTIONS THAT STORES THE RECT INTO A LIST ON EACH MAIN DRAW PASS
ONCE YOU HAVE THE LIST (I.E. MUST DRAW BALL LAST), USE THAT LIST OF RECTS TO INTERSECT THE BALL AND INVERT COLOR IN THE INTERSECTED AREA.
*/
void CBall::draw(SDL_Renderer* r, const std::vector<SDL_Rect> &drawnBoxes) {
	// draw ball
	CRectEntity::draw(r);
	// draw inverted over intersects
	std::vector<SDL_Rect> intersects;
	for (auto box : drawnBoxes) {
		SDL_Rect intersection;
		if (SDL_IntersectRect(&_boundingBox, &box, &intersection))
			intersects.push_back(intersection);
	}
	if (!intersects.empty()) {
		// keep old color
		SDL_Color save;
		SDL_GetRenderDrawColor(r, &save.r, &save.g, &save.b, &save.a);
		// draw colored rectangle
		SDL_SetRenderDrawColor(r, 255 - _drawColor.r, 255 - _drawColor.g, 255 - _drawColor.b, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRects(r, &intersects[0], intersects.size());
		// reset color
		SDL_SetRenderDrawColor(r, save.r, save.g, save.b, save.a);
	}
}

void CBall::_update_direction() {
	_direction = atan2(_vy, _vx);
}
