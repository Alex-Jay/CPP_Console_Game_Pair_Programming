#pragma once
#include "Weapon.h"
#include "Player.h"
#include "Monster.h"
#include <string>
#include <iostream>

using namespace std;

class BattleObject
{
private:
	int m_health, m_attack, m_defence;
	bool m_defend;
	Weapon m_weapon;
	bool m_isDead;


public:
	BattleObject();
	BattleObject(int health, int attack, int defence, Weapon weapon);
	BattleObject(int health, int attack, int defence);

	Weapon getWeapon();
	int getHealth();
	int getAttack();
	int getDefence();
	bool isDefend();
	void decreaseHealth(int damage);
	void Attack(Player bo);
	void Attack(Monster bo);
	void Defend();
	void setWeapon(Weapon n);
	bool checkIsDead();
	bool getIsDead();
	void setIsDead();
	void setHealth(int health);
	string toString();
	~BattleObject();
};

