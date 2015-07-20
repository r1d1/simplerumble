#include "Agent.h"
#include "utils.h"

Agent::Agent() : m_MaxLife(5), m_Life(5), m_AbilityOne(0)
{
	std::cout << "Dft Ctor" << std::endl;
	//m_AbilityOne = new Attack("None", 0, -1);
	//m_AbilityTwo = new Attack("None", 0, -1);
	//m_AbilityThree = new Attack("None", 0, -1);
	int nameLength = 3+rand()%10;

	m_Name = randomNameGenerator(nameLength);
	std::cout << "Done ..." << std::endl;
}

Agent::Agent(std::string myname, int maxlife, std::string wname, int dmg, int res) : m_Name(myname), m_MaxLife(maxlife), m_Life(maxlife), m_Shield(1), m_defending(1), m_AbilityOne(0), m_AbilityTwo(0), m_AbilityThree(0) 
{
	std::cout << "Comp Ctor" << std::endl;
	//m_AbilityOne = new Attack(wname, dmg, res);
	//m_AbilityTwo = new Attack("None", 0, -1);
	//m_AbilityThree = new Attack("None", 0, -1);
	int nameLength = 3+rand()%10;
	if(myname.empty()){ m_Name = randomNameGenerator(nameLength); }

	std::cout << "Done ..." << std::endl;
}

Agent::~Agent()
{
	// Weapons are external, don't deallocate, it must be done where they have been allocated !
	//std::cout << m_Name << " ab 1" << std::endl;
	//if(m_AbilityOne != 0){ delete m_AbilityOne; }
	//std::cout << m_Name << " ab 2" << std::endl;
	//if(m_AbilityTwo != 0){ delete m_AbilityTwo; }
	//std::cout << m_Name << " ab 3" << std::endl;
	//if(m_AbilityThree != 0){ delete m_AbilityThree; }
	m_AbilityOne = m_AbilityTwo = m_AbilityThree = 0;
}

int Agent::getLife() const { return m_Life; }
int Agent::getMaxLife() const { return m_MaxLife; }
bool Agent::isAlive() const { return m_Life > 0; }
void Agent::displayState() const
{
	std::cout << "I'm \033[1m" << m_Name << "\033[21m, I've \033[" << ((float(m_Life) / float(m_MaxLife) < 0.3) ? "91m" : ((float(m_Life) / float(m_MaxLife) < 0.6) ? "93m" : "92m")) << m_Life << "\033[39m/" << m_MaxLife << " HP and I'm fighting with " << ( (m_AbilityOne != 0) ? m_AbilityOne->getName() : "nothing") << " that does " << ( (m_AbilityOne != 0) ?  m_AbilityOne->getDamage() : 0) << std::endl;
}

void Agent::takeDamage(int value)
{
	int delta = m_Life - (value - m_defending * m_Shield);
	m_Life = (delta < 0 ? 0 : delta);
}

void Agent::attack(Agent & target)
{
	m_defending = 1;
	if(m_AbilityOne != 0){ target.takeDamage(m_AbilityOne->getDamage()); }
}

void Agent::changeAttack(Attack * atk)
{
	m_AbilityOne = atk;
	m_defending = 1;
	//m_AbilityOne->change(atk->getName(), atk->getDamage(), atk->getResistance());
}


void Agent::defend()
{
	m_defending = 2;
}

void Agent::surrender()
{
	m_defending = -1;
}
