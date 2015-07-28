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

//	sf::Sprite * opponentSprite;
//	sf::Sprite * playerSprite;
//	opponentSprite.SetPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
//	playerSprite.SetPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);

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
	titleText.SetSize(32);
	titleText.SetPosition(WINDOW_WIDTH * 3/10, WINDOW_HEIGHT *2/10);

	sf::String stateText;
	titleText.SetText("State 0");
	titleText.SetSize(32);
	titleText.SetPosition(10, 10);
	// ##### MENU Interface #####

	std::cout << "Done." << std::endl << "Init Menu ..." << std::endl;

	//sf::Image cursorImage(15, 15, sf::Color(0, 255, 0));
//	cursor.SetImage(cursorImage);
	sf::Image cursorImage;
	sf::Sprite cursorSprite;
	if (!cursorImage.LoadFromFile("images/menuSelect2.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
	else{ cursorSprite.SetImage(cursorImage); }

	cursorSprite.SetScale(0.2f, 0.2f);

	sf::String choice0;

	//choice0.SetPosition(WINDOW_WIDTH *4.5/ 10, WINDOW_HEIGHT * 6 / 10);
	choice0.SetPosition(WINDOW_WIDTH *4.5/ 10, WINDOW_HEIGHT * 6 / 10);
	choice0.SetColor(sf::Color::Red);
	bool startColorState=true;

	sf::String choice1;
	sf::String choice2;
	sf::String choice3;
	sf::String choice4;
	sf::String choice5;

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

	
	choice1.SetPosition(25.0f, WINDOW_HEIGHT * 4 / 5);
	choice2.SetPosition(25.0f + WINDOW_WIDTH * 1 / 5, WINDOW_HEIGHT * 4 / 5);
	choice3.SetPosition(25.0f + WINDOW_WIDTH * 2 / 5, WINDOW_HEIGHT * 4 / 5);
	choice4.SetPosition(25.0f + WINDOW_WIDTH * 3 / 5, WINDOW_HEIGHT * 4 / 5);
	choice5.SetPosition(25.0f + WINDOW_WIDTH * 4 / 5, WINDOW_HEIGHT * 4 / 5);
	
	// -------------------------------------------------------------
	int menuChoice = 0;
	int maxMenuChoices = 5;
	// 0 : attack ; 1 : defend ; 2 : surrender ; 3 : do nothing ; 4 : quit game
	int characterChoice = 0;
	int maxCharacterChoices = 2;

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
	Attack attackOne("Blade", attackTypes.at(0), 1);
	Attack attackTwo("Blade", attackTypes.at(1), 1);
	Attack attackThree("Blade", attackTypes.at(2), 1);
	attackList.push_back(attackOne);
	attackList.push_back(attackTwo);
	attackList.push_back(attackThree);

	//Attack axe("Axe", 10, 350);
	Agent * opponent;
	Agent * player;

	//player = new Agent("", 100, "Wooden sword", 3, 500);
	//opponent = new Agent("", 90, "Axe", 4, 500);
	Agent character1("", 70 + rand() % 30);
	Agent character2("", 70 + rand() % 30);

	std::vector<Agent> characters;

	// ----------------------------------------
	// Start game loop
	//opponent->displayState();
	//player->displayState();
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
					case 2 : // Switching on options :
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ validatedChoice = true; }
						if (App.GetInput().IsKeyDown(sf::Key::Left)){ menuChoice = ( ((menuChoice-1)>0)? menuChoice-1 : 0); }
						if (App.GetInput().IsKeyDown(sf::Key::Right)){ menuChoice = ( ((menuChoice+1) < maxMenuChoices-1)? menuChoice+1 : maxMenuChoices-1); }
						if (App.GetInput().IsKeyDown(sf::Key::Up)){ menuChoice = ( ((menuChoice-1)>0)? menuChoice-1 : 0); }
						if (App.GetInput().IsKeyDown(sf::Key::Down)){ menuChoice = ( ((menuChoice+1) < maxMenuChoices-1)? menuChoice+1 : maxMenuChoices-1); }
						if (App.GetInput().IsKeyDown(sf::Key::A)){ player->changeAttack(&attackOne); opponent->changeAttack(&attackTwo); std::cout << "You got the Axe !" << std::endl; }
					//	if (App.GetInput().IsKeyDown(sf::Key::S)){ player->changeAttack(&sword); opponent->changeAttack(&axe); std::cout << "You got the Sword !" << std::endl; }
					break;
					default :
						std::cout << "Should not happen in the final game." << std::endl;
					break;
				}
			//	std::cout << "Menu choice : " << menuChoice << std::endl;
			}
			switch(gameState)
			{
				case 1 :
					cursorSprite.SetScale(0.17f, 0.17f);
					cursorPosX = (WINDOW_WIDTH * (characterChoice + 0.84))  / 3;
					cursorPosY = 10.0f;
				break;
				case 2 :
					cursorSprite.SetScale(0.1f, 0.1f);
					cursorPosX = (WINDOW_WIDTH * (menuChoice)) / maxMenuChoices;
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
		sf::String char1MaxLife(std::to_string(character1.getMaxLife()));
		sf::String char1Shield(std::to_string(character1.getShield()));
		char1Name.SetPosition(WINDOW_WIDTH * 0.4 / 3, WINDOW_HEIGHT / 4);
		char1Name.SetSize(24);
		char1MaxLife.SetPosition(WINDOW_WIDTH * 0.4 / 3, WINDOW_HEIGHT * 1.5 / 4);
		char1MaxLife.SetSize(24);
		char1Shield.SetPosition(WINDOW_WIDTH * 0.4 / 3, WINDOW_HEIGHT * 2 / 4);
		char1Shield.SetSize(24);
	
		sf::String char2Name(character2.getName());
		sf::String char2MaxLife(std::to_string(character2.getMaxLife()));
		sf::String char2Shield(std::to_string(character2.getShield()));
		char2Name.SetPosition(WINDOW_WIDTH * 2.2 / 3, WINDOW_HEIGHT / 4);
		char2Name.SetSize(24);
		char2MaxLife.SetPosition(WINDOW_WIDTH * 2.2 / 3, WINDOW_HEIGHT * 1.5 / 4);
		char2MaxLife.SetSize(24);
		char2Shield.SetPosition(WINDOW_WIDTH * 2.2 / 3, WINDOW_HEIGHT * 2 / 4);
		char2Shield.SetSize(24);
		
		switch(gameState)
		{
			case 0:
				// State : Title 
				App.Draw(titleText);
				startColorState = !startColorState;
				choice0.SetColor( ((startColorState) ? sf::Color::White : sf::Color::Yellow) );
				App.Draw(choice0);
			break;
			case 1 :
				//opponentSprite->SetSubRect(sf::IntRect(0, 0, 32, 48));
				//playerSprite->SetSubRect(sf::IntRect(0, 0, 32, 48));
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
				cumulativeTime += elapsedTime;
				if(cumulativeTime > 0.5)
				{
					if( posOne )
					{
						// Animation of Sprites
						opponentSprite->SetSubRect(sf::IntRect(0, 96, 32, 144));
						playerSprite->SetSubRect(sf::IntRect(64, 48, 96, 96));
//						std::cout << cumulativeTime << std::endl;
					}
					else
					{
						opponentSprite->SetSubRect(sf::IntRect(32, 96, 64, 144));
						playerSprite->SetSubRect(sf::IntRect(32, 48, 64, 96));
//						std::cout << cumulativeTime << std::endl;
					}
					cumulativeTime = 0.0;
					posOne = !posOne;
				}

				App.Draw(sf::Shape::Rectangle(10, 180, 590, 210, sf::Color(128, 192, 0), 0, sf::Color::Black)); //, sf::Color::Black, 0, sf::Color::Red);
				App.Draw(*opponentSprite);
				App.Draw(*playerSprite);
				App.Draw(choice1);
				App.Draw(choice2);
				App.Draw(choice3);
				App.Draw(choice4);
				App.Draw(choice5);
			break;
			default:
			break;
		}
		App.Draw(cursorSprite);
		App.Display();
	}

	//delete player;
	//delete opponent;
	// Reseting pointers (not useful ?)
	player = opponent = 0;

	return EXIT_SUCCESS;
}

