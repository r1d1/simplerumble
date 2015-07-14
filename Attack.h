#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <iostream>
// This class is a general living agent, will be the mother of two classes (Character and Monster)


class Attack
{
	private:
		std::string m_Name;
		int m_Damage;
		int m_Resistance;

	public:
		Attack();
		Attack(std::string, int, int);
		~Attack();

		std::string getName() const;
		int getDamage() const;
		int getResistance() const;
		bool isNotBroken() const;
		
		void display() const;
		void change(std::string, int, int);
};

#endif
