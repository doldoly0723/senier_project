#ifndef ENEMY_OWEND_STATES_H
#define ENEMY_OWEND_STATES_H

////////////////////////////
// EnemyOwnedStates.h
////////////////////////////
#include "State.h"
#include "EnemyOwnedStates.h"
#include "Enemy.h"

class Enemy;

class Idle : public State<Enemy>
{

};

class Wander : public State<Enemy>
{
private:
	Wander() {}

	Wander(const Wander&);
	Wander* operator=(const Wander&);

public:
	static Wander* Instance();

public:

	virtual void Enter(Enemy* enemy);

	virtual void Execute(Enemy* enemy);

	virtual void Exit(Enemy* enemy);
};


class FollowPlayer : public State<Enemy>
{

};


class AttackPlayer : public State<Enemy>
{

};

#endif // !1
