#ifndef STATEMACHINE_H
#define STATEMACHINE_H

////////////////////////////////////////
// StateMachine.h
///////////////////////////////////////
#include "State.h"

template <class entity_type>
class StateMachine
{
private:

	entity_type* m_pOwner;

	State<entity_type>* m_pCurrentState;

	State<entity_type>* m_pPreviousState;

	State<entity_type>* m_pGlobalState;

public:
	StateMachine(entity_type* owner) : m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}

	virtual ~StateMachine() {};

	void SetCurrentState(State<entity_type>* s) { m_pCurrentState = s; }
	void SetGlobalState(State<entity_type>* s) { m_pGlobalState = s; }
	void SetPreviousState(State<entity_type>* s) { m_pCurrentState = s; }


	void Update() const
	{
		if (m_pGlobalState) m_pGlobalState->Excute(m_pOwner);

		if (m_pCurrentState) m_pCurrentState->Excute(m_pOwner);
	}

	void ChangeState(State<entity_type>* pNewState)
	{
		m_pPreviousState = m_pCurrentState;

		m_pCurrentState->Exit(m_pOwner);

		m_pCurrentState = pNewState;

		m_pCurrentState->Enter(m_pOwner);
	}

	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	bool isInState(const State<entity_type>* st) const
	{
		return typeid(*m_pCurrentState) == typeid(st);
	}

	State<entity_type>* CurrentState() const { return m_pCurrentState };
	State<entity_type>* GlobalState() const { return m_pGlobalState };
	State<entity_type>* PreviousState() const { return m_pPreviousState };
};


#endif