#include "utils.h"

std::string randomNameGenerator(int length)
{
	std::string alphabet="aeiouybcdfghjklmnpqrstvwxz";
	int firstLetter = rand() % alphabet.size();
	std::string heroName = "";
	heroName += alphabet.at(firstLetter);
	for(int letter=1 ; letter < length ; letter++)
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
	return heroName;
}
