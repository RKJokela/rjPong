#ifndef CPLAYERPADDLE_H_INCLUDED
#define CPLAYERPADDLE_H_INCLUDED

#include "Interfaces.h"
#include "CRectEntity.h"

class CPlayerPaddle : public CRectEntity, public ITakesInput {
public:
	CPlayerPaddle(int side);
	void handle_input(const GameInputs& input);
	void update();
private:
	int _playerSide;
};

#endif // !CPLAYERPADDLE_H_INCLUDED
