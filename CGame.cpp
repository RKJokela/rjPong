#include "CGame.h"
#include "Utilities.h"

#define L side::LEFT
#define R side::RIGHT

const SDL_Color bgColor = MAKE_SDL_COLOR(COLOR_BG);
const SDL_Color fgColor = MAKE_SDL_COLOR(COLOR_FG);

CGame::CGame() :
_r(NULL), _ball(),
_drawRects(0),
_waiting(false),
_waitTicks(0) {
	_scores[L] = 0;
	_scores[R] = 0;
	_listInputHandlers = NULL;
	CAiPaddle* left = new CAiPaddle(L);
	CPlayerPaddle* right = new CPlayerPaddle(R);
	_paddles[L]  = left;
	_paddles[R] = right;
	_listInputHandlers = new inputNode;
	_listInputHandlers->entity = right;
	_listInputHandlers->next = NULL; /*new inputNode;
	_listInputHandlers->next->entity = right;
	_listInputHandlers->next->next = NULL; */
	_inputs.game.l_down = false;
	_inputs.game.l_up = false;
	_inputs.game.r_down = false;
	_inputs.game.r_up = false;
	left->set_ball(&_ball);
	_waitTicks = 1500 / MS_PER_FRAME;
	_waiting = true;
}

CGame::~CGame()
{
	// remove the paddles
	delete _paddles[L];
	delete _paddles[R];
	while (_listInputHandlers != NULL) {
		inputNodePtr tmp = _listInputHandlers->next;
		delete _listInputHandlers;
		_listInputHandlers = tmp;
	}
}

void CGame::handle_event(const SDL_Event* e) {
	CEvent::handle_event(e);
}

void CGame::update() {
	inputNodePtr ih = _listInputHandlers;
	while (ih != NULL) {
		ih->entity->handle_input(_inputs);
		ih = ih->next;
	}

	start_ball();
	
	SDL_Rect futurePos = { 0 };
	_ball.future(futurePos);

	_handle_collisions(&futurePos);

	_ball.update();
	_paddles[L]->update();
	_paddles[R]->update();

	// OLD COLLISION CODE
	//double ballX = _ball.get_x();
	//double ballY = _ball.get_y();
	//if (_ball.get_vx() < 0. &&
	//	ballX <= _paddles[L]->get_x() + PADDLE_W)
	//{	// hit left paddle
	//	double paddleTop = _paddles[L]->get_y();
	//	double paddleBot = paddleTop + _paddles[L]->get_bounding_box()->h;
	//	double paddleLft = _paddles[L]->get_x();
	//	double paddleRgt = paddleLft + _paddles[L]->get_bounding_box()->w;
	//	double crW = paddleRgt - ballX;
	//	double crH = (ballY < paddleTop ? (ballY + BALL_SIZE - paddleTop) : \
	//		(ballY + BALL_SIZE > paddleBot) ? (paddleBot - ballY) : \
	//		BALL_SIZE);
	//	if (crH > 0.0) {
	//		if (crH > crW) // hit side
	//		{
	//			double ballCtrY = ballY + 0.5*BALL_SIZE;
	//			double paddCtrY = 0.5*(paddleTop + paddleBot);
	//			double ctrOffsetNorm = 2*(ballCtrY - paddCtrY)/(paddleBot - paddleTop + BALL_SIZE);
	//			SDL_assert(abs(ctrOffsetNorm) <= 1.0);
	//			_ball.change_vel_y(ctrOffsetNorm*PADDLE_HIT_DV_MAX);
	//			_ball.bounce_x(paddleRgt);
	//			_ball.accelerate(BALL_ACCEL_ON_HIT);
	//		}
	//		else if (ballX + BALL_SIZE >= paddleLft) { // hit top or bottom
	//			if (ballY < paddleTop) {// hit top
	//				if (_ball.get_vy() > 0.0)
	//					_ball.bounce_y(paddleTop - BALL_SIZE);
	//				if (_paddles[L]->get_vy() < 0.0)
	//					_ball.change_vel_y(_paddles[L]->get_vy());
	//			}
	//			else if (ballY + BALL_SIZE > paddleBot) { // hit bottom
	//				if (_ball.get_vy() < 0.0)
	//					_ball.bounce_y(paddleBot);
	//				if (_paddles[L]->get_vy() > 0.0)
	//					_ball.change_vel_y(_paddles[L]->get_vy());
	//			}
	//		}
	//	}
	//}
	//else if (_ball.get_vx() > 0. &&
	//	ballX + BALL_SIZE >= _paddles[R]->get_x()) 
	//{	// hit right paddle
	//	double paddleTop = _paddles[R]->get_y();
	//	double paddleBot = paddleTop + _paddles[R]->get_bounding_box()->h;
	//	double paddleLft = _paddles[R]->get_x();
	//	double paddleRgt = paddleLft + _paddles[R]->get_bounding_box()->w;
	//	double crW = ballX + BALL_SIZE - paddleLft;
	//	double crH = (ballY < paddleTop ? (ballY + BALL_SIZE - paddleTop) : \
	//		(ballY + BALL_SIZE > paddleBot) ? (paddleBot - ballY) : \
	//		BALL_SIZE);
	//	if (crH > 0.0) {
	//		if (crH > crW) // hit side
	//		{
	//			double ballCtrY = ballY + 0.5*BALL_SIZE;
	//			double paddCtrY = 0.5*(paddleTop + paddleBot);
	//			double ctrOffsetNorm = 2 * (ballCtrY - paddCtrY) / (paddleBot - paddleTop + BALL_SIZE);
	//			SDL_assert(abs(ctrOffsetNorm) <= 1.0);
	//			_ball.change_vel_y(ctrOffsetNorm*PADDLE_HIT_DV_MAX);
	//			_ball.bounce_x(paddleLft - BALL_SIZE);
	//			_ball.accelerate(BALL_ACCEL_ON_HIT);
	//		}
	//		else if (ballX <= paddleRgt) { // hit top or bottom
	//			if (ballY < paddleTop) {// hit top
	//				if (_ball.get_vy() > 0.0)
	//					_ball.bounce_y(paddleTop - BALL_SIZE);
	//				if (_paddles[R]->get_vy() < 0.0)
	//					_ball.change_vel_y(_paddles[R]->get_vy());
	//			}
	//			else if (ballY + BALL_SIZE > paddleBot) { // hit bottom
	//				if (_ball.get_vy() < 0.0)
	//					_ball.bounce_y(paddleBot);
	//				if (_paddles[R]->get_vy() > 0.0)
	//					_ball.change_vel_y(_paddles[R]->get_vy());
	//			}
	//		}
	//	}
	//}

	// scoring
	bool gameOver = false;
	if (_ball.scoredLeft) {
		_ball.reset();
		_waitTicks = 1000 / MS_PER_FRAME;
		_waiting = true;
		if (++_scores[R] >= SCORE_MAX)
			gameOver = true;
	}
	else if (_ball.scoredRight) {
		_ball.reset();
		_waitTicks = 1000 / MS_PER_FRAME;
		_waiting = true;
		if (++_scores[L] >= SCORE_MAX)
			gameOver = true;
	}
	if (gameOver) {
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PeepEvents(&e, 1, SDL_ADDEVENT, 0, 0);
	}
}

