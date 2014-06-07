#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

union GameInputs;

class IMover
{
public:
	virtual void change_vel(double amt, double degrees) = 0;
};

class ITakesInput
{
public:
	virtual void handle_input(GameInputs input) = 0;
};


#endif // !INTERFACES_H_INCLUDED
