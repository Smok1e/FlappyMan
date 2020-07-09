#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------

#define RANDOMCOLOR sf::Color (eu::rnd (0, 255), eu::rnd (0, 255), eu::rnd (0, 255))

//---------------------------------------------------

#include <SFML/Graphics.hpp>

#include "C:\Lib\ExtraUtilits\ExtraUtilits.h"
#include "FontManager.h"
#include "GameObjects.h"
#include "GameManager.h"

//---------------------------------------------------

int main ()

{
	
	sf::RenderWindow window (sf::VideoMode (wWidth, wHeight), wTitle);

	GameManager manager (&window);

	while (window.isOpen ())

	{

		sf::Event event;

		while (window.pollEvent (event))

			manager.pollEvents (event);

		manager.run ();

		window.display ();

	}

}