const SDL_Rect centerline = {
	SCREEN_W / 2 - 1,
	0,
	2,
	SCREEN_H
};

const char* digits[10][7] = {
	{
		"####",
		"#  #",
		"#  #",
		"#  #",
		"#  #",
		"#  #",
		"####"
	},
	{
		"   #",
		"   #",
		"   #",
		"   #",
		"   #",
		"   #",
		"   #",
	},
	{
		"####",
		"   #",
		"   #",
		"####",
		"#   ",
		"#   ",
		"####"
	},
	{
		"####",
		"   #",
		"   #",
		"####",
		"   #",
		"   #",
		"####"
	},
	{
		"#  #",
		"#  #",
		"#  #",
		"####",
		"   #",
		"   #",
		"   #"
	},
	{
		"####",
		"#   ",
		"#   ",
		"####",
		"   #",
		"   #",
		"####"
	},
	{
		"####",
		"#   ",
		"#   ",
		"####",
		"#  #",
		"#  #",
		"####"
	},
	{
		"####",
		"   #",
		"   #",
		"   #",
		"   #",
		"   #",
		"   #",
	},
	{
		"####",
		"#  #",
		"#  #",
		"####",
		"#  #",
		"#  #",
		"####"
	},
	{
		"####",
		"#  #",
		"#  #",
		"####",
		"   #",
		"   #",
		"   #"
	}
};

