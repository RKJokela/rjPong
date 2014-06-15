#ifndef CBALL_H_INCLUDED
#define CBALL_H_INCLUDED

#include "CRectEntity.h"

class CBall : public CRectEntity {
public:
	CBall();

	void reset();
	void update();

	bool scoredLeft;
	bool scoredRight;
};

#endif // !CBALL_H_INCLUDED
