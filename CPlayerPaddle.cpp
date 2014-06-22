#include "CPlayerPaddle.h"
#include "CGamestate.h" // for GameInputs
#include "Defines.h"

CPlayerPaddle::CPlayerPaddle(int side) :
CRectEntity(PADDLE_VEL),
_playerSide(side) {
	// set horizontal position left or right
	if (_playerSide == LEFT)
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

void CPlayerPaddle::handle_input(const GameInputs& input) {
	cancel_vel();
	double vel = 0.0;
	bool up, down;
	if (_playerSide == LEFT) {
		up   = input.game.l_up;
		down = input.game.l_down;
	}
	else { // RIGHT
		up   = input.game.r_up;
		down = input.game.r_down;
	}
	if (up)
		vel += MAX_VELOCITY;
	if (down)
		vel -= MAX_VELOCITY;
	double dir = (vel > 0.0) ? UP : DOWN;
	vel = SDL_fabs(vel);
	change_vel(vel, dir);
}

void CPlayerPaddle::update() {
	CRectEntity::update();
	// keep onscreen
	if (_boundingBox.y < 0) {
		_y = 0.0;
		_boundingBox.y = 0;
	}
	else if (_boundingBox.y + _boundingBox.h > SCREEN_H) {
		_y = SCREEN_H - _boundingBox.h;
		_boundingBox.y = (int)_y;
	}
}