/*int main()
{
	int menuChoice = -1,i=255;
	int counter = 0;
	int gameState = 0;
	
	// ================ Initialisation ! ================
	// State 0
	// Create main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SIMPLE RUMBLE !!!");
	
	App.Clear(sf::Color(0,0,0));
    App.Display();

	// ##### Scene #####
//	Minipers heros;
	//sf::Image perso;
	sf::Image imageBackground;
	sf::Image imageHouse;

	sf::Image perso;
	sf::Sprite persoSprite;
	sf::Sprite backgroundSprite;
	sf::Sprite houseSprite;

	App.Clear(sf::Color(64,0,0));
    App.Display();

	// ##### TITLE Interface #####

	std::cout << "Done." << std::endl << "Init title ..." << std::endl;

	sf::String titleText;
	titleText.SetText("SIMPLE RUMBLE !");
	titleText.SetSize(32);
	titleText.SetPosition(WINDOW_WIDTH * 3/10, WINDOW_HEIGHT *4/10);

	
	
	// ##### MENU Interface #####

	std::cout << "Done." << std::endl << "Init Menu ..." << std::endl;

	sf::String choice0;

	sf::String choice1;
	sf::String choice2;
	sf::String choice3;
	sf::String choice4;

	choice0.SetText("Start");
	
	choice1.SetText("Play");
	choice2.SetText("Help");
	choice3.SetText("Tadaaaaaa !");
	choice4.SetText("Quit");

	choice0.SetPosition(WINDOW_WIDTH *4.5/ 10, WINDOW_HEIGHT * 6 / 10);
	choice0.SetColor(sf::Color::Red);
	bool startColorState=true;
	
	choice1.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 10);
	choice2.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2 / 5);
	choice3.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	choice4.SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 5);
	
	// ##### GAME Interface #####

	std::cout << "Done." << std::endl << "Init Game interface ..." << std::endl;

	sf::Image imageEpee;
	sf::Image imageEpee_magique;
	sf::Image imageBouclier;
	sf::Image imageBouclier_magique;
	sf::Sprite armeSprite;
	sf::Sprite defenseSprite;

	App.Clear(sf::Color(128,0,0));
    App.Display();

	sf::String pvs;
	sf::String mana;
	sf::String nom_display;

	sf::String stateText;
//	stateText.SetPosition(WINDOW_WIDTH /4, 0);
	
	std::stringstream pvs_display;
	std::stringstream mana_display;
//	pvs_display << heros.getVie();
//	pvs_display.str();


	//sf::Image boutons;
	//sf::Sprite boutonsSprite;

	sf::Shape carre;
	//sf::Rect rectangle1(10, 10, 790, 590); //, sf::Color::Black, 0, sf::Color::Red);
	//sf::Shape::Rectangle (10, 10, 790, 590, sf::Color::Black, 0, sf::Color::Red);

	App.Clear(sf::Color(196,0,0));
    App.Display();


	srand(time(NULL));
	
//	heros.setNom("Bob");
	
	pvs.SetText(pvs_display.str()); //heros.getNom());
//	pvs.SetPosition(8,13);
	pvs.SetScale(0.6f, 0.6f);
	mana.SetScale(0.6f, 0.6f);
//	nom_display.SetText(heros.getNom());
//	nom_display.SetPosition(48, 13);
	nom_display.SetScale(0.6f, 0.6f);
//    
//	carre.AddPoint(200, 200, sf::Color(255, 255, 0), sf::Color(255,255,255));
//    carre.AddPoint(400, 200, sf::Color(255, 255, 0), sf::Color(255,0,0));
//    carre.AddPoint(400, 400, sf::Color(0, 255, 255), sf::Color(0,255,0));
//    carre.AddPoint(200, 400, sf::Color(0, 255, 255), sf::Color(0,0,255));
//    carre.EnableFill(true); // Remplissage activ
//    carre.EnableOutline(true); // Bordures actives
//    carre.SetOutlineWidth(10); // Bordures de taille 20 pixels
	
	backgroundSprite.Scale(6.0f, 6.0f);
	backgroundSprite.SetPosition(0, 50);
	houseSprite.Scale(6.0f, 6.0f);
	houseSprite.SetPosition(0, 50);	
	
// 	if (!boutons.LoadFromFile("images/boutons.png")) // Si le chargement du fichier a chou
//	{
//		std::cout << "Erreur durant le chargement de l'image boutons" << std::endl;
//		return EXIT_FAILURE; // On ferme le programme
//	}
//	else // Si le chargement de l'image a russi
//	{
//		boutonsSprite.SetImage(boutons);
//	}
	
	std::cout << "Done." << std::endl << "Loading Pictures ..." << std::endl;

	
	if (!imageBackground.LoadFromFile("images/tuilev1.png"))
	{
		std::cout << "Erreur durant le chargement de l'image boutons" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}
	else // Si le chargement de l'image a russi
	{
		backgroundSprite.SetImage(imageBackground);
	}
	
	if (!imageHouse.LoadFromFile("images/tuilev1_2.png"))
	{
		std::cout << "Erreur durant le chargement de l'image boutons" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}
	else // Si le chargement de l'image a russi
	{
		houseSprite.SetImage(imageHouse);
	}
	
		
//	boutonsSprite.SetPosition(100,100);
//	boutonsSprite.SetSubRect(sf::IntRect(200, 0, 350, 60));

	// mechant.png
	
	//if (!perso.LoadFromFile("images/gifle.png")) // Si le chargement du fichier a chou
	if (!perso.LoadFromFile("images/mechant2.png")) // Si le chargement du fichier a chou
	{
		std::cout << "Erreur durant le chargement de l'image gifle" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}
	else // Si le chargement de l'image a russi
	{
		persoSprite.SetImage(perso);
	}

	persoSprite.SetPosition(400,300);
	persoSprite.SetSubRect(sf::IntRect(26, 71, 44, 96));
	persoSprite.Scale(sf::Vector2f(2.0,2.0));

	if (!imageEpee.LoadFromFile("images/epee.png"))
	{
		std::cout << "Erreur durant le chargement de l'image epee" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}
	else // Si le chargement de l'image a russi
	{
		armeSprite.SetImage(imageEpee);
	}

	if (!imageEpee_magique.LoadFromFile("images/epee2.png"))
	{
		std::cout << "Erreur durant le chargement de l'image epee2" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	if (!imageBouclier.LoadFromFile("images/bouclier.png"))
	{
		std::cout << "Erreur durant le chargement de l'image bouclier" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}
	else // Si le chargement de l'image a russi
	{
		defenseSprite.SetImage(imageBouclier);
	}

	if (!imageBouclier_magique.LoadFromFile("images/bouclier2.png"))
	{
		std::cout << "Erreur durant le chargement de l'image bouclier 2" << std::endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	App.Clear(sf::Color(255,0,0));
    App.Display();
	
	// ###### END OF LOADING
	gameState = 1;
	stateText.SetText("State 1");

    // Start game loop
    while (App.IsOpened())
    {
	    // Process events
        sf::Event Event;
		float ElapsedTime = App.GetFrameTime();

		
		while (App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed){ App.Close(); }

			// Event processing
			if(Event.Type == sf::Event::KeyPressed)
			{
				switch(gameState)
				{
					case 1 :
						//if (App.GetInput().IsKeyDown(sf::Key::Left)){ std::cout << "touche Gauche" << std::endl; }
						//if (App.GetInput().IsKeyDown(sf::Key::Right)){ std::cout << "touche Right" << std::endl; }
						//if (App.GetInput().IsKeyDown(sf::Key::Up)){ std::cout << "touche Up" << std::endl; }
						//if (App.GetInput().IsKeyDown(sf::Key::Down)){ std::cout << "touche Down" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ std::cout << "NextState" << std::endl; gameState = 2; stateText.SetText("State 2"); }
						//stateText.SetText("State 1");
					break;
					case 2 :
						//boutonsSprite.SetSubRect(sf::IntRect(200, 0, 350, 60));
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ std::cout << "touche ENTER ! VALIDATION" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Left)){ std::cout << "touche Gauche" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Right)){ std::cout << "touche Right" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Up)){ std::cout << "touche Up" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Down)){ std::cout << "touche Down" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::A)){ std::cout << "NextState" << std::endl; gameState = 3; stateText.SetText("State 3"); }
						//stateText.SetText("State 2");
					break;
					case 3 :
						if (App.GetInput().IsKeyDown(sf::Key::Q)){ std::cout << "Q (action 1)" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::S)){ std::cout << "S (action 2)" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::D)){ std::cout << "D (action 3)" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ std::cout << "touche ENTER ! VALIDATION" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Left)){ std::cout << "touche Gauche" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Right)){ std::cout << "touche Right" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Up)){ std::cout << "touche Up" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Down)){ std::cout << "touche Down" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::A)){ std::cout << "NextState" << std::endl; gameState = 1; stateText.SetText("State 1"); }
						//stateText.SetText("State 3");
					break;
					default :
						std::cout << "Should not happen in the final game." << std::endl;
					break;
				}
			}
		}
//		float ElapsedTime = App.GetFrameTime();
        // Process events
//        sf::Event Event;

//        while (App.GetEvent(Event))
//        {
//            // Close window : exit
//            if (Event.Type == sf::Event::Closed){ App.Close(); }
//							
//		//	if(Event.Type == sf::Event::KeyPressed)
//		//	{
//		//		//boutonsSprite.SetSubRect(sf::IntRect(200, 0, 350, 60));
//
//		//		if (App.GetInput().IsKeyDown(sf::Key::Left))
//		//		{
//		//			if(counter == 0)
//		//			{
//		//				std::cout << "touche Gauche" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(49, 104, 67, 104+23));
//		//				persoSprite.Move(-SPEED * ElapsedTime, 0);
//
//		//				counter = 1;
//		//			}
//		//			else
//		//			{
//		//				if(counter == 1)
//		//				{
//		//					std::cout << "touche Gauche" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(26, 103, 44, 103+24));
//		//					persoSprite.Move(-SPEED * ElapsedTime, 0);
//		//					counter = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(counter == 2)
//		//					{
//		//						std::cout << "touche Gauche" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(1, 104, 20, 104+23));
//		//						persoSprite.Move(-SPEED * ElapsedTime, 0);
//		//						counter = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//		//		if (App.GetInput().IsKeyDown(sf::Key::Right))
//		//		{
//		//			if(counter == 0)
//		//			{
//		//				std::cout << "touche Droite 1" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(54, 39, 71, 64));
//		//				persoSprite.Move(SPEED * ElapsedTime, 0);
//
//		//				counter = 1;
//		//			}
//		//			else
//		//			{
//		//				if(counter == 1)
//		//				{
//		//					std::cout << "touche Droite 2" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(30, 39, 49, 64));
//		//					persoSprite.Move(SPEED * ElapsedTime, 0);
//		//					counter = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(counter == 2)
//		//					{
//		//						std::cout << "touche Droite 3" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(5, 39, 23, 64));
//		//						persoSprite.Move(SPEED * ElapsedTime, 0);
//		//						counter = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//
//		//		if (App.GetInput().IsKeyDown(sf::Key::Up))
//		//		{
//		//			if(counter == 0)
//		//			{
//		//				std::cout << "touche Droite" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(49, 8, 67, 32));
//		//				persoSprite.Move(0, -SPEED * ElapsedTime);
//
//		//				counter = 1;
//		//			}
//		//			else
//		//			{
//		//				if(counter == 1)
//		//				{
//		//					std::cout << "touche Droite" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(26, 7, 44, 32));
//		//					persoSprite.Move(0, -SPEED * ElapsedTime);
//		//					counter = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(counter == 2)
//		//					{
//		//						std::cout << "touche Droite" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(1, 8, 20, 32));
//		//						persoSprite.Move(0, -SPEED * ElapsedTime);
//		//						counter = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//		//		
//		//		if (App.GetInput().IsKeyDown(sf::Key::Down))
//		//		{
//		//			if(counter == 0)
//		//			{
//		//				std::cout << "touche Droite" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(49, 72, 67, 96));
//		//				persoSprite.Move(0, SPEED * ElapsedTime);
//
//		//				counter = 1;
//		//			}
//		//			else
//		//			{
//		//				if(counter == 1)
//		//				{
//		//					std::cout << "touche Droite" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(26, 71, 44, 96));
//		//					persoSprite.Move(0, SPEED * ElapsedTime);
//		//					counter = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(counter == 2)
//		//					{
//		//						std::cout << "touche Droite" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(1, 72, 20, 96));
//		//						persoSprite.Move(0, SPEED * ElapsedTime);
//		//						counter = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//		//		if (App.GetInput().IsKeyDown(sf::Key::A))
//		//		{
//		//			heros.attaquer(heros);
//		//			std::cout << "Attaque pvs : " << heros.getVie() << std::endl;
//		//		}	
//
//		//		if (App.GetInput().IsKeyDown(sf::Key::Z))
//		//		{
//		//			heros.soigner(heros);
//		//			std::cout << "Soin ! pvs : " << heros.getVie() << std::endl;
//		//		}
//		//		if(App.GetInput().IsKeyDown(sf::Key::E))
//		//		{
//		//			heros.setPhysique(heros.getPhysique() + 100);
//		//			heros.setMana(heros.getMana() - 100);
//		//			std::cout << "Epee Magique ! Atk : " << heros.getPhysique() << std::endl;
//		//			armeSprite.SetImage(imageEpee_magique);
//		//		}
//		//		if(App.GetInput().IsKeyDown(sf::Key::B))
//		//		{
//		//			heros.setMental(heros.getMental() + 75);
//		//			heros.setMana(heros.getMana() - 75);
//		//			std::cout << "Bouclier magique ! Def : " << heros.getMental() << std::endl;
//		//			defenseSprite.SetImage(imageBouclier_magique);
//		//			
//		//		}
//		//		if(App.GetInput().IsKeyDown(sf::Key::N))
//		//		{
//		//			std::cout << "Back to basics" << std::endl;
//		//			armeSprite.SetImage(imageEpee);
//		//			defenseSprite.SetImage(imageBouclier);
//		//			// Dissocier les deux trucs suivants :
//		//			//heros.setPhysique(heros.getPhysique() - 100);
//		//			//heros.setMental(heros.getMental() - 75);
//		//			heros.setPhysique(50);
//		//			heros.setMental(50);
//		//			heros.setMana(heros.getMana_max());
//		//		}
//
//		//	}
//		//}
//// ================================================================================================	
//
////		App.Clear(sf::Color::Black);
//	
//		switch(gameState)
//		{
//			case 1 :
//				// State : Title 
//				App.Clear(sf::Color::Blue);
//				App.Draw(titleText);
//				startColorState = !startColorState;
//				choice0.SetColor( ((startColorState) ? sf::Color::White : sf::Color::Red) );
//				App.Draw(choice0);
//	//			App.Display();
//			break;
//			case 2 :
//				App.Clear(sf::Color::Black);
//
//				App.Draw(choice1);
//				App.Draw(choice2);
//				App.Draw(choice3);
//				App.Draw(choice4);
//	//			App.Draw(stateText);
//	//			App.Display();
//
//			break;
//		
//			case 3 :
//				App.Clear(sf::Color::Green);
//
//				App.Draw(sf::Shape::Rectangle(10, 60, 790, 590, sf::Color(32,156,0, 0), 10, sf::Color(0,96,96,255)));
//				App.Draw(persoSprite);
//
//				// #################### Interface de jeu #################### 
//				// Top
//				nom_display.SetPosition(5, 5);
//				pvs.SetPosition(40, 5);
//				mana.SetPosition(760, 5);
//
//				App.Draw(sf::Shape::Rectangle(80, 5, 80+300, 25, sf::Color(64,0,0,255), 0, sf::Color(255,255,0)));
//			//	App.Draw(sf::Shape::Rectangle(80, 5, 80+300 * heros.getVie() / heros.getVie_max(), 25, sf::Color(128,0,0), 0, sf::Color(255,255,0))); //590 * ( 1.1 - heros.getVie() / 999.0)
//				App.Draw(sf::Shape::Rectangle(80+310, 5, 80+310+360, 25, sf::Color(0,0,64,255), 0, sf::Color(255,255,0)));
//			//	App.Draw(sf::Shape::Rectangle(80 + 310 + 360  - 360 * heros.getMana() / heros.getMana_max(), 5, 80+310+360, 25, sf::Color(0,0,128), 0, sf::Color(255,255,0))); //590 * ( 1.1 - heros.getVie() / 999.0)		
//				// Bottom left
//				armeSprite.SetPosition(15, 505);
//				defenseSprite.SetPosition(75, 525);
//					
//				App.Draw(sf::Shape::Circle(40, 530, 30, sf::Color(0,96,96,255), -3, sf::Color::Black));
//				App.Draw(sf::Shape::Circle(95, 560, 30, sf::Color(0,96,96,255), -3, sf::Color::Black));
//				App.Draw(pvs);
//				App.Draw(mana);
//				App.Draw(nom_display);
//				App.Draw(armeSprite);
//				App.Draw(defenseSprite);
////				App.Draw(stateText);
////				App.Display();
//			break;
//			default :
//				std::cout << "Display Error" << std::endl;
//			break;
//		}
//		App.Draw(stateText);
//		// Finally, display the rendered frame on screen
//		App.Display();
//    }
//
    return EXIT_SUCCESS;
} */
