#pragma once

#include "../World/Enemy.h"
#include "../Characters/Character.h"
#include "../Items/Inventory.h"
#include "../Core/Logger.h"
#include <functional>


class Battle
{
private:
	Character& player_;
	vector<Character*>& enemies_;
	Inventory& inventory_;
	Logger& logger_;

public:
	Battle(Character& player, vector<Character*>& enemies, Inventory& inventory, Logger& logger);
	void StartBattle();

private:
	void EnemyTurn();
	void ShowEnemies();
	void ShowStats();
	void ProcessPlayerAction(std::function<void(Character&)> action);
	bool IsBattleOver();
	Character* ChooseTarget();
};