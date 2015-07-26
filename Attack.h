#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <iostream>
#include <cstdlib>

class Attack
{
	private:
		std::string m_Name;
		std::string m_Type;
		int m_Damage;
		int m_Resistance;
		int m_Cost;

	public:
		Attack();
		Attack(std::string, int, int);
		Attack(std::string, std::string, int level);
		~Attack();

		std::string getName() const;
		std::string getType() const;
		int getDamage() const;
		int getAttack() const;
		int getResistance() const;
		bool isNotBroken() const;
		
		void display() const;
		void change(std::string, int, int);
};

#endif
