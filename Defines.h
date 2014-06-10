#ifndef		DEFINES_H
#define		DEFINES_H

//--WINDOW--
// Window dimensions in pixels
#define SCREEN_W	640
#define SCREEN_H	480

// Goes in window title bar
#define TITLE		"rjPong"

//--GRAPHICS--
// Pixel format used for everything
#define PIXELFORMAT	SDL_PIXELFORMAT_ARGB8888
#define	BPP			32
#define RMASK		0x00ff0000
#define GMASK		0x0000ff00
#define BMASK		0x000000ff
#define AMASK		0xff000000
#define RSHIFT		16
#define GSHIFT		8
#define BSHIFT		0
#define ASHIFT		24
#define COLORKEY	0x0000ffff	// Cyan

//--COLORS--
#define COLOR_BG	0xff000000	// black	0xff094270	// cool blue-teal
#define COLOR_FG	0xffffffff	// white

#define GETR(PIXEL)	(((PIXEL)&RMASK)>>RSHIFT)
#define GETG(PIXEL)	(((PIXEL)&GMASK)>>GSHIFT)
#define GETB(PIXEL)	(((PIXEL)&BMASK)>>BSHIFT)
#define GETA(PIXEL)	(((PIXEL)&AMASK)>>ASHIFT)

#define MAKE_SDL_COLOR(PIXEL) {\
	GETR(PIXEL), \
	GETG(PIXEL), \
	GETB(PIXEL), \
	GETA(PIXEL)}

//--GAME--
// Game Framerate cap in frames/sec
#define FPS			60
// Time per frame in ms
#define MS_PER_FRAME	(1000.0/FPS)
// Ball
#define BALL_SIZE	20					// square
#define BALL_VEL	5.0					// pixels per frame
#define BALL_COLOR	COLOR_FG
// Paddle
#define PADDLE_W	20
#define PADDLE_H	100					// can be changed during game
#define PADDLE_SCREEN_OFFSET	50		// distance from edge of screen
#define PADDLE_VEL	5.0					// pixels per frame
#define	PADDLE_COLOR COLOR_FG
// Directions in degrees
#define UP			270.0
#define DOWN		90.0

#endif	//	DEFINES_H
