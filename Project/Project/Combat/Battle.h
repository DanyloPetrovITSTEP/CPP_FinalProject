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
	void ShowStats();
	void RunAway();
};