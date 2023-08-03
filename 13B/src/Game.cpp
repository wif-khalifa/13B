#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Vec2.h"
#include "EntityManager.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	// TODO: Read in config file here using pre-made PlayerConfig,
	//		 EnemyConfig, and BulletConfig variables
	 
	//std::ifstream fin(path);	// Prof example, still need to do stuff with fin
	
	// If entry is for player, since we have player struct PlayerConfig declared do this
	// fin >> m_playerConfig.SR >> m_playerConfig.CR >> ...

	// Set up default windown parameters, remember that last Window variable from 
	// config file determines fullscreen vs window
	m_window.create(sf::VideoMode(1280, 720), "Psuedo-GeoWars");
	m_window.setFramerateLimit(60);

	spawnPlayer();

	m_running = true;	// Not sure if this is best location, 
}

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
			sUserInput();
		}

		sRender();

		// Increment current frame, may need to be moved when gameplay is paused
		m_currentFrame++;
	}
}

void Game::setPaused(bool paused)
{
	// TODO
}

// Respawn player in middle of screen
void Game::spawnPlayer()
{
	float mx, my;

	// TODO: Finish adding all Player properties with values from config file, in code below,
	//		 some values are hard-coded, these values should be replaced with values read in
	//		 from config file, such as m_playerConfig.V below

	// Entities are created by calling EntityManager.addEntity(tag)
	std::shared_ptr<Entity> entity = m_entityManager.addEntity("player");

	// Give Entity a transform so it spawns in center of window with velocity (1,1) and angle 0
	mx = m_window.getSize().x / 2.0f;
	my = m_window.getSize().y / 2.0f;
	entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(0.0f, 0.0f), 0.0f);

	// Entity will have radius 32, 8 vertices, dark grey fill, and red outline with thickness 4
	//entity->cShape = std::make_shared<CShape>(32.0f, m_playerConfig.V, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4);
entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(5, 5, 5), sf::Color(255, 0, 0), 4);	// Added for testing

// Add an input component to the player
entity->cInput = std::make_shared<CInput>();

// Since we want this Entity to be our player, set our Game's player variables to be thie Entity,
// this goes slightly against the EntityManager paradigm, but we use the player so much it's worth it.
m_player = entity;
}

void Game::spawnEnemy()
{
	// TODO: Make sure enemy is spawned properly with the m_enemyConfig variables
	//		 the enemy must be spawned completely within the bounds of the window
	//
	std::shared_ptr<Entity> entity = m_entityManager.addEntity("enemy");

	// Give Entity a transform to spawn in random location
	float ex = rand() % m_window.getSize().x + 32;	// TODO: replace radius values with SR, set bound for right side of window
	float ey = rand() % m_window.getSize().y - 32;	// TODO: replace radius values with SR, set bound for right side of window
	float sx = rand() % 6 - 3;	// TODO: replace velocity values with SMIN and SMAX 
	float sy = rand() % 6 - 3;	// TODO: replace velocity values with SMIN and SMAX
	int vert = rand() % 8 + 3;

	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(sx, sy), 0.0f);

	// Give Enemy cShape component, this is just an example, needs work
	entity->cShape = std::make_shared<CShape>(32.0f, vert, sf::Color(rand() % 255, rand() % 255, rand() % 255), sf::Color(255, 255, 255), 4.0f);

	// Record when the most recent enemy was spawned, use this value to determine
	// when next enemy should be spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	// TODO: Spawn small enemies at location of input enemy e

	// When creating the smaller enemy, have to read values of original enemy
	// - Spawn number of small enemies equal to number of vertices of original enemy
	// - Set each small enemy to the same color as the original, but half the size
	// - Small enemies are worth double points of the original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	// TODO: Implement spawning of a bullet which travels toward target
	//		 - Bullet speed is given as a scalar speed
	//		 - Set velocity using formula in notes

	// Add bullet object to Entity vector, then add componenets
	std::shared_ptr<Entity> bullet = m_entityManager.addEntity("bullet");

	// Example of adding componenets below
	//bullet->cTransform = std::make_shared<CTransform>(target, Vec2(0, 0), 0);
	bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, target, 0);
	bullet->cShape = std::make_shared<CShape>(10, 8, sf::Color(255, 255, 255), sf::Color(255, 255, 255), 2);
	
	// Adjust velocity direction based on mouse position relative to m_player position
	if (target.x < m_player->cTransform->pos.x)
	{
		bullet->cTransform->velocity.x *= -1;
	}

	if (target.y < m_player->cTransform->pos.y)
	{
		bullet->cTransform->velocity.y *= -1;
	}
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	// TODO: implement special weapon
}

void Game::sMovement()
{
	// TODO: Implement all Entity movement in this function
	//		 - read m_player->cInput component to determine if player is moving

	// Set player velocity to {0,0} at the beginning of every frame so that
	// if keys are released player will halt movement
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

void Game::sLifespan()
{
	// TODO: Implement all lifespan functionality
	//
	//		 For all Entities
	//		 - If Entity has no component lifespan skip it
	//		 - If Entity has > 0 remaining lifespan, subtract 1
	//		 - If Entity has lifespan and is alive, scale its alpha channel properly
	//		 - If Entity has lifespan and time is up, destroy the Entity
}

void Game::sCollision()
{
	// TODO: Implement all proper collisions between entities using collision
	//		 radius not shape radius

	for (auto b : m_entityManager.getEntities("bullet"))
	{
		for (auto e : m_entityManager.getEntities("enemy"))
		{
			// Add collision detection here 
		}
	}
}

void Game::sEnemySpawner()
{
	if ((m_currentFrame - m_lastEnemySpawnTime) > 90)
	{
		spawnEnemy();
	}
}

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

	m_window.display();
}

void Game::sUserInput()
{
	// TODO: Handle user input here, not that you should only be setting the 
	//		 player's input command variables here, you should not implement
	//		 the player's movement logic here, the movement system will read
	//		 the variables you set in this function

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
				std::cout << "W key pressed" << std::endl;
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::S:
				std::cout << "S key pressed" << std::endl;
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				std::cout << "A key pressed" << std::endl;
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				std::cout << "D key pressed" << std::endl;
				m_player->cInput->right = true;
			default: break;
			}
		}

		// Trigger event when key is released
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key released" << std::endl;
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				std::cout << "S key released" << std::endl;
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				std::cout << "A key released" << std::endl;
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				std::cout << "D key released" << std::endl;
				m_player->cInput->right = false;
			default: break;
			}
		}
		;
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// remove coordinate printing for final version
				std::cout << "Left mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << std::endl;
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << std::endl;
				// TODO: Call spawnSpecialWeapon() here
			}
		}
	}
}