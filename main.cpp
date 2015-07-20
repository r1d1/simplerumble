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

#define SPEED 10000
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/*void ThreadFunction(void* UserData)
{
	// Thread printing :
	for (int = 0; i < 10; ++i){ std::cout << "I'm the thread number 1" << std::endl; sf::Sleep(0.1f); }
}*/

int main(int argc, char** argv)
{
	srand(time(NULL));
	// Create a thread with our function
	/*sf::Thread Thread(&ThreadFunction);
	// Start it !
	Thread.Launch();
	
	// Main thread code :
	for(int i = 0 ; i < 10 ; i++){ std::cout << "I'm the main thread" << std::endl; sf::Sleep(0.1f); }
*/
	Attack sword("Sword", 3, 450);
	Attack axe("Axe", 10, 350);
	Agent npc1("", 100, "Wooden sword", 3, 500);
	Agent npc2("", 90, "Axe", 4, 500);
	//Création de 2 objets de type Personnage : npc1 et npc2
	int choice;

	for(int turn=0 ; turn < 15 ; turn++)
	{
		std::cout << "What to do ?" << std::endl << "# 0 : Attack" << std::endl << "# 1 : Defend" << std::endl << "# 2 : Surrender" << std::endl;
		std::cin >> choice;
		std::cout << "Turn " << turn << " you choose " << choice << std::endl;
		switch(choice)
		{
			case 0:
				std::cout << "Attacking !" << std::endl;
				npc2.attack(npc1);
			break;
			case 1:
				std::cout << "Defending !" << std::endl;
				npc2.defend();
			break;
			case 2:
				std::cout << "Surrender !" << std::endl;
				npc2.surrender();
			break;
			default:
				std::cout << "Wrong choice !" << std::endl;
				npc2.takeDamage(7);
			break;
		}
		npc1.attack(npc2);
		npc1.displayState();
		npc2.displayState();
		if(turn == 5){ npc1.changeAttack(&axe); }
		if(turn == 7){ npc2.changeAttack(&sword); }
		std::cout << "---------------------------" << std::endl;
	}


	return EXIT_SUCCESS;
}

