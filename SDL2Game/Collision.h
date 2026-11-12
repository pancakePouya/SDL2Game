#pragma once
#include <SDL.h>
#include "Object.h"
#include "Block.h"
enum class CollisionType {
	cactus,
	ice,
	grass,
	none
};
enum class CollisionSide {
	None,
	Top,
	Bottom,
	Left,
	Right
};


class Collision {
public:
	bool collidable = false;
	CollisionSide Check(
		GameObject& a,
		GameObject& b
	);
	Type CheckType(
		CollisionSide side,
		GameObject& a,
		GameObject& b
	);
	void MoveObjects(CollisionSide side,
		GameObject& a,
		Block& b,
		float dt);

	void Collide(
		CollisionSide side,
		GameObject& a,
		GameObject& b
	);
};