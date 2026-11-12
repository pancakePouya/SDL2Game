#pragma once
#include <SDL.h>
#include "Camera.h"
#include "Object.h"
#include <vector>

class Block : public GameObject {
public:

	bool onGround = false;
	float limit = 0;
	float gravitySpeed = 1000;
	bool fallable = false;

	Block();
	Block(float X, float Y, int W, int H, int Weight,Type blockType);
	void Update(float dt);
	bool CheckGround(const std::vector<Block>& blocks);
	void move(float dt);
	void Render(
		SDL_Renderer* renderer,
		Camera& camera,
		SDL_Texture* texture,
		SDL_Rect* pos,
		float zoom

	);
	void Frender(SDL_Renderer* renderer,
		int r, int g, int b,int a);
	void Shot(float dx, float dy);
	void Gravity(float deltatime);
};