#pragma once

//---------------------------------------------------

#include <SFML\Graphics.hpp>

//---------------------------------------------------

class GameManager

{

public :

	GameManager (sf::RenderWindow * window);

	void run ();

	bool pollEvents (const sf::Event & event);

	bool processEvents (const sf::Event & event);

	bool onKeyPressed ();

	bool onMouseWheelMoved (int delta);

	bool Close ();

	void drawFpsLimit ();

private :

	ObjectManager manager_;

	FontManager fontmanager_;

	sf::RenderWindow * window_;

};

//---------------------------------------------------

#include "GameManager.cpp"