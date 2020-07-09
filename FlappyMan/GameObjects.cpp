
//----=AbstractObject=-------------------------------

AbstractObject::AbstractObject () :

	x_ (0),
	y_ (0),

	vx_ (0),
	vy_ (0),

	width_  (0),
	height_ (0),

	manager_ (nullptr)

{}

//---------------------------------------------------

void AbstractObject::draw ()

{

}

//---------------------------------------------------

void AbstractObject::move ()

{

	setPosition (x_ + vx_, y_ + vy_);

}

//---------------------------------------------------

void AbstractObject::setPosition (double x, double y)

{


	x_ = x;
	y_ = y;

}

//---------------------------------------------------

sf::Vector2f AbstractObject::getPosition ()

{

	return sf::Vector2f (x_, y_);

}

//---------------------------------------------------

void AbstractObject::setSize (double width, double height)

{

	width_  = width;
	height_ = height;

}

//---------------------------------------------------

sf::Vector2f AbstractObject::getSize ()

{

	return sf::Vector2f (width_, height_);

}

//---------------------------------------------------

void AbstractObject::setDirection (double vx, double vy)

{

	vx_ = vx;
	vy_ = vy;

}

//---------------------------------------------------

sf::Vector2f AbstractObject::getDirection ()

{

	return sf::Vector2f (vx_, vy_);

}

//---------------------------------------------------

void AbstractObject::setManager (ObjectManager * manager)

{

	manager_ = manager;

}

//---------------------------------------------------

ObjectManager * AbstractObject::getManager ()

{

	return manager_;

}

//---------------------------------------------------

bool AbstractObject::onKeyPressed ()

{

	return false;

}

//---------------------------------------------------

bool AbstractObject::onMouseClick ()

{

	return false;

}

//----=RectObject=-----------------------------------

RectObject::RectObject () :

	AbstractObject (),

	rect_ ()

{

	setColor     (sf::Color::White);

	setPosition  (0, 0);
	setSize      (10, 10);
	setDirection (0, 0);

}

//---------------------------------------------------

void RectObject::draw ()

{

	manager_ -> getWindow () -> draw (rect_);

}

//---------------------------------------------------

void RectObject::setColor (sf::Color color)

{

	color_ = color;

	rect_.setFillColor (color_);

}

//---------------------------------------------------

sf::Color RectObject::getColor ()

{

	return color_;

}

//---------------------------------------------------

void RectObject::setPosition (double x, double y)

{

	AbstractObject::setPosition (x, y);

	rect_.setPosition (x_, y_);

}

//---------------------------------------------------

void RectObject::setSize (double width, double height)

{

	AbstractObject::setSize (width, height);

	rect_.setSize (sf::Vector2f (width_, height_));

}

//----=Wall=-----------------------------------------

Wall::Wall () :

	RectObject (),

	hole_y_ (0),

	hole_height_ (0)

{

	reset ();

}

//---------------------------------------------------

void Wall::draw ()

{

	sf::RectangleShape rect;

	rect.setPosition (x_, 0);
	rect.setSize (sf::Vector2f (width_, wHeight));
	rect.setFillColor (color_);

	manager_ -> getWindow () -> draw (rect);

	rect.setPosition (x_, hole_y_);
	rect.setSize (sf::Vector2f (width_, hole_height_));
	rect.setFillColor (WallBackground);

	manager_ -> getWindow () -> draw (rect);

}

//---------------------------------------------------

void Wall::reset ()

{

	hole_height_ = eu::rnd (HoleMinHeight, HoleMaxHeight);

	hole_y_ = eu::rnd (wHeight / 2 - hole_height_ / 2 - HoleRange, wHeight / 2 - hole_height_ / 2 + HoleRange);

	setPosition (wWidth, 0);

	setSize (eu::rnd (WallMinWidth, WallMaxWidth), height_);

	setColor (WallColor);

}

//---------------------------------------------------

void Wall::move ()

{

	AbstractObject::move ();

	if (x_ < -width_) reset ();

}

//----=player=---------------------------------------

Player::Player () :

	spacePressed_ (false)

{

	setPosition (100, wHeight / 2 - 30);
	setSize (50, 30);
	setColor (PlayerColor);

}

//---------------------------------------------------

void Player::move ()

{

	if (vy_ < MaxPlayerSpeed) vy_ += PlayerFallVelocity;

	if (y_ + vy_ < wHeight - height_ && y_ + vy_ >= 0) setPosition (x_, y_ + vy_);

	setPosition (x_ + vx_, y_);

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Space))

	{
	
		onSpace ();

		spacePressed_ = true;
	
	}

	else spacePressed_ = false;

}

//---------------------------------------------------

bool Player::onMouseClick ()

{

	jump ();

	return true;

}

//---------------------------------------------------

bool Player::onSpace ()

{

	if (spacePressed_) return false;

	jump ();

	return true;

}

//---------------------------------------------------

void Player::jump ()

{

	if (vy_ > -MaxPlayerSpeed) vy_ = -PlayerJumpVelocity;

}

//----=ObjectManager=--------------------------------

ObjectManager::ObjectManager ()

{

	window_ = nullptr;

	for (size_t i = 0; i < MaxObjects; i++)

		objects_[i] = nullptr;

}

//---------------------------------------------------

ObjectManager::~ObjectManager ()

{

	for (size_t i = 0; i < MaxObjects; i++)	

		removeObject (objects_[i]);

}

//---------------------------------------------------

void ObjectManager::setWindow (sf::RenderWindow * window)

{

	window_ = window;

}

//---------------------------------------------------

sf::RenderWindow * ObjectManager::getWindow ()

{

	return window_;

}

//---------------------------------------------------

void ObjectManager::setGameManager (GameManager * manager)

{

	gamemanager_ = manager;

}

//---------------------------------------------------

GameManager * ObjectManager::getGameManager ()

{

	return gamemanager_;

}

//---------------------------------------------------

size_t ObjectManager::addObject (AbstractObject * object)

{

	for (size_t i = 0; i < MaxObjects; i++)

	{
	
		if (objects_[i]) continue;

		objects_[i] = object;

		object -> setManager (this);

		return i;

	}

	return -1;

}

//---------------------------------------------------

size_t ObjectManager::removeObject (AbstractObject * object)

{

	for (size_t i = 0; i < MaxObjects; i++)

	{
	
		if (!objects_[i]) continue;

		if (objects_[i] == object)

		{

			objects_[i] = nullptr;

			delete (objects_[i]);

			return i;

		}

	}

	return -1;

}

//---------------------------------------------------

void ObjectManager::drawObjects ()

{

	for (size_t i = 0; i < MaxObjects; i++)

	{

		if (!objects_[i]) continue; 
		
		objects_[i] -> draw ();

	}

}

//---------------------------------------------------

void ObjectManager::moveObjects ()

{

	for (size_t i = 0; i < MaxObjects; i++)

	{

		if (!objects_[i]) continue; 
		
		objects_[i] -> move ();

	}

}

//---------------------------------------------------

bool ObjectManager::processEvents (const sf::Event & event)

{

	for (size_t i = 0; i < MaxObjects; i++)

	{

		if (!objects_[i]) continue;

		if (event.type == sf::Event::KeyPressed)         if (objects_[i] -> onKeyPressed ()) return true;

		if (event.type == sf::Event::MouseButtonPressed) if (objects_[i] -> onMouseClick ()) return true;

	}

	return false;

}

//---------------------------------------------------