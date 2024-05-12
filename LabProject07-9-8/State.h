#ifndef STATE_H
#define STATE_H

////////////////////////////////////////
// State.h
///////////////////////////////////////

template <class entity_type>
class State
{
public:
	virtual ~State() {};

	virtual void Enter(entity_type*) = 0;

	virtual void Excute(entity_type*) = 0;

	virtual void Exit(entity_type*) = 0;
};

#endif