GameManager::GameManager (sf::RenderWindow * window) :

	window_ (window),

	manager_ (),

	fontmanager_ (Fonts, "Resources\\Fonts\\")

{

	manager_.setWindow (window_);
	
	for (size_t i = 0; i < WallsCount; i++)

	{
	
		Wall * wall = new Wall;

		wall -> setPosition ((double) (wWidth / WallsCount * i + wWidth), 0);
		wall -> setDirection (-WallsSpeed, 0);

		manager_.addObject (wall);

	}

	manager_.addObject (new Player);

	window_ -> setFramerateLimit (wFpsLimit);

}

//---------------------------------------------------

void GameManager::run ()

{

	window_ -> clear (Background);

	manager_.moveObjects ();
	manager_.drawObjects ();

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::LControl)) drawFpsLimit ();

}

//---------------------------------------------------

bool GameManager::pollEvents (const sf::Event & event)

{

	if          (processEvents (event)) return true;

	if (manager_.processEvents (event)) return true;

	return false;

}

//---------------------------------------------------

bool GameManager::processEvents (const sf::Event & event)

{

	if (event.type == sf::Event::KeyPressed)      if (onKeyPressed                            ()) return true;

	if (event.type == sf::Event::MouseWheelMoved) if (onMouseWheelMoved (event.mouseWheel.delta)) return true;

	return false;

}

//---------------------------------------------------

bool GameManager::onKeyPressed ()

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape)) return Close ();

	return false;

}

//---------------------------------------------------

bool GameManager::onMouseWheelMoved (int delta)

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::LControl))

	{

		wFpsLimit += delta;

		window_ -> setFramerateLimit (wFpsLimit);

		return true;

	}

	return false;

}

//---------------------------------------------------

bool GameManager::Close ()

{

	window_ -> close ();

	return true;

}

//---------------------------------------------------

void GameManager::drawFpsLimit ()

{

	sf::Font font = fontmanager_.getFont (FontConsole);

	sf::Text text;

	text.setFont (font);

	text.setFillColor (sf::Color::White);
	text.setPosition (2, -25);
	text.setCharacterSize (50);
	text.setString (std::to_string (wFpsLimit));

	window_ -> draw (text);

}