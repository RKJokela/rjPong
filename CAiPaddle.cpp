#include "CAiPaddle.h"
#include "Defines.h"
#include "Utilities.h"

#define P_GAIN	0.1
#define I_GAIN	0.0
#define D_GAIN	0.0

#define REST_ZONE (0.1*PADDLE_H)

CAiPaddle::CAiPaddle(int side) : CRectEntity(PADDLE_VEL), _myBall(nullptr), _mySide(side) {
	// set horizontal position left or right
	if (_mySide == LEFT)
		_x = PADDLE_SCREEN_OFFSET;
	else
		_x = SCREEN_W - PADDLE_SCREEN_OFFSET - PADDLE_W;
	// center vertically
	_y = 0.5*(SCREEN_H - PADDLE_H);
	// set paddle size
	_boundingBox.w = PADDLE_W;
	_boundingBox.h = PADDLE_H;
	// set color
	set_color(PADDLE_COLOR);
	// position bounding box
	cancel_vel();
	update();
}

void CAiPaddle::set_ball(const CBall* ball) {
	_myBall = ball;
}

void CAiPaddle::update() {
	if (_myBall) {
		double ballVertDist = _myBall->get_y() - _y - 0.5*_boundingBox.h;
		if (abs(ballVertDist) < REST_ZONE)
			_vy = 0;
		else {// chase the ball!
			_vy = CLAMP(P_GAIN*ballVertDist, -MAX_VELOCITY, MAX_VELOCITY);
			if (_y + _vy < 0.0) {
				_y = 0;
				_vy = 0;
			}
			else if (_y + _vy > SCREEN_H - _boundingBox.h) {
				_y = SCREEN_H - _boundingBox.h;
				_vy = 0;
			}
		}
		CRectEntity::update();
	}
}