// uses currently set render draw color
void CGame::_draw_digit(Uint8 digit, int x, int y, int pxSize) {
	if (digit > 9)
		return;
	SDL_Rect px[28] = { 0 };
	int count = 0;
	const char** digPts = digits[digit];
	int posX = x, posY = y;
	for (int i = 0; i < 7; i++) {
		const char* digRow = *digPts;
		// draw the row
		for (int j = 0; j < 4; j++) {
			char ch = *digRow;
			if (ch == '#') {
				// set the rect
				px[count].x = posX;
				px[count].y = posY;
				px[count].h = pxSize;
				px[count].w = pxSize;
				// increment count
				count++;
			}
			posX += pxSize;
			digRow++;
		}
		// increment row
		posY += pxSize;
		digPts++;
		// reset x
		posX = x;
	}

	// now, draw it
	_fill_rects(px, count);
}

void CGame::draw() {
	// empty the drawn boxes list
	_drawRects.clear();
	// fill background
	SDL_SetRenderDrawColor(_r, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_r);
	// draw centerline
	SDL_SetRenderDrawColor(_r, fgColor.r, fgColor.g, fgColor.b, SDL_ALPHA_OPAQUE);
	_fill_rect(&centerline);
	// draw scores
	_draw_digit(_scores[L], (SCREEN_W - SCORE_W) / 2 - 3*SCORE_OFFSET, SCORE_OFFSET);
	_draw_digit(_scores[R], (SCREEN_W - SCORE_W) / 2 + 3*SCORE_OFFSET, SCORE_OFFSET);
	// draw paddles
	_paddles[L]->draw(_r);
	_paddles[R]->draw(_r);
	// draw ball
	_ball.draw(_r, _drawRects);

	// show onscreen
	SDL_RenderPresent(_r);
}

void CGame::set_renderer(SDL_Renderer* r) {
	_r = r;
}

void CGame::start_ball() {
	static bool started = false;
	if (_waitTicks > 0)
		started = false;
	if (!_waiting && !started) {
		auto angle = SDL_GetTicks() % 61 - 30;
		auto flip  = SDL_GetTicks() % 2;
		if (flip)
			angle += 180;
		if (angle < 0)
			angle += 360;
		_ball.change_vel(BALL_VEL_INIT, angle);
		started = true;
	}
	_waitTicks = MAX(0, _waitTicks - 1);
	if (!_waitTicks)
		_waiting = false;
}

void CGame::OnKeyDown(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat) {
	int angle = 0;
	switch (key) {
	case SDLK_UP:
		_inputs.game.r_up = true;
		break;
	case SDLK_DOWN:
		_inputs.game.r_down = true;
		break;
	case SDLK_LSHIFT:
		_inputs.game.l_up = true;
		break;
	case SDLK_LCTRL:
		_inputs.game.l_down = true;
		break;
	case SDLK_q:
	case SDLK_ESCAPE:
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		SDL_PeepEvents(&quitEvent, 1, SDL_ADDEVENT, 0, 0);
		break;
	//	QUICK AND DIRTY TESTING HERE
	case SDLK_r:
		_ball.reset();
		_scores[L] = _scores[R] = 0;
		break;
	case SDLK_SPACE:
		do {
			angle = SDL_GetTicks() % 360;
		} while ((angle >= 60 && angle <= 120) || (angle >= 240 && angle <= 300));
		_ball.change_vel(BALL_VEL_INIT, angle);
		break;
	default:
		break;
	}
}

void CGame::OnKeyUp(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat) {
	switch (key) {
	case SDLK_UP:
		_inputs.game.r_up = false;
		break;
	case SDLK_DOWN:
		_inputs.game.r_down = false;
		break;
	case SDLK_LSHIFT:
		_inputs.game.l_up = false;
		break;
	case SDLK_LCTRL:
		_inputs.game.l_down = false;
		break;
	default:
		break;
	}
}

void CGame::_fill_rect(const SDL_Rect* rect) {
	_drawRects.push_back(*rect);
	SDL_RenderFillRect(_r, rect);
}
void CGame::_fill_rects(const SDL_Rect* first, int count) {
	for (int i = 0; i < count; i++)
		_drawRects.push_back(first[i]);
	SDL_RenderFillRects(_r, first, count);
}

