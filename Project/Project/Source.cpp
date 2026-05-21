// ======================================================
// INCLUDES
// Here we will include libraries
// ======================================================


// ======================================================
// GLOBAL CONSTANTS / SETTINGS
// Here we can store file names and simple game settings.
// Example:
// save file name
// shop item prices
// dungeon level names
// ======================================================


// ======================================================
// EXCEPTIONS
// Here we will create simple typed exceptions.
// Example:
// GameException
// SaveLoadException
// InventoryException
// ======================================================


// ======================================================
// LOGGER / GAME MESSAGES
// Here we will store and print game messages.
// Example:
// "Hero entered the dungeon"
// "Hero bought a potion"
// "Game saved"
// ======================================================


// ======================================================
// ITEM SYSTEM
// Base Item class.
// Derived classes:
// Potion
// Weapon
// Armor
//
// Items will be stored in the player's inventory.
// ======================================================


// ======================================================
// INVENTORY
// Inventory class.
// Stores player's items.
// Main methods:
// add item
// remove item
// show inventory
// use item
// ======================================================


// ======================================================
// CHARACTER SYSTEM
// Base Character class.
// Fields:
// name
// health
// max health
// damage
// gold
// inventory
//
// Derived classes:
// Warrior
// Archer
// Mage
// Rogue
//
// Each class has prepared starting stats.
// Example:
// Warrior: 100 HP, 10 damage
// Mage: 70 HP, 18 damage
// ======================================================


// ======================================================
// ENEMY SYSTEM
// Base Enemy class.
// Derived enemy types:
// Goblin
// Skeleton
// Boss
//
// Enemies will be used in dungeons.
// ======================================================


// ======================================================
// DUNGEON SYSTEM
// Dungeon class or functions.
// Shows dungeon level menu.
// Example:
// 1. Easy dungeon
// 2. Medium dungeon
// 3. Hard dungeon
// 4. Back
//
// Starts battle with enemies.
// ======================================================


// ======================================================
// BATTLE SYSTEM
// Battle class or battle functions.
// Handles fighting between player and enemies.
// Shows battle menu.
// Example:
// 1. Attack
// 2. Use item
// 3. Run away
// ======================================================


// ======================================================
// SHOP SYSTEM
// Shop class or shop functions.
// Shows shop menu.
// Example:
// 1. Buy potion
// 2. Buy weapon
// 3. Buy armor
// 4. Back
// ======================================================


// ======================================================
// SAVE / LOAD SYSTEM
// Save player class, stats, gold and inventory to file.
// Load saved player data from file.
// Used by:
// Continue
// Save game
// ======================================================


// ======================================================
// MAIN MENU
// First menu after starting the program.
// Options:
// 1. New game
// 2. Continue
// 3. Exit
// ======================================================


// ======================================================
// CHARACTER CLASS SELECTION MENU
// Opens after New game.
// Options:
// 1. Warrior
// 2. Archer
// 3. Mage
// 4. Rogue
// 5. Exit game
// ======================================================


// ======================================================
// GAME MENU
// Main game menu after creating or loading character.
// Options:
// 1. Go into the dungeon
// 2. Go to the shop
// 3. Go rest in home
// 4. Save game
// 5. Exit game
// ======================================================


// ======================================================
// GAME CLASS
// Main class that connects all systems together.
// It should control:
// main menu
// class selection
// game menu
// dungeon
// shop
// save/load
//
// main() should not contain game logic.
// ======================================================


// ======================================================
// MAIN FUNCTION
// Creates Game object and calls run().
// Also has try/catch for errors.
// ======================================================