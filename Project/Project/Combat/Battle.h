// Battle.h
// Battle system.
// Responsible for turn-based combat.
//
// Battle menu example:
// 1. Attack
// 2. Use item
// 3. Show stats
// 4. Surrender
//
// Uses:
// - Character
// - Enemy
// - Inventory
// - Logger

#pragma once

#include "../World/Enemy.h"
#include "../Characters/Character.h"
#include "../Items/Inventory.h"
#include "../Core/Logger.h"


class Battle
{
private:
	Character& player_;
	Enemy& enemy_;
	Inventory& inventory_;
	Logger& logger_;

public:
	Battle(Character& player, Enemy& enemy, Inventory& inventory, Logger& logger);
	void StartBattle();

private:
	void PlayerAttack();
	void EnemyAttack();
	void UseItem();
	void ShowStats();
	void RunAway();
};