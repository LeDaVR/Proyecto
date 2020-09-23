#ifndef ECS_MOVEMENT_SYSTEM_H
#define ECS_MOVEMENT_SYSTEM_H

#include "ecs/entities/entityManager.hpp"
#include "ecs/systems/unit/unitSystem.hpp"

class MovementSystem
{
	
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static void move(Unit* unit, float deltaTime);
    static void moveTowards(Unit* unit);
    static void moveRight(Unit* unit, float deltaTime);
    static void moveLeft(Unit* unit, float deltaTime);
    static void moveUp(Unit* unite, float deltaTime);
    static void moveDown(Unit* unit, float deltaTime);

	static bool between(float val, float left, float right);
	static void checkColisions(Unit* unit01, Unit* unit02, float deltaTime);
	static void checkObstacles(Unit* unit, float deltaTime);

    static float getXdis(Unit* unit);
    static float getYdis(Unit* unit);
    static float getDistance(Unit* unit);
	static void setExtremes(Unit* unit, float& up, float& down, float& left, float& right);

private:
	static bool up, down, left, right;
    explicit MovementSystem() {}
};

#endif // ECS_MOVEMENT_SYSTEM_H
