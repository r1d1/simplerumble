#include "Attack.h"

Attack::Attack() : m_Name("None"), m_Damage(0), m_Resistance(-1)
{}

Attack::Attack(std::string name, int dmg, int res) : m_Name(name), m_Damage(dmg), m_Resistance(res) 
{}

Attack::Attack(std::string name, std::string type, int level) : m_Name(name), m_Type(type), m_Damage(level), m_Cost(level) 
{}

Attack::~Attack(){}

std::string Attack::getName() const { return m_Name; }
std::string Attack::getType() const { return m_Type; }
int Attack::getDamage() const { return m_Damage; }

int Attack::getAttack() const
{
	int strength = m_Damage * 5.0;
	return strength + rand() % strength;
}

int Attack::getResistance() const { return m_Resistance; }
bool Attack::isNotBroken() const { return m_Resistance > 0; }

void Attack::display() const { std::cout << " - " << m_Name << " " << m_Damage << " " << m_Resistance << std::endl; }

void Attack::change(std::string name, int dmg, int res){ m_Name=name; m_Damage = dmg; m_Resistance = res; }


