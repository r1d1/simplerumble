#include "Agent.h"

Agent::Agent() : m_MaxLife(5), m_Life(5), m_AbilityOne("None", 0, -1)
{
	int nameLength = 3+rand()%10;

	std::string alphabet="aeiouybcdfghjklmnpqrstvwxz";
	int firstLetter = rand() % alphabet.size();
	std::string heroName = "";
	heroName += alphabet.at(firstLetter);
	//std::string vowels="aeiouy";
	//std::string consonants="bcdfghjklmnpqrstvwxz";
	for(int letter=1 ; letter < nameLength ; letter++)
	{
		// vowel or consonant ?
		if( alphabet.substr(0, 6).find(heroName.at(letter-1)) != std::string::npos)
		{
			// We had a vowel, so draw a consonant with prob 0.8 :
			if( (rand() % 10) < 8){	heroName += alphabet[6+ rand() % 20]; }
			else{ heroName += alphabet[rand() % 6]; }
		}		
		else
		{
			// We had a consonant, so draw a vowel with prob 0.9 :
			if( (rand() % 10) < 9){	heroName += alphabet[rand() % 6]; }
			else{ heroName += alphabet[6 +rand() % 20]; }
		}
	}
	m_Name = heroName;
}

Agent::Agent(std::string myname, int maxlife, std::string wname, int dmg, int res) : m_Name(myname), m_MaxLife(maxlife), m_Life(maxlife), m_AbilityOne(wname, dmg, res)
{}

Agent::~Agent(){}

int Agent::getLife() const { return m_Life; }
int Agent::getMaxLife() const { return m_MaxLife; }
bool Agent::isAlive() const { return m_Life > 0; }
void Agent::displayState() const{ std::cout << "I'm " << m_Name << ", I've " << m_Life << "/" << m_MaxLife << " HP and I'm fighting with " << m_AbilityOne.getName() << " that does " << m_AbilityOne.getDamage() << std::endl;  }

void Agent::takeDamage(int value)
{
	int delta = m_Life - value;
	m_Life = (delta < 0 ? 0 : delta);
}

void Agent::attack(Agent & target){ target.takeDamage(m_AbilityOne.getDamage()); }
void Agent::changeAttack(Attack * atk){ m_AbilityOne.change(atk->getName(), atk->getDamage(), atk->getResistance()); }
