/*********************************************************************************************************
;**********								13B Game Implementation									**********		 
;*********************************************************************************************************
;
;PACKAGE NAME:	TODO
;
;FUNCTION:
;
;	This unit contains the source code designed to...TODO
;
;PUBLIC DECLARATIONS:
;
;	PUBLIC SYMBOLS
;	--------------
;	TODO
;
;	PUBLIC SUB-PROGRAMS
;	------------------
;	TODO
;
;PRIVATE DECLARATIONS:
;
;	PRIVATE SYMBOLS
;	---------------
;	TODO
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	TODO
;
*/

#include <iostream>		// For testing, delete later
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Vec2.h"
#include "EntityManager.h"


/**********************************************************************************************************
;**********										Game::Game										 **********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Game::Game(const std::string& config)
{
	init(config);
}


/*********************************************************************************************************
;**********										Game::init										**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::init(const std::string& path)
{
	std::ifstream	fin(path);
	std::string		configType, fontFile; 
	int				winWidth, winHeight, frameLimit, fontSize, rValueFont, gValueFont, bValueFont;
	bool			fullScreen; 
	
	while (fin >> configType)
	{
		if (configType == "Window")
		{
			fin >> winWidth		//	window width
				>> winHeight	//	window height
				>> frameLimit	//	frame rate limit
				>> fullScreen;	//	videomode 1 = full screen, 0 = window

			m_window.create(sf::VideoMode(winWidth, winHeight, fullScreen), "Psuedo-GeoWars");
			m_window.setFramerateLimit(frameLimit);
		}
		else if (configType == "Font")
		{
			fin >> fontFile		//	font config file
				>> fontSize		//	font size
				>> rValueFont	//	font color R-value
				>> gValueFont	//	font color G-value
				>> bValueFont;	//	font color B-value

			if (!m_font.loadFromFile(fontFile))
			{
				std::cerr << "Could not load font, exiting application" << std::endl;
			}
			m_text.setFont(m_font);
			m_text.setCharacterSize(fontSize);
			m_text.setFillColor(sf::Color(rValueFont, gValueFont, bValueFont));

			m_pauseText.setFont(m_font);
			m_pauseText.setCharacterSize(fontSize);
			m_pauseText.setFillColor(sf::Color(rValueFont, gValueFont, bValueFont));
			m_pauseText.setString("PAUSED");
			m_pauseText.setPosition((m_window.getSize().x / 2) - (m_pauseText.getLocalBounds().width / 2),
									(m_window.getSize().y / 2) - (m_pauseText.getLocalBounds().height));
		}
		else if (configType == "Player")
		{
			fin >> m_playerConfig.SR	//	shape radius
				>> m_playerConfig.CR	//	collision radius
				>> m_playerConfig.S		//	speed
				>> m_playerConfig.FR	//	fill color R-value
				>> m_playerConfig.FG	//	fill color G-value
				>> m_playerConfig.FB	//	fill color B-value
				>> m_playerConfig.OR	//	outline color R-value
				>> m_playerConfig.OG	//	outline color G-value
				>> m_playerConfig.OB	//	outline color B-value
				>> m_playerConfig.OT	//	outline color thickness
				>> m_playerConfig.V;	//	shape vertices	
		}
		else if (configType == "Enemy")
		{
			fin >> m_enemyConfig.SR		//	shape redius
				>> m_enemyConfig.CR		//	collision radius
				>> m_enemyConfig.SMIN	//	min speed
				>> m_enemyConfig.SMAX	//	max speed
				>> m_enemyConfig.OR		//	outline color R-value
				>> m_enemyConfig.OG		//	outline color G-value
				>> m_enemyConfig.OB		//	outline color B-value
				>> m_enemyConfig.OT		//	outline color thickness
				>> m_enemyConfig.VMIN	//	min vertices
				>> m_enemyConfig.VMAX	//	max vertices
				>> m_enemyConfig.L		//	small enemy lifespan
				>> m_enemyConfig.SI;	//	spawn interval
		}
		else if (configType == "Bullet")
		{
			fin >> m_bulletConfig.SR	//	shape radius
				>> m_bulletConfig.CR	//	collision radius
				>> m_bulletConfig.S		//	speed
				>> m_bulletConfig.FR	//	fill color R-value
				>> m_bulletConfig.FG	//	fill color G-value
				>> m_bulletConfig.FB	//	fill color B-value
				>> m_bulletConfig.OR	//	outline color R-value
				>> m_bulletConfig.OG	//	outline color G-value
				>> m_bulletConfig.OB	//	outline color B-value
				>> m_bulletConfig.OT	//	outline color thickness
				>> m_bulletConfig.V		//	shape vertices
				>> m_bulletConfig.L;	//	lifespan
		}
	}

	spawnPlayer();

	m_running = true;	// Not sure if this is best location, 
}


/*********************************************************************************************************
;**********										Game::run										**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::run()
{
	// TODO: Add pause functionality here, some systems should function
	//		 while paused (rendering), some systems shouldn't (movement / input)
	while (m_running)
	{
		m_entityManager.update();

		// This is not a definitive list of functions that should be called (or not called) 
		// when paused. However, this seems mostly correct minus sUserInput, can't unpause 
		// game without user input
		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sLifespan();
		}

		sUserInput();
		sRender();

		// Increment current frame, may need to be moved when gameplay is paused
		m_currentFrame++;
	}
}


/*********************************************************************************************************
;**********									Game::spawnPlayer									**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::spawnPlayer()
{
	float mx, my;

	// Entities are created by calling EntityManager.addEntity(tag)
	std::shared_ptr<Entity> entity = m_entityManager.addEntity("player");

	// Give Entity a transform so it spawns in center of window with velocity (1,1) and angle 0
	mx = m_window.getSize().x / 2.0f;
	my = m_window.getSize().y / 2.0f;
	entity->cTransform = std::make_shared<CTransform>(	Vec2(mx, my), 
														Vec2(0.0f, 0.0f), 
														0.0f);

	// Add shape component for player Entity
	entity->cShape = std::make_shared<CShape>(	m_playerConfig.SR, 
												m_playerConfig.V, 
												sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), 
												sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), 
												m_playerConfig.OT);
	
	// Add an input component to the player
	entity->cInput = std::make_shared<CInput>();

	// Add score component to player Entity
	entity->cScore = std::make_shared<CScore>(0);

	// Add collision component to player Entity
	entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
	
	// Since we want this Entity to be our player, set our Game's player variables to be thie Entity,
	// this goes slightly against the EntityManager paradigm, but we use the player so much it's worth it.
	m_player = entity;
}


/*********************************************************************************************************
;**********									Game::spawnEnemy									**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::spawnEnemy()
{
	std::shared_ptr<Entity> entity = m_entityManager.addEntity("enemy");

	// Give Entity a transform to spawn in random location
	float ex = rand() % m_window.getSize().x	+ m_enemyConfig.SR;
	float ey = rand() % m_window.getSize().y	- m_enemyConfig.SR;
	float sx = rand() % (int)m_enemyConfig.SMAX - m_enemyConfig.SMIN;
	float sy = rand() % (int)m_enemyConfig.SMAX - m_enemyConfig.SMIN;
	int vert = rand() % m_enemyConfig.VMAX		+ m_enemyConfig.VMIN;

	// Add components to enemy Entity
	entity->cTransform	= std::make_shared<CTransform>(Vec2(ex, ey), Vec2(sx, sy), 0.0f);
	entity->cShape		= std::make_shared<CShape>(	m_enemyConfig.SR, 
													vert,
													sf::Color(	rand() % m_enemyConfig.OR, 
																rand() % m_enemyConfig.OG,
																rand() % m_enemyConfig.OB),
													sf::Color(255, 255, 255), 
													m_enemyConfig.OT);
	entity->cCollision	= std::make_shared<CCollision>(m_enemyConfig.CR);

	// Record when the most recent enemy was spawned to use for determining when to spawn new enemy
	m_lastEnemySpawnTime = m_currentFrame;
}


/*********************************************************************************************************
;**********								Game::spawnSmallEnemies									**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	// TODO: Spawn small enemies at location of input enemy e

	// When creating the smaller enemy, have to read values of original enemy
	// - Spawn number of small enemies equal to number of vertices of original enemy
	// - Set each small enemy to the same color as the original, but half the size
	// - Small enemies are worth double points of the original enemy
	int		numSpawn	= e->cShape->circle.getPointCount();
	float	theta		= 6.28f / numSpawn;

	for (int i = 0; i < numSpawn; i++)
	{
		std::shared_ptr<Entity> entity = m_entityManager.addEntity("small enemy");

		entity->cTransform = std::make_shared<CTransform>(Vec2(e->cTransform->pos.x, e->cTransform->pos.y), 
														  Vec2((2*cosf(theta*i)), (2*sinf(theta*i))),
														  0.0f);

		entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR / 2,
												  numSpawn, 
												  e->cShape->circle.getFillColor(), 
												  e->cShape->circle.getOutlineColor(), 
												  m_enemyConfig.OT);

		entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR / 2);
		entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L, m_enemyConfig.L);
	}
}


/*********************************************************************************************************
;**********									Game::spawnBullet									**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	// Add bullet object to Entity vector, then add componenets
	std::shared_ptr<Entity> bullet = m_entityManager.addEntity("bullet");

	// Add required components for bullet Entity
	bullet->cTransform	= std::make_shared<CTransform>(m_player->cTransform->pos, target, 0);

	bullet->cShape		= std::make_shared<CShape>(	m_bulletConfig.SR, 
													m_bulletConfig.V, 
													sf::Color(	m_bulletConfig.FR, 
																m_bulletConfig.FG, 
																m_bulletConfig.FB),
													sf::Color(	m_bulletConfig.OR,
																m_bulletConfig.OG,
																m_bulletConfig.OB),
																m_bulletConfig.OT);

	bullet->cLifespan	= std::make_shared<CLifespan>(m_bulletConfig.L, m_bulletConfig.L);

	bullet->cCollision  = std::make_shared<CCollision>(m_bulletConfig.CR);

	// Convert bullet velocity to unit vector
	bullet->cTransform->velocity.normalize(m_player->cTransform->pos);

	// Multiply bullet velocity vector by speed factor in config.txt
	bullet->cTransform->velocity = bullet->cTransform->velocity * m_bulletConfig.S;	
}


/*********************************************************************************************************
;**********								Game::spawnSpecialWeapon								**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2& target)
{
	int numVertices			= 20;
	int initialRadius		= 2;
	int collisionRadius		= 10;
	int outlineThickness	= 1;
	int outline				= 255;
	int fill				= 0;
	int lifespan			= 100;
	int speed				= 20;

	std::shared_ptr<Entity> specialWeapon = m_entityManager.addEntity("special weapon");

	specialWeapon->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, target, 0);

	specialWeapon->cShape = std::make_shared<CShape>(	initialRadius,
														numVertices,
														sf::Color(	fill,
																	fill,
																	fill),
														sf::Color(	outline,
																	outline,
																	outline),
																	outlineThickness);

	specialWeapon->cLifespan = std::make_shared<CLifespan>(lifespan, lifespan);

	specialWeapon->cCollision = std::make_shared<CCollision>(collisionRadius);

	// Convert special weapon velocity to unit vector
	specialWeapon->cTransform->velocity.normalize(m_player->cTransform->pos);

	// Multiple special weapon velocity vector by speed factor
	specialWeapon->cTransform->velocity = specialWeapon->cTransform->velocity * speed;
}


/*********************************************************************************************************
;**********								Game::activateSpecialWeapon								**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::activateSpecialWeapon(std::shared_ptr<Entity> e, int radius)
{
	if (e->cShape->circle.getRadius() < radius)
	{
		e->cShape->circle.setRadius(e->cShape->circle.getRadius() + 1);
	}
}


/*********************************************************************************************************
;**********									Game::sMovement										**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::sMovement()
{
	// Set player velocity to {0,0} at the beginning of every frame so player halts when keys released
	m_player->cTransform->velocity = { 0,0 };

	// Implement player movement
	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -5;
	}
	else if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = 5;
	}

	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -5;
	}
	else if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 5;
	}

	// Update position for all Entities based on cTransform
	for (std::shared_ptr<Entity> e : m_entityManager.getEntities())
	{
		// Reverse velocity direction for enemies that hit window edges
		if (e->tag() == "enemy")
		{
			if ((e->cShape->circle.getPosition().x - e->cShape->circle.getRadius()) < 0 ||
				(e->cShape->circle.getPosition().x + e->cShape->circle.getRadius()) > m_window.getSize().x)
			{
				e->cTransform->velocity.x *= -1;
			}

			if ((e->cShape->circle.getPosition().y - e->cShape->circle.getRadius()) < 0 ||
				(e->cShape->circle.getPosition().y + e->cShape->circle.getRadius()) > m_window.getSize().y)
			{
				e->cTransform->velocity.y *= -1;
			}
		}

		e->cTransform->pos = e->cTransform->pos + e->cTransform->velocity;
	}
}


/*********************************************************************************************************
;**********									Game::sLifespan										**********		
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::sLifespan()
{
	int			finalRadius = 80;
	int32_t		alphaRatio;
	int32_t		colorToInt;
	int32_t		colorMask = 0xFFFFFF00;
	int32_t		alphaMask = 0x000000FF;

	for (std::shared_ptr<Entity> e : m_entityManager.getEntities())
	{
		if (e->cLifespan)
		{
			// Update remaining lifespan for Entity
			e->cLifespan->remaining--;

			// If Entity has remaining lifespan update alpha ratio, otherwise destroy Entity
			if (e->cLifespan->remaining > 0)
			{
				// Calculate new alpha ratio for Entities with lifespans
				alphaRatio = 255 * ((float)e->cLifespan->remaining / (float)e->cLifespan->total);		// Replace 255 with variable from config.txt

				// Decrease alpha ratio as Entity's lifespan reaches end
				if (e->tag() == "bullet")
				{
					e->cShape->circle.setFillColor(sf::Color(	m_bulletConfig.FR, 
																m_bulletConfig.FG, 
																m_bulletConfig.FB, 
																alphaRatio));

					e->cShape->circle.setOutlineColor(sf::Color(m_bulletConfig.OR, 
																m_bulletConfig.OG, 
																m_bulletConfig.OB, 
																alphaRatio));
				}
				else if (e->tag() == "small enemy")
				{
					colorToInt = e->cShape->circle.getFillColor().toInteger();

					e->cShape->circle.setFillColor(sf::Color((colorToInt & colorMask) | (alphaRatio & alphaMask)));

					e->cShape->circle.setOutlineColor(sf::Color(m_enemyConfig.OR, 
																m_enemyConfig.OG, 
																m_enemyConfig.OB, 
																alphaRatio));
				}
				else if (e->tag() == "special weapon")
				{
					// Halt special weapon motion when 3/4 life remaining
					if (e->cLifespan->remaining <= e->cLifespan->total * 0.75)
					{
						e->cTransform->velocity.x = 0;
						e->cTransform->velocity.y = 0;

						activateSpecialWeapon(e, finalRadius);
					}
				}
			}
			else
			{
				e->destroy();
			}
		}
	}
}


/*********************************************************************************************************
;**********										Game::sCollision								**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::sCollision()
{
	float toVector;

	// Detect collisions between bullets and enemies
	for (std::shared_ptr<Entity> b : m_entityManager.getEntities("bullet"))
	{
		for (std::shared_ptr<Entity> e : m_entityManager.getEntities("enemy"))
		{
			// Detect collisions between bullet and enemy Entities
			if (b->cTransform->pos.length(e->cTransform->pos) <= (m_bulletConfig.CR + m_enemyConfig.CR))
			{
				b->destroy();
				e->destroy();
				
				spawnSmallEnemies(e);

				// Add ((100 points)*(e's #vertices))/enemy) to player score
				m_player->cScore->score += 100 * e->cShape->circle.getPointCount();
			}
		}

		for (std::shared_ptr<Entity> e : m_entityManager.getEntities("small enemy"))
		{
			// Detect collisions between bullet and small enemy Entities
			if (b->cTransform->pos.length(e->cTransform->pos) <= (m_bulletConfig.CR + (m_enemyConfig.CR / 2)))
			{
				b->destroy();
				e->destroy();

				// Add ((200 points)*(e's #vertices))/enemy) to player score
				m_player->cScore->score += 200 * e->cShape->circle.getPointCount();
			}
		}
	}

	// Execute special weapon logic for nearby enemies
	for (std::shared_ptr<Entity> w : m_entityManager.getEntities("special weapon"))
	{
		for (std::shared_ptr<Entity> e : m_entityManager.getEntities("enemy"))
		{
			toVector = w->cTransform->pos.length(e->cTransform->pos);

			if (toVector <= w->cShape->circle.getRadius() + m_enemyConfig.CR)
			{
				e->destroy();
				spawnSmallEnemies(e);
			}
		}
	}

	// Execute special weapon logic for nearby enemies
	for (std::shared_ptr<Entity> w : m_entityManager.getEntities("special weapon"))
	{
		for (std::shared_ptr<Entity> e : m_entityManager.getEntities("small enemy"))
		{
			toVector = w->cTransform->pos.length(e->cTransform->pos);

			if (toVector <= w->cShape->circle.getRadius() + e->cShape->circle.getRadius())
			{
				e->destroy();
			}
		}
	}

	for (std::shared_ptr<Entity> e : m_entityManager.getEntities("enemy"))
	{
		// Detect collisions between player and enemy Entities
		if (m_player->isActive() && (m_player->cTransform->pos.length(e->cTransform->pos) <= (m_playerConfig.CR + m_enemyConfig.CR)))
		{
			m_player->destroy();
			e->destroy();

			spawnSmallEnemies(e);
		}
	}

	for (std::shared_ptr<Entity> e : m_entityManager.getEntities("small enemy"))
	{
		// Detect collisions between player and enemy Entities
		if (m_player->isActive() && (m_player->cTransform->pos.length(e->cTransform->pos) <= (m_playerConfig.CR + e->cShape->circle.getRadius())))
		{
			m_player->destroy();
			e->destroy();
		}
	}
}


/*********************************************************************************************************
;**********									Game::sEnemySpawner									**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::sEnemySpawner()
{
	if ((m_currentFrame - m_lastEnemySpawnTime) > m_enemyConfig.SI)
	{
		spawnEnemy();
	}
}

/*********************************************************************************************************
;**********										Game::sRender									**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::sRender()
{
	// TODO: Change code below to draw all of the Entities
	//		 sample drawing of the player Entity that we have created
	m_window.clear();

	// Code below was added during lecture and will need to be included to draw all Entities
	for (auto& e : m_entityManager.getEntities())
	{
		// Set position of the shape based on the Entity's transform->pos
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		// Set the rotation of the shape based on the Entity's transform->angle
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(m_player->cTransform->angle);

		// Draw the Entity's sf::CircleShape
		m_window.draw(e->cShape->circle);
	}

	if (m_paused)
	{
		m_window.draw(m_pauseText);
	}

	m_text.setString("SCORE: " + std::to_string(m_player->cScore->score));
	m_window.draw(m_text);
	m_window.display();
}


/*********************************************************************************************************
;**********										Game::sUserInput								**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Game::sUserInput()
{
	static int	coolDown		= 100;
	static bool specialActive	= false;

	if (specialActive)
	{
		coolDown--;

		if (coolDown <= 0)
		{
			coolDown	  = 6000;
			specialActive = false;
		}
	} 

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// Trigger event when window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		// Trigger event when key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			case sf::Keyboard::Space:
				if (!m_player->isActive())
					spawnPlayer();
				break;
			case sf::Keyboard::Enter:
				if (!m_paused)
					m_paused = true;
				else
					m_paused = false;
				break;
			default: break;
			}
		}

		// Trigger event when key is released
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
			default: break;
			}
		}
		
		if (event.type == sf::Event::MouseButtonPressed && m_player->isActive())
		{
			if (event.mouseButton.button == sf::Mouse::Left && m_player->isActive())
			{
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right && specialActive != true)
			{
				spawnSpecialWeapon(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
				specialActive = true;
			}
		}
	}
}