/*int main()
{
	int choixmenu = -1,i=255;
	int compteur = 0;
	int stateOfZeGame = 0;
	
	// ================ Initialisation ! ================
	// State 0
	// Create main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SIMPLE RUMBLE !!!");
	
	App.Clear(sf::Color(0,0,0));
    App.Display();

	// ##### Scene #####
//	Minipers heros;
	sf::Image perso;
	sf::Image imageBackground;
	sf::Image imageHouse;

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
	stateOfZeGame = 1;
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
				switch(stateOfZeGame)
				{
					case 1 :
						//if (App.GetInput().IsKeyDown(sf::Key::Left)){ std::cout << "touche Gauche" << std::endl; }
						//if (App.GetInput().IsKeyDown(sf::Key::Right)){ std::cout << "touche Right" << std::endl; }
						//if (App.GetInput().IsKeyDown(sf::Key::Up)){ std::cout << "touche Up" << std::endl; }
						//if (App.GetInput().IsKeyDown(sf::Key::Down)){ std::cout << "touche Down" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ std::cout << "NextState" << std::endl; stateOfZeGame = 2; stateText.SetText("State 2"); }
						//stateText.SetText("State 1");
					break;
					case 2 :
						//boutonsSprite.SetSubRect(sf::IntRect(200, 0, 350, 60));
						if (App.GetInput().IsKeyDown(sf::Key::Return)){ std::cout << "touche ENTER ! VALIDATION" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Left)){ std::cout << "touche Gauche" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Right)){ std::cout << "touche Right" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Up)){ std::cout << "touche Up" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::Down)){ std::cout << "touche Down" << std::endl; }
						if (App.GetInput().IsKeyDown(sf::Key::A)){ std::cout << "NextState" << std::endl; stateOfZeGame = 3; stateText.SetText("State 3"); }
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
						if (App.GetInput().IsKeyDown(sf::Key::A)){ std::cout << "NextState" << std::endl; stateOfZeGame = 1; stateText.SetText("State 1"); }
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
//		//			if(compteur == 0)
//		//			{
//		//				std::cout << "touche Gauche" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(49, 104, 67, 104+23));
//		//				persoSprite.Move(-SPEED * ElapsedTime, 0);
//
//		//				compteur = 1;
//		//			}
//		//			else
//		//			{
//		//				if(compteur == 1)
//		//				{
//		//					std::cout << "touche Gauche" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(26, 103, 44, 103+24));
//		//					persoSprite.Move(-SPEED * ElapsedTime, 0);
//		//					compteur = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(compteur == 2)
//		//					{
//		//						std::cout << "touche Gauche" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(1, 104, 20, 104+23));
//		//						persoSprite.Move(-SPEED * ElapsedTime, 0);
//		//						compteur = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//		//		if (App.GetInput().IsKeyDown(sf::Key::Right))
//		//		{
//		//			if(compteur == 0)
//		//			{
//		//				std::cout << "touche Droite 1" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(54, 39, 71, 64));
//		//				persoSprite.Move(SPEED * ElapsedTime, 0);
//
//		//				compteur = 1;
//		//			}
//		//			else
//		//			{
//		//				if(compteur == 1)
//		//				{
//		//					std::cout << "touche Droite 2" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(30, 39, 49, 64));
//		//					persoSprite.Move(SPEED * ElapsedTime, 0);
//		//					compteur = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(compteur == 2)
//		//					{
//		//						std::cout << "touche Droite 3" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(5, 39, 23, 64));
//		//						persoSprite.Move(SPEED * ElapsedTime, 0);
//		//						compteur = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//
//		//		if (App.GetInput().IsKeyDown(sf::Key::Up))
//		//		{
//		//			if(compteur == 0)
//		//			{
//		//				std::cout << "touche Droite" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(49, 8, 67, 32));
//		//				persoSprite.Move(0, -SPEED * ElapsedTime);
//
//		//				compteur = 1;
//		//			}
//		//			else
//		//			{
//		//				if(compteur == 1)
//		//				{
//		//					std::cout << "touche Droite" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(26, 7, 44, 32));
//		//					persoSprite.Move(0, -SPEED * ElapsedTime);
//		//					compteur = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(compteur == 2)
//		//					{
//		//						std::cout << "touche Droite" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(1, 8, 20, 32));
//		//						persoSprite.Move(0, -SPEED * ElapsedTime);
//		//						compteur = 0;
//		//					}
//		//				}
//		//			}
//		//		}
//		//		
//		//		
//		//		if (App.GetInput().IsKeyDown(sf::Key::Down))
//		//		{
//		//			if(compteur == 0)
//		//			{
//		//				std::cout << "touche Droite" << std::endl;
//		//				// sf::IntRect(18, 8, 18+48, 8+70)
//		//				persoSprite.SetSubRect(sf::IntRect(49, 72, 67, 96));
//		//				persoSprite.Move(0, SPEED * ElapsedTime);
//
//		//				compteur = 1;
//		//			}
//		//			else
//		//			{
//		//				if(compteur == 1)
//		//				{
//		//					std::cout << "touche Droite" << std::endl;
//		//					persoSprite.SetSubRect(sf::IntRect(26, 71, 44, 96));
//		//					persoSprite.Move(0, SPEED * ElapsedTime);
//		//					compteur = 2;						
//		//				}
//		//				else
//		//				{
//		//					if(compteur == 2)
//		//					{
//		//						std::cout << "touche Droite" << std::endl;
//		//						persoSprite.SetSubRect(sf::IntRect(1, 72, 20, 96));
//		//						persoSprite.Move(0, SPEED * ElapsedTime);
//		//						compteur = 0;
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
//		switch(stateOfZeGame)
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
