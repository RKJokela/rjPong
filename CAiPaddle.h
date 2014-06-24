#ifndef CAI_PADDLE_H_INCLUDED
#define CAI_PADDLE_H_INCLUDED

#include "CRectEntity.h"
#include "CBall.h"

class CAiPaddle : public CRectEntity
{
public:
	CAiPaddle(int side);
	void set_ball(const CBall* ball);
	void update();

private:
	const CBall* _myBall;
	int _mySide;
};

#endif // !CAI_PADDLE_H_INCLUDED