// collisions
// NEW METHOD:
//	extend a line from each vertex of bounding box from old position to new
//	use ball's x velocity to determine which paddle to check for collision (only check if moving toward paddle - should avoid stutters)
//	for front 2 lines, intersect with paddle bounding box
//	cases:
//		all 4 lines intersect: just reflect x direction
//		
void CGame::_handle_collisions(const SDL_Rect* newBallPos) {
	enum {
		frontTop = 0,
		frontBot,
		backTop,
		backBot,
		CORNERS
	};
	static int framesSinceLastCollision = 0;
	bool left = (_ball.get_vx() < 0);
	const CRectEntity* paddle = left ? _paddles[L] : _paddles[R];
	const SDL_Rect* paddleBox = paddle->get_bounding_box();
	const SDL_Rect* oldBallPos = _ball.get_bounding_box();
	bool up    = (_ball.get_vy() < 0);
	bool upRel = (_ball.get_vy() - paddle->get_vy() < 0);
	int fr0 = left ? oldBallPos->x : oldBallPos->x + oldBallPos->w;
	int fr1 = left ? newBallPos->x : newBallPos->x + newBallPos->w;
	int ba0 = left ? oldBallPos->x + oldBallPos->w : oldBallPos->x;
	int ba1 = left ? newBallPos->x + newBallPos->w : newBallPos->x;
	int tp0 = oldBallPos->y;
	int tp1 = newBallPos->y;
	int bt0 = oldBallPos->y + oldBallPos->h;
	int bt1 = newBallPos->y + newBallPos->h;

	bool hitPaddle = false;
	bool reflectX = false, reflectY = false;
	int paddleEdge = left ? paddleBox->x + paddleBox->w - 1: paddleBox->x;
	int reflectLine = left ? paddleEdge : paddleEdge - BALL_SIZE;

	SDL_Point pos0[CORNERS];
	SDL_Point pos1[CORNERS];
	SDL_bool hit[CORNERS] = { SDL_FALSE };

	pos0[frontTop] = { fr0, tp0 };
	pos0[frontBot] = { fr0, bt0 };
	pos0[backTop]  = { ba0, tp0 };
	pos0[backBot]  = { ba0, bt0 };
	pos1[frontTop] = { fr1, tp1 };
	pos1[frontBot] = { fr1, bt1 };
	pos1[backTop]  = { ba1, tp1 };
	pos1[backBot]  = { ba1, bt1 };

	// check for crosses
	for (int i = 0; i < CORNERS; ++i) {
		hit[i] = SDL_IntersectRectAndLine(paddleBox, &pos0[i].x, &pos0[i].y, &pos1[i].x, &pos1[i].y);
		hitPaddle = hitPaddle || hit[i];
	}

	if (!hitPaddle || framesSinceLastCollision < 10) {
		++framesSinceLastCollision;
		return; // don't waste your time
	}

	framesSinceLastCollision = 0;

	// case 1: both front lines cross
	if (hit[frontTop] && hit[frontBot])
		reflectX = true;
	// case 2: ball hit upper part of paddle
	else if (hit[frontBot]) {
		if (upRel) // traveling up (relative to paddle!)
			reflectX = true;
		else { // traveling down (relative to paddle)
			if (pos0[frontBot].x == paddleEdge) // hit side
				reflectX = true;
			else { // hit top
				reflectY = true;
				reflectLine = paddleBox->y - BALL_SIZE;
			}
		}
	}
	// case 3: ball hit lower part of paddle
	else if (hit[frontTop]) {
		if (!upRel) // traveling down (relative to paddle)
			reflectX = true;
		else { // traveling up (relative to paddle)
			if (pos0[frontTop].x == paddleEdge) // hit side
				reflectX = true;
			else { // hit bottom
				reflectY = true;
				reflectLine = paddleBox->y + paddleBox->h;
			}
		}
	}
	// front lines don't cross, but we have collision, so must be one of back lines
	// case 4: back of ball grazed top of paddle, traveling down
	else if (hit[backBot]) {
		reflectY = true;
		reflectLine = paddleBox->y - BALL_SIZE;
	}
	// case 5: back of ball grazed bottom of paddle, traveling up
	else if (hit[backTop]) {
		reflectY = true;
		reflectLine = paddleBox->y + paddleBox->h;
	}

	// now, do the proper bounce
	if (reflectX) {
		_ball.bounce_x(reflectLine);
		// get ball offset from paddle center
		double numerator = _ball.get_y() + 0.5*BALL_SIZE - ((double)paddleBox->y + 0.5*paddleBox->h);
		int denominator = paddleBox->h + BALL_SIZE;
		double ratio = 2.0 * numerator / denominator;
		_ball.change_vel_y(ratio*PADDLE_HIT_DV_MAX);
		_ball.change_vel_y(PADDLE_HIT_DV_RATIO*paddle->get_vy());
		_ball.accelerate(BALL_ACCEL_ON_HIT);
	}
	else if (reflectY) {
		_ball.bounce_y(reflectLine);
		_ball.change_vel_y(paddle->get_vy());
	}
	else // should never get here!
		SDL_assert(SDL_FALSE && "ERROR IN COLLISION CODE!");
}

#undef L
#undef R
