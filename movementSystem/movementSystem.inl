bool MovementSystem::up;
bool MovementSystem::down;
bool MovementSystem::left;
bool MovementSystem::right;

void MovementSystem::init()
{
    //
}

void MovementSystem::update(float deltaTime)
{
    Unit* unit;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        
        unit = (Unit*)((*i)->entity);
        if(unit->transform->position == unit->transform->targetPoint)
            continue;
        
        move(unit, deltaTime);
    }
}

void MovementSystem::destroy()
{
    std::cout << "Movement System Destroyed" << std::endl;
}

void MovementSystem::move(Unit* unit, float deltaTime)
{
    if(unit->transform->isStatic) return;

    up = false;
    down = false;
    left = false;
    right = false;
    
	moveTowards(unit);
    checkObstacles(unit, deltaTime);
    if(up)
        moveUp(unit, deltaTime);
    if(down)
        moveDown(unit, deltaTime);
    if(left)
        moveLeft(unit, deltaTime);
    if(right)
        moveRight(unit, deltaTime);
}

void MovementSystem::moveTowards(Unit* unit)
{
	left = false;
	right = false;
	up = false;
	down = false;

	if (unit->transform->position.x > unit->transform->targetPoint.x)
		left = true;
	else if (unit->transform->position.x < unit->transform->targetPoint.x)
		right = true;
	if (unit->transform->position.z > unit->transform->targetPoint.z)
		up = true;
	else if (unit->transform->position.z < unit->transform->targetPoint.z)
		down = true;
}

void MovementSystem::checkObstacles(Unit* unit, float deltaTime)
{
	Unit* unit2;
	List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
	List<BaseComponent*>::iterator i;
	for (i = memory.begin(); i != memory.end(); ++i)
	{
		if ((*i)->entity->type != UNIT_ENTITY)
			continue;
		unit2 = (Unit*)((*i)->entity);
		if (unit == unit2)
			continue;

		checkColisions(unit, unit2, deltaTime);
	}
}

void MovementSystem::checkColisions(Unit* unit, Unit* unit2, float deltaTime)
{
	glm::vec3 objetive = unit->transform->targetPoint;
	glm::vec3 position = unit->transform->position;
	float up2, down2, left2, right2;

	float speed = unit->stats->velocity * deltaTime;
	float speedX = getXdis(unit) / getDistance(unit) * speed;
	float speedY = getYdis(unit) / getDistance(unit) * speed;
	setExtremes(unit2, up2, down2, left2, right2);
	if (between(position.x, left2, right2) && position.z - speedY < down2 && position.z - speedY > up2)
		up = false;

	if (between(position.x, left2, right2) && between(position.z + speedY, up2, down2))
		down = false;

	if (between(position.z, up2, down2) && position.x - speedX < right2 && position.x - speedX > left2)
		left = false;

	if (between(position.z, up2, down2) && between(position.x + speedX, left2, right2))
		right = false;
}

void MovementSystem::moveUp(Unit* unit, float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = (getYdis(unit) / getDistance(unit)) * speed;
    if(balancedspeed < getYdis(unit))
        unit->transform->position.z -= balancedspeed;
    else
        unit->transform->position.z = unit->transform->targetPoint.z;
}

void MovementSystem::moveDown(Unit* unit, float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = getYdis(unit) / getDistance(unit) * speed;
    if(balancedspeed < getYdis(unit))
        unit->transform->position.z += balancedspeed;
    else
        unit->transform->position.z = unit->transform->targetPoint.z;
}
void MovementSystem::moveRight(Unit* unit, float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = getXdis(unit) / getDistance(unit) * speed;
    if(balancedspeed < getXdis(unit))
        unit->transform->position.x += balancedspeed;
    else
        unit->transform->position.x = unit->transform->targetPoint.x;
}

void MovementSystem::moveLeft(Unit* unit,float deltaTime)
{
    float speed = unit->stats->velocity * deltaTime;
    float balancedspeed = getXdis(unit) / getDistance(unit) * speed;
    if(balancedspeed < getXdis(unit))
        unit->transform->position.x -= balancedspeed;
    else
        unit->transform->position.x = unit->transform->targetPoint.x;
}

float MovementSystem::getXdis(Unit* unit)
{
    return abs(unit->transform->position.x - unit->transform->targetPoint.x);
}

float MovementSystem::getYdis(Unit* unit)
{
    return abs(unit->transform->position.z - unit->transform->targetPoint.z);
}

float MovementSystem::getDistance(Unit* unit)
{
    float xdis = getXdis(unit);
    float ydis = getYdis(unit);
    return sqrt(pow(xdis, 2) + pow(ydis, 2));
}

void MovementSystem::setExtremes(Unit* unit, float& up, float& down, float& left, float& right)
{
    glm::vec3 size = unit->boxCollider->size;
    glm::vec3 position = unit->transform->position;

    up = position.z - size.z / 2.0f;
    down = position.z + size.z / 2.0f;
    left = position.x - size.x / 2.0f;
    right = position.x + size.x / 2.0f;

}

bool MovementSystem::between(float val, float left, float right)
{
    return val > left && val < right;
}



