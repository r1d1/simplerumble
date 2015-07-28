////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
/*
SIMPLE RUMBLE !
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Agent.h"
#include "Attack.h"
#include "utils.h"

#define SPEED 1000
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
//#define WINDOW_HEIGHT 200

int main(int argc, char** argv)
{
	int gameState = 0;
	
	srand(time(NULL));
	// ================ Initialising ! ================
	// Create main window
	// Black screen
	sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SIMPLE RUMBLE !!!");
	
	sf::Sprite * opponentSprite;
	sf::Sprite * playerSprite;
	
	sf::Image character1Image;
	sf::Sprite character1Sprite;
	sf::Image character2Image;
	sf::Sprite character2Sprite;
	if (!character1Image.LoadFromFile("images/npc1-full.png")){ std::cout << "Error when loading opponent image" << std::endl; return EXIT_FAILURE; }
	else{ character1Sprite.SetImage(character1Image); }
	if (!character2Image.LoadFromFile("images/npc2-full.png")){ std::cout << "Error when loading player image" << std::endl; return EXIT_FAILURE; }
	else{ character2Sprite.SetImage(character2Image); }

	character1Sprite.SetSubRect(sf::IntRect(32, 96, 64, 144));
	character2Sprite.SetSubRect(sf::IntRect(32, 48, 64, 96));
	character1Sprite.SetScale(2.0f, 2.0f);
	character2Sprite.SetScale(2.0f, 2.0f);
	character1Sprite.SetPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
	character2Sprite.SetPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
	
	bool posOne = true;

	sf::Image axeImage;
	sf::Sprite axeSprite;
	sf::Image swordImage;
	sf::Sprite swordSprite;
	if (!axeImage.LoadFromFile("images/axe.png")){ std::cout << "Error when loading axe image" << std::endl; return EXIT_FAILURE; }
	else{ axeSprite.SetImage(axeImage); }
	if (!swordImage.LoadFromFile("images/sword.png")){ std::cout << "Error when loading sword image" << std::endl; return EXIT_FAILURE; }
	else{ swordSprite.SetImage(swordImage); }

	App.Clear(sf::Color(0,0,0));
	App.Display();

	// ##### TITLE Interface #####
	// State 0
	sf::String titleText;
	titleText.SetText("SIMPLE RUMBLE !");
	titleText.SetSize(48);
	titleText.SetRotation(20);
//	titleText.SetCenter(WINDOW_WIDTH * 3/10, WINDOW_HEIGHT *2/10);
	titleText.SetPosition(WINDOW_WIDTH * 1.0/5, WINDOW_HEIGHT * 2.5/5);

	// ##### MENU Interface #####
	std::cout << "Done." << std::endl << "Init Menu ..." << std::endl;

	sf::Image cursorImage;
	sf::Sprite cursorSprite;
	if (!cursorImage.LoadFromFile("images/menuSelect2.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
	else{ cursorSprite.SetImage(cursorImage); }

	cursorSprite.SetScale(0.2f, 0.2f);

	sf::String choice0;

	choice0.SetPosition(WINDOW_WIDTH *4.5/ 10, WINDOW_HEIGHT * 6 / 10);
	choice0.SetColor(sf::Color::Red);
	bool startColorState=true;

	sf::String choice1;
	sf::String choice2;
	sf::String choice3;
	sf::String choice4;
	sf::String choice5;
	sf::String choice6;
	sf::String choice7;

	choice0.SetText("Start");
	choice0.SetSize(32);

	choice1.SetText("Attack");
	choice1.SetSize(16);
	
	choice2.SetText("Defend");
	choice2.SetSize(16);
	
	choice3.SetText("Surrender");
	choice3.SetSize(16);
	
	choice4.SetText("Do nothing");
	choice4.SetSize(16);
	
	choice5.SetText("Quit");
	choice5.SetSize(16);
	
	choice6.SetText("End of the Game !");
	choice6.SetSize(32);

	choice7.SetText("Play again !");
	choice7.SetSize(16);
	
	choice1.SetPosition(25.0f, WINDOW_HEIGHT * 4.5 / 5);
	choice2.SetPosition(25.0f + WINDOW_WIDTH * 1 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice3.SetPosition(25.0f + WINDOW_WIDTH * 2 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice4.SetPosition(25.0f + WINDOW_WIDTH * 3 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice5.SetPosition(25.0f + WINDOW_WIDTH * 4 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice6.SetPosition(25.0f + WINDOW_WIDTH * 0.5 / 2, WINDOW_HEIGHT / 4);
	choice7.SetPosition(WINDOW_WIDTH * 1.05 / 3, WINDOW_HEIGHT * 4.5 / 5);
	
	// -------------------------------------------------------------
	int menuChoice = 0;
	int maxMenuChoices = 5;
	// 0 : attack ; 1 : defend ; 2 : surrender ; 3 : do nothing ; 4 : quit game
	int characterChoice = 0;
	int maxCharacterChoices = 2;
	int endMenuChoice = 0;
	int maxEndMenuChoices = 2;

	// -------------------------------------------------------------
	Attack sword("Sword", 3, 450);
	Attack axe("Axe", 10, 350);
	// Attack type :
	// Moon
	// Feather
	// Light
	std::vector<std::string> attackTypes;
	attackTypes.push_back("Moon");
	attackTypes.push_back("Feather");
	attackTypes.push_back("Light");

	std::vector<Attack> attackList;
	Attack attackOne("Blade", attackTypes.at(0), 2);
	Attack attackTwo("Blade", attackTypes.at(1), 1);
	Attack attackThree("Blade", attackTypes.at(2), 1);
	attackList.push_back(attackOne);
	attackList.push_back(attackTwo);
	attackList.push_back(attackThree);

	Agent * opponent;
	Agent * player;

	Agent character1("", 70 + rand() % 30);
	Agent character2("", 70 + rand() % 30);

	// ----------------------------------------
	std::vector<Agent> characters;

	// ----------------------------------------
	// Start game loop
	float cumulativeTime = 0.0;
	float cursorPosX=0.0, cursorPosY=0.0;
	cursorSprite.SetPosition(cursorPosX, cursorPosY);
	while (App.IsOpened())
	{
		// Process events
		sf::Event Event;
		float elapsedTime = App.GetFrameTime();
		bool validatedChoice = false;
		int enemyChoice;

		while (App.GetEvent(Event))
		{
			// Event processing
			if(Event.Type == sf::Event::Closed){ App.Close(); }
			if(Event.Type == sf::Event::KeyPressed)
			{
				switch(gameState)
				{
					case 0 : // Titlescreen
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ gameState = 1; }
					
					//	if (App.GetInput().IsKeyDown(sf::Key::F1)){ std::cout << "F1" << std::endl; }
					//	if (App.GetInput().IsKeyDown(sf::Key::F2)){ std::cout << "F2" << std::endl; }
					//	if (App.GetInput().IsKeyDown(sf::Key::F3)){ std::cout << "F3" << std::endl; }
					//	if (App.GetInput().IsKeyDown(sf::Key::F4)){ std::cout << "F4" << std::endl; }
					//	
					//	if (App.GetInput().IsKeyDown(sf::Key::Back)){ std::cout << "Back" << std::endl; }
					//	
					//	if (App.GetInput().IsKeyDown(sf::Key::Numpad0)){ std::cout << "Np0" << std::endl; }
					//	if (App.GetInput().IsKeyDown(sf::Key::Numpad1)){ std::cout << "Np1" << std::endl; }

					break;
					case 1 : // Character Selection
						
						if (App.GetInput().IsKeyDown(sf::Key::Left)){ characterChoice = ( ((characterChoice-1)>0)? characterChoice-1 : 0); }
						if (App.GetInput().IsKeyDown(sf::Key::Right)){ characterChoice = ( ((characterChoice+1) < maxCharacterChoices-1)? characterChoice+1 : maxCharacterChoices-1); }
						player = ((!characterChoice) ? &character1 : &character2);
						opponent = ((!characterChoice) ? &character2 : &character1);
						playerSprite = ((characterChoice) ? &character1Sprite : &character2Sprite);
						opponentSprite = ((characterChoice) ? &character2Sprite : &character1Sprite);
					


						std::cout << "character choice " << characterChoice << std::endl;
						if (App.GetInput().IsKeyDown(sf::Key::Return))
						{
							gameState = 2;
							opponentSprite->SetPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
							playerSprite->SetPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
						}
					break;
					case 2 :
						if( !player->isAlive() || !opponent->isAlive() ){ gameState = 3; }
						else
						{
							// Switching on options :
							if (App.GetInput().IsKeyDown(sf::Key::Return)){ validatedChoice = true; }
							if (App.GetInput().IsKeyDown(sf::Key::Left)){ menuChoice = ( ((menuChoice-1)>0)? menuChoice-1 : 0); }
							if (App.GetInput().IsKeyDown(sf::Key::Right)){ menuChoice = ( ((menuChoice+1) < maxMenuChoices-1)? menuChoice+1 : maxMenuChoices-1); }
							if (App.GetInput().IsKeyDown(sf::Key::Up)){ menuChoice = ( ((menuChoice-1)>0)? menuChoice-1 : 0); }
							if (App.GetInput().IsKeyDown(sf::Key::Down)){ menuChoice = ( ((menuChoice+1) < maxMenuChoices-1)? menuChoice+1 : maxMenuChoices-1); }
							if (App.GetInput().IsKeyDown(sf::Key::A)){ player->changeAttack(&attackOne); opponent->changeAttack(&attackTwo); std::cout << "You got the Axe !" << std::endl; }
						}
					break;
					case 3 :
						//if( !player->isAlive() || !opponent->isAlive() ){ gameState = 3; }
						//else
						//{
						std::cout << "End state !" << std::endl;
							// Switching on options :
						if (App.GetInput().IsKeyDown(sf::Key::Left)){ endMenuChoice = ( ((endMenuChoice-1)>0)? endMenuChoice-1 : 0); }
						if (App.GetInput().IsKeyDown(sf::Key::Right)){ endMenuChoice = ( ((endMenuChoice+1) < maxEndMenuChoices-1)? endMenuChoice+1 : maxEndMenuChoices-1); }
						std::cout << "character choice " << endMenuChoice << std::endl;

						if (App.GetInput().IsKeyDown(sf::Key::Return))
						{
							if(endMenuChoice == 0)
							{
								// If play again, back to character selection screen
								gameState = 1; 
								// Reset if we already finished a game :
								character1.resetCharacter();
								character2.resetCharacter();
								character1Sprite.SetPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
								character2Sprite.SetPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
							} 
							else{ App.Close(); } // if quit
						}
					break;
					default :
						std::cout << "Should not happen in the final game." << std::endl;
						std::cout << "Unexpected display state !" << std::endl;
						App.Close();
					break;
				}
			//	std::cout << "Menu choice : " << menuChoice << std::endl;
			}
			switch(gameState)
			{
				case 1 :
					cursorSprite.SetScale(0.17f, 0.17f);
					cursorPosX = (WINDOW_WIDTH * (characterChoice + 0.84))  / 3;
					cursorPosY = 20.0f;
				break;
				case 2 :
					cursorSprite.SetScale(0.1f, 0.1f);
					cursorPosX = (WINDOW_WIDTH * (menuChoice)) / maxMenuChoices;
					cursorPosY = WINDOW_HEIGHT - 45.0f;
				break;
				case 3 :
					cursorSprite.SetScale(0.1f, 0.1f);
					cursorPosX = (WINDOW_WIDTH * (endMenuChoice + 0.6)) / maxEndMenuChoices + 0.5;
					std::cout << "cursor x : " << cursorPosX << std::endl;
					cursorPosY = WINDOW_HEIGHT - 45.0f;
				break;
				default:
					cursorPosX = -100; 
					cursorPosY = -100;
				break;
			}
			if(validatedChoice) // should go in config variable fightState = 2;
			{
				enemyChoice = rand() % maxMenuChoices;
				switch(menuChoice)
				{
					case 0:
						std::cout << "Attacking !" << std::endl;
						player->attack(*opponent);
					break;
					case 1:
						std::cout << "Defending !" << std::endl;
						player->defend();
					break;
					case 2:
						std::cout << "Surrender !" << std::endl;
						player->surrender();
					break;
					case 3:
						std::cout << "You coward !" << std::endl;
						player->takeDamage(rand() % 10);
					break;
					case 4:
						App.Close();
					break;
					default:
						std::cout << "Unknown choice" << std::endl;
					break;
				}
				validatedChoice = false;
				switch(enemyChoice)
				{
					case 0:
						std::cout << "Attacking !" << std::endl;
						opponent->attack(*player);
					break;
					case 1:
						std::cout << "Defending !" << std::endl;
						opponent->defend();
					break;
					case 2:
						std::cout << "Surrender !" << std::endl;
						opponent->surrender();
					break;
					default:
						std::cout << "Wrong choice !" << std::endl;
						opponent->takeDamage(2);
					break;
				}
				std::cout << "Player state : " << std::endl;
				player->displayState();
				std::cout << "Opponent state : " << std::endl;
				opponent->displayState();
			}
		}
		cursorSprite.SetPosition(cursorPosX, cursorPosY);
		App.Clear(sf::Color::Black);

		sf::String char1Name(character1.getName());
		sf::String char1MaxLife("Life : " + std::to_string(character1.getMaxLife()));
		sf::String char1Shield("Shield : " + std::to_string(character1.getShield()));

		sf::String char2Name(character2.getName());
		sf::String char2MaxLife("Life : " + std::to_string(character2.getMaxLife()));
		sf::String char2Shield("Shield : " + std::to_string(character2.getShield()));

		char1Name.SetPosition(WINDOW_WIDTH * 0.3 / 3, WINDOW_HEIGHT * 0.8 / 4);
		char1Name.SetSize(24);
		char1MaxLife.SetPosition(WINDOW_WIDTH * 0.3 / 3, WINDOW_HEIGHT * 1.7 / 4);
		char1MaxLife.SetSize(24);
		char1Shield.SetPosition(WINDOW_WIDTH * 0.3 / 3, WINDOW_HEIGHT * 2 / 4);
		char1Shield.SetSize(24);
			
		char2Name.SetPosition(WINDOW_WIDTH * 2.3 / 3, WINDOW_HEIGHT * 0.8 / 4);
		char2Name.SetSize(24);
		char2MaxLife.SetPosition(WINDOW_WIDTH * 2.3 / 3, WINDOW_HEIGHT * 1.7 / 4);
		char2MaxLife.SetSize(24);
		char2Shield.SetPosition(WINDOW_WIDTH * 2.3 / 3, WINDOW_HEIGHT * 2 / 4);
		char2Shield.SetSize(24);
		
		cumulativeTime += elapsedTime;

		float playerRatio = 0.0;
		float opponentRatio = 0.0;
		if( player && (player->getMaxLife() != 0) ){ playerRatio = float(player->getLife()) / player->getMaxLife(); }
		if( opponent && (opponent->getMaxLife() !=0) ){ opponentRatio = float(opponent->getLife()) / opponent->getMaxLife(); }
	
//		std::cout << playerRatio << " " << opponentRatio << std::endl;
		switch(gameState)
		{
			case 0:
				// State : Title 
				if(cumulativeTime > 0.5)
				{
					// Animation of Sprites
					if( posOne ){ choice0.SetColor(sf::Color::Red); }
					else{ choice0.SetColor(sf::Color::White); }
					cumulativeTime = 0.0;
					posOne = !posOne;
				}
				titleText.SetColor(sf::Color(192, 64, 0));
				titleText.SetScale(1.1f,1.1f);
				App.Draw(titleText);
				titleText.SetColor(sf::Color(255, 255, 0));
				App.Draw(titleText);
				
				startColorState = !startColorState;
				
				App.Draw(choice0);
			break;
			case 1 :
				character1Sprite.SetSubRect(sf::IntRect(0, 0, 32, 48));
				character2Sprite.SetSubRect(sf::IntRect(0, 0, 32, 48));
				App.Draw(char1Name);
				App.Draw(char1MaxLife);
				App.Draw(char1Shield);
				App.Draw(char2Name);
				App.Draw(char2MaxLife);
				App.Draw(char2Shield);

				App.Draw(character1Sprite);
				App.Draw(character2Sprite);
			break;
			case 2 :
				App.Clear(sf::Color(0, 192, 255));
				if(cumulativeTime > 0.5)
				{
					if( posOne )
					{
						// Animation of Sprites
						opponentSprite->SetSubRect(sf::IntRect(0, 96, 32, 144));
						playerSprite->SetSubRect(sf::IntRect(64, 48, 96, 96));
					}
					else
					{
						opponentSprite->SetSubRect(sf::IntRect(32, 96, 64, 144));
						playerSprite->SetSubRect(sf::IntRect(32, 48, 64, 96));
					}
					cumulativeTime = 0.0;
					posOne = !posOne;
				}

				// Life slot

				App.Draw(sf::Shape::Circle(10, 10, 50, sf::Color((1.0 - playerRatio) * 255, playerRatio * 255, 0), 5, sf::Color(255, 255, 255))); //, sf::Color::Black, 0, sf::Color::Red);
				App.Draw(sf::Shape::Circle(WINDOW_WIDTH-10, 10, 50, sf::Color((1.0 - opponentRatio) * 255, opponentRatio * 255, 0), 5, sf::Color(255, 255, 255))); //, sf::Color::Black, 0, sf::Color::Red);
				
				// BG :
				App.Draw(sf::Shape::Rectangle(0, WINDOW_HEIGHT * 0.8/2, WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(192, 128, 64), 0, sf::Color(128,128,0))); //, sf::Color::Black, 0, sf::Color::Red);
				// Menu : 
				App.Draw(sf::Shape::Rectangle(0, WINDOW_HEIGHT * 4.2/5, WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(192, 0, 0), 5, sf::Color(64, 0, 0))); //, sf::Color::Black, 0, sf::Color::Red);
				App.Draw(*opponentSprite);
				App.Draw(*playerSprite);
				App.Draw(choice1);
				App.Draw(choice2);
				App.Draw(choice3);
				App.Draw(choice4);
				App.Draw(choice5);
			break;
			case 3 :
				// End state :
				App.Draw(choice5);
				App.Draw(choice6);
				App.Draw(choice7);
			break;
			default:
				std::cout << "Unexpected display state !" << std::endl;
				App.Close();
			break;
		}
		App.Draw(cursorSprite);
		App.Display();
	}

	// Reseting pointers (not useful ?)
	player = opponent = 0;

	return EXIT_SUCCESS;
}

