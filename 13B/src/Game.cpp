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
	std::ifstream fin(path);	// Prof example, still need to do stuff with fin
	// If entry is for player, since we have player struct PlayerConfig declared do this
	// fin >> m_playerConfig.SR >> m_playerConfig.CR >> ...

	// Set up default windown parameters, remember that last Window variable from 
	// config file determines fullscreen vs window
	m_window.create(sf::VideoMode(1280, 720), "Psuedo-GeoWars");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run()
{
	// TODO: Add pause functionality here, some systems should function
	//		 while paused (rendering), some systems shouldn't (movement / input)
	while (m_running)
	{
		m_entities.update();

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
	std::shared_ptr<Entity> entity = m_entities.addEntity("player");

	// Give Entitey a transform so it spawns in center of window with velocity (1,1) and angle 0
	mx = m_window.getSize().x / 2.0f;
	my = m_window.getSize().y / 2.0f;
	entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);

	// Entity will have radius 32, 8 vertices, dark grey fill, and red outline with thickness 4
	entity->cShape = std::make_shared<CShape>(32.0f, m_playerConfig.V, sf::Color(10, 10, 10), sf::Color(255, 0, 0, 4.0f), 6);

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
	std::shared_ptr<Entity> entity = m_entities.addEntity("enemy");

	// Give Entity a transform to spawn in random location, this is not correct,
	// needs work
	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;
	
	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

	// Give Enemy cShape component, this is just an example, needs work
	entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

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
	auto bullet = m_entities.addEntity("bullet");

	// Example of adding componenets below
	bullet->cTransform = std::make_shared<CTransform>(target, Vec2(0, 0), 0);
	bullet->cShape = std::make_shared<CShape>(10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2);
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

	// Sample movement speed update, this needs to be re-written to update all
	// entities
	m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
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

	for (auto b : m_entities.getEntities("bullet"))
	{
		for (auto e : m_entities.getEntities("enemy"))
		{
			// Add collision detection here 
		}
	}
}

void Game::sEnemySpawner()
{
	// TODO: Code which implement enemy spawing goes here
	//
	//		 use (m_currentFrame - mLastEnemySpawnTime) to determine
	//		 how long since last enemy spawned

	// Calling spawnEnemy() without using frame formula will result in enemies
	// spawing every frame
	spawnEnemy();
}

void Game::sRender()
{
	// TODO: Change code below to draw all of the Entities
	//		 sample drawing of the player Entity that we have created
	m_window.clear();

	// Code below was added during lecture and will need to be included to draw all Entities
	for (auto& e : m_entities.getEntities())
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