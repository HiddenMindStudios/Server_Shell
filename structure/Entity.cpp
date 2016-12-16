#include "stdafx.h"
#include "Entity.h"


Entity::Entity(Entity& e) : MapObject(e)
{

}

Entity::~Entity()
{

};

Entity::Entity(){

}

void Entity::update(double dt)
{
	*pos += *move;
}

//Move Vectors should NOT be normalized when you pass them!
void Entity::setMoveVector(Vector2D v)
{
	move = new Vector2D(v);
	move->normalize();
}
