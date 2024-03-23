#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "all_states.h"

class StateMachine
{
	State *states[STATE::_TOTAL];
	STATE current;

public:
	StateMachine();
	void changeState(STATE newState);

	void run();
};

StateMachine::StateMachine()
{
	current = STATE::_TOTAL;

	states[STATE::BOOT] = new BootState;
	states[STATE::READY] = new ReadyState;
	states[STATE::UP] = new UpState;
	states[STATE::DOWN] = new DownState;
	states[STATE::STOP] = new StopState;
	states[STATE::ERROR] = new ErrorState;

	changeState(STATE::BOOT);
}

void StateMachine::changeState(STATE newState)
{
	if (current == newState)
		return; // Don't do anything if we're already in this state.

	// Do we want to allow changing the state if we're in an error state?
	// Maybe not? If that's the case, put that logic here.

	current = newState;

	if (!states[current]->begin())
	{
		current = STATE::ERROR;
		states[current]->begin();
	}
}

void StateMachine::run()
{
	if (states[current]->isDone())
	{
		changeState(states[current]->nextState());
	}

	if (!states[current]->run())
	{
		changeState(STATE::ERROR);
	}
}

#endif
