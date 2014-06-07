#ifndef		CAPP_H
#define		CAPP_H

#include <SDL.h>
#include "Defines.h"
#include "CEvent.h"
// OTHER INCLUDES HERE

// -------------------

union GameInputs {
	struct menu {
		bool confirm;
		bool cancel;
	};
	struct game {
		bool up;
		bool down;
	};
};

class CApp : public CEvent {
public:
	CApp();

	// called by main()
	int  Execute();

public:
	bool init();
	void handle_event(SDL_Event* Event);
	void update();
	void draw();
	void cleanup();

	void OnExit();

	// PROGRAM-SPECIFIC FUNCTIONS HERE

private:
	bool _running;

	SDL_Window*   _window;
	SDL_Renderer* _renderer;

	// PROGRAM-SPECIFIC MEMBERS HERE
	
};

#endif	//	CAPP_H
