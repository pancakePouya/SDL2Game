#pragma once
#include <SDL.h>
enum class Type {
	cactus,
	ice,
	grass
};
class GameObject {
public:
	Type ObjectType;
	float x = 0;
	float y = 0;
	float oldX = 0;
	float oldY = 0;

	float weight = 0.0f;
	float Xroughness = 0.0f;
	float Yroughness = 0.0f;
	float Xfriction = 0.0f;
	//
	float Xpotentioal = 0.0f;
	float Ypotentioal = 0.0f;
	bool forcing = false;
	bool Nforcing = false;

	float Xspeed = 0.0f;
	float Yspeed = 0.0f;
	float Yvelocity = 0.0f;

	SDL_Rect rect;
	SDL_Rect cc = { rect.x - 10,rect.y - 10,rect.w + 10,rect.h + 10 };
	bool collidable = true;
	bool visible = true;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveTop = false;
	bool moveDown = false;

	bool Xmovable = true;
	bool Ymovable = true;
	
};