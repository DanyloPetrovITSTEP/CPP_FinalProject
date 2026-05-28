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
	bool battle_result_printed_ = false;

public:
	Battle(Character& player, vector<Character*>& enemies, Inventory& inventory, Logger& logger);
	void StartBattle();

private:
	void EnemyTurn();
	void ShowEnemies();
	void ShowStats();
	bool ProcessPlayerAction(std::function<bool(Character&)> action);
	bool IsBattleOver();
	Character* ChooseTarget();
};