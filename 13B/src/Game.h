/*********************************************************************************************************
;**********
;*********************************************************************************************************
;
;PACKAGE NAME:	TODO
;
;FUNCTION:
;
;	This unit contains the definitions required to create the...TODO
;
;
;PUBLIC DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	TODO
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
;	USER DEFINED TYPES
;	------------------
;	TODO
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

#pragma once

#include <SFML/Config.hpp>
#include "Entity.h"
#include "EntityManager.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig	{ int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
private:

	EntityManager		m_entityManager;	// Vector of Entities to maintain
	
	sf::RenderWindow	m_window;			// Window we will draw to
	sf::Font			m_font;				// Font used to draw
	sf::Text			m_text;				// Score text to be drawn to screen
	sf::Text			m_pauseText;		// Pause screen text
	
	PlayerConfig		m_playerConfig;
	EnemyConfig			m_enemyConfig;
	BulletConfig		m_bulletConfig;
	
	int					m_score					= 0;
	int					m_currentFrame			= 0;
	int					m_lastEnemySpawnTime	= 0;
	
	bool				m_paused	= false;	// Whether we update game logic
	bool				m_running	= false;	// Whether game is running

	std::shared_ptr<Entity> m_player;

	// Systems Declarations
	void init(const std::string& config);		// Initialize GameState with config file path

	void sMovement();							// System: Entity position / movement update
	void sUserInput();							// System: User input			
	void sLifespan();							// System: Lifespan
	void sRender();								// System: Render / Drawing
	void sEnemySpawner();						// System: Spawn enemies
	void sCollision();							// System: Collisions

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2& target);
	void activateSpecialWeapon(std::shared_ptr<Entity> entity, int radius);

public:

	// Constructor, takes in game config
	Game(const std::string& config);	

	void run();
};