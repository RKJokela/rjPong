#include "CBall.h"
#include "Defines.h"

CBall::CBall() : CRectEntity(BALL_VEL) {
	reset();
	update();
	set_color(GETR(BALL_COLOR), GETG(BALL_COLOR), GETB(BALL_COLOR));
	_boundingBox.w = BALL_SIZE;
	_boundingBox.h = BALL_SIZE;
}

void CBall::reset() {
	scoredLeft = scoredRight = false;
	_x = 0.5*(SCREEN_W -BALL_SIZE);
	_y = 0.5*(SCREEN_H - BALL_SIZE);
	cancel_vel();
}

/*
IDEA FOR BALL DRAWING:
SINCE EVERYTHING IS DRAWN WITH RECTS:
CREATE A VENEER FOR THE RENDERFILLRECT FUNTIONS THAT STORES THE RECT INTO A LIST ON EACH MAIN DRAW PASS
ONCE YOU HAVE THE LIST (I.E. MUST DRAW BALL LAST), USE THAT LIST OF RECTS TO INTERSECT THE BALL AND INVERT COLOR IN THE INTERSECTED AREA.
*/

void CBall::update() {
	// bounce off screen edges
	CRectEntity::update();
	if (_x + BALL_SIZE < 0.0) {
		/*
		// reflect x position
		_x = -_x;
		// reflect velocity
		// coming toward left wall: angle is in (90, 270)
		// need to subtract from 180
		_direction = M_PI - _direction;
		if (_direction < 0.0)
			_direction += 2 * M_PI;
		*/
		scoredLeft = true;
	}
	else if (_x > SCREEN_W) {
		/*
		_x = 2 * SCREEN_W - (_x + BALL_SIZE) - BALL_SIZE;
		// coming toward right wall: angle is in (-90, 90)
		// need to subtract from 180
		_direction = M_PI - _direction;
		if (_direction < 0.0)
			_direction += 2 * M_PI;
		*/
		scoredRight = true;
	}

	if (_y < 0.0) {
		// reflect y position
		_y = -_y;
		// reflect velocity
		// coming toward top wall: angle is in (180, 360)
		// need to subtract from 360
		_direction = 2 * M_PI - _direction;
	}
	else if (_y+BALL_SIZE > SCREEN_H) {
		_y = 2 * SCREEN_H - (_y+BALL_SIZE)-BALL_SIZE;
		// coming toward bottom wall: angle is in (0, 180)
		// need to subtract from 360
		_direction = 2*M_PI - _direction;
	}
}
