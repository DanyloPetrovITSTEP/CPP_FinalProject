// Character.h
// Base abstract character class.
// Responsible for common character data and behavior.
//
// Fields:
// - name
// - health
// - max health
// - damage
// - gold
// - inventory
//
// Common methods:
// - getName()
// - getHealth()
// - getDamage()
// - getGold()
// - isAlive()
// - takeDamage(value)
// - heal(value)
// - addGold(value)
// - spendGold(value)
//
// Virtual methods:
// - getClassName()
// - specialAction()
//
// Derived classes:
// - Warrior
// - Archer
// - Mage
// - Rogue