#pragma once

#include "Config.h"

//---------------------------------------------------

class GameManager;
class ObjectManager;

//----=AbstractObject=-------------------------------

class AbstractObject 

{

public :

	AbstractObject ();

	virtual void draw ();

	virtual void move ();

	virtual void         setPosition (double x, double y);
	virtual sf::Vector2f getPosition ();

	virtual void         setSize (double width, double height);
	virtual sf::Vector2f getSize ();

	virtual void         setDirection (double vx, double vy);
	virtual sf::Vector2f getDirection ();

	virtual void            setManager (ObjectManager * manager);
    virtual ObjectManager * getManager ();

	virtual bool onKeyPressed ();

	virtual bool onMouseClick ();

protected :

	double x_;
	double y_;

	double vx_;
	double vy_;

	double width_;
	double height_;

	ObjectManager * manager_;

};

class RectObject : public AbstractObject

{

public :

	RectObject ();

	virtual void draw ();

	virtual void setColor (sf::Color color);
	sf::Color    getColor ();

	virtual void setPosition (double x, double y);

	virtual void setSize (double width, double height);

protected :

	sf::RectangleShape rect_;

	sf::Color color_;

};

//----=Wall=-----------------------------------------

class Wall : public RectObject

{

public :

	Wall ();

	virtual void draw ();

	virtual void move ();

	virtual void reset ();

protected :

	double hole_y_;

	double hole_height_;

};

//----=Player=---------------------------------------

class Player : public RectObject

{

public :

	Player ();

	void move ();

	bool onMouseClick ();

protected :

	bool spacePressed_;

	bool onSpace ();

	void jump ();

};

//----=ObjectManager=---------------------------------

class ObjectManager 

{

public :

	ObjectManager ();

	~ObjectManager ();

	size_t addObject    (AbstractObject * object);

	size_t removeObject (AbstractObject * object);

	void drawObjects ();

	void moveObjects ();

	void               setWindow (sf::RenderWindow * window);
	sf::RenderWindow * getWindow ();

	void          setGameManager (GameManager * manager);
	GameManager * getGameManager ();

	bool processEvents (const sf::Event & event);

private :

	AbstractObject * objects_ [MaxObjects];

	sf::RenderWindow * window_;

	GameManager * gamemanager_;

};

//---------------------------------------------------

#include "GameObjects.cpp"