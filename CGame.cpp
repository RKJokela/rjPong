#include "CGame.h"
#include "Defines.h"

const SDL_Color bgColor = MAKE_SDL_COLOR(COLOR_BG);
const SDL_Color fgColor = MAKE_SDL_COLOR(COLOR_FG);

CGame::CGame() :
_r(NULL) {
	_listInputHandlers = NULL;
	CPlayerPaddle* left  = new CPlayerPaddle(CPlayerPaddle::LEFT);
	CPlayerPaddle* right = new CPlayerPaddle(CPlayerPaddle::RIGHT);
	_paddleLeft  = left;
	_paddleRight = right;
	_listInputHandlers = new inputNode;
	_listInputHandlers->entity = left;
	_listInputHandlers->next = new inputNode;
	_listInputHandlers->next->entity = right;
	_listInputHandlers->next->next = NULL;
	_inputs.game.l_down = false;
	_inputs.game.l_up = false;
	_inputs.game.r_down = false;
	_inputs.game.r_up = false;
}

CGame::~CGame()
{
	// remove the paddles
	delete _paddleLeft;
	delete _paddleRight;
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
	_paddleLeft->update();
	_paddleRight->update();
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
void draw_digit(SDL_Renderer* r, Uint8 digit, int x, int y, int pxSize = SCORE_PX_SIZE) {
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
	SDL_RenderFillRects(r, px, count);
}

void CGame::draw() {
	// fill background
	SDL_SetRenderDrawColor(_r, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_r);
	// draw centerline
	SDL_SetRenderDrawColor(_r, fgColor.r, fgColor.g, fgColor.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(_r, &centerline);
	// draw scores
	draw_digit(_r, 3, (SCREEN_W - SCORE_W) / 2 - 100, SCORE_PX_SIZE);
	draw_digit(_r, 2, (SCREEN_W - SCORE_W) / 2 + 100, SCORE_PX_SIZE);
	// draw paddles
	_paddleLeft->draw(_r);
	_paddleRight->draw(_r);

	// show onscreen
	SDL_RenderPresent(_r);
}

void CGame::set_renderer(SDL_Renderer* r) {
	_r = r;
}

void CGame::OnKeyDown(SDL_Keycode key, Uint16 mod, SDL_Scancode scancode, bool repeat) {
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
