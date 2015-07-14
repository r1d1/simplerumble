#ifndef AGENT_H
#define AGENT_H

// This class is a general living agent, will be the mother of two classes (Character and Monster)
#include "Attack.h"
#include <string>
#include <iostream>
#include <cstdlib>

class Agent
{
	private:
		std::string m_Name;
		int m_Life;
		int m_MaxLife;
		//int m_AttackDamage;
		Attack m_AbilityOne;
		Attack m_AbilityTwo;
		Attack m_AbilityThree;

	public:
		Agent();
		Agent(std::string, int, std::string, int, int);
		~Agent();
		int getLife() const;
		int getMaxLife() const;
		bool isAlive() const;
		void displayState() const;


		void takeDamage(int value);
		void attack(Agent & target);
		void changeAttack(Attack * atk);
};

#endif
