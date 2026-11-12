#include "Collision.h"
#include <iostream>

void Collision::MoveObjects(CollisionSide side,
	GameObject& a,
	Block& b,
	float dt) {
	if (side == CollisionSide::Left && a.moveRight) {
		if (b.Xmovable) {
			b.x = a.x + a.rect.w;
			a.Xspeed -= b.weight;
			b.Xpotentioal = a.Xspeed;
			b.forcing = true;
		}
		
	}
	else {
		b.forcing = false;
	}



	if (side == CollisionSide::Right && a.moveLeft) {
		if (b.Xmovable) {
			//b.Xspeed = a.Xspeed / 5;
			b.x = a.x - b.rect.w;
			a.Xspeed += b.weight;
			b.Xpotentioal = a.Xspeed;
			b.Nforcing = true;
		}
	}
	else {
		b.Nforcing = false;
	}

//
	if (side == CollisionSide::Top && a.moveDown) {
		if (b.Ymovable) {
			b.y = a.y + a.rect.h;
			a.Yspeed -= b.weight;
			b.Ypotentioal = a.Yspeed;
			b.forcing = true;
		}

	}
	else {
		b.forcing = false;
	}

	if (side == CollisionSide::Bottom && a.moveTop) {
		if (b.Ymovable) {
			//b.Xspeed = a.Xspeed / 5;
			b.y = a.y - b.rect.h;
			a.Yspeed += b.weight;
			b.Ypotentioal = a.Yspeed;
			b.Nforcing = true;
		}
	}
	else {
		b.Nforcing = false;
	}
}
void Collision::Collide(CollisionSide side,
	GameObject& a,
	GameObject& b) {

	switch (side) {
	case CollisionSide::Top:
		a.y = b.y - a.rect.h;
		break;
	case CollisionSide::Bottom:
		a.Yvelocity = 0;
		a.y = b.y + b.rect.h;
		break;
	case CollisionSide::Left:
		if (!a.moveRight)
			a.x = b.x - a.rect.w;
		if(!b.Xmovable)
			a.x = b.x - a.rect.w;
		break;
	case CollisionSide::Right:
		if (!a.moveLeft)
			a.x = b.x + b.rect.w;
		if (!b.Xmovable)
			a.x = b.x + b.rect.w;
		break;
	case CollisionSide::None:
		break;
	}
}
Type Collision::CheckType(
	CollisionSide side,
	GameObject& a,
	GameObject& b
) {
	if (side != CollisionSide::None)
		return b.ObjectType;
	return Type::ice;
}
CollisionSide Collision::Check(
	GameObject& a,
	GameObject& b
) {
	//if(SDL_HasIntersection(&a.cc,&b.cc))


	if (!a.collidable || !b.collidable) {
		return CollisionSide::None;
	}
	if (a.x + a.rect.w <= b.x) {
		return CollisionSide::None;

	}

	if (a.x >= b.x + b.rect.w) {
		return CollisionSide::None;

	}

	if (a.y + a.rect.h <= b.y) {
		return CollisionSide::None;
	}

	if (a.y >= b.y + b.rect.h) {
		return CollisionSide::None;
	}

	if (a.oldY + a.rect.h <= b.y)
		return CollisionSide::Top;

	if (a.oldY >= b.y + b.rect.h)
		return CollisionSide::Bottom;

	if (a.oldX >= b.x + b.rect.w)
		return CollisionSide::Right;

	if (a.oldX + a.rect.w <= b.x)
		return CollisionSide::Left;



	return CollisionSide::None;
}