#ifndef CBALL_H_INCLUDED
#define CBALL_H_INCLUDED

#include <vector>
#include "CRectEntity.h"

class CBall : public CRectEntity {
public:
	CBall();

	void reset();
	void update();

	void bounce_x(double reflectLine);
	void bounce_y(double reflectLine);

	void change_vel_x(double dv);
	void change_vel_y(double dv);

	// for cool color inversion effect
	void draw(SDL_Renderer* r, const std::vector<SDL_Rect> &drawnBoxes);

	bool scoredLeft;
	bool scoredRight;

private:
	void _update_direction();
	void _do_collision(const SDL_Rect &box);
};

#endif // !CBALL_H_INCLUDED
