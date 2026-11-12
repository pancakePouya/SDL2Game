#include "Camera.h"
#include "Block.h"
#include <iostream>
Block::Block() {};
Block::Block(float X, float Y, int W, int H, int Weight, Type blockType) {
	x = X;
	y = Y;
	rect.x = 0;
	rect.y = 0;
	rect.w = 100;
	rect.h = 100;
	rect.w = W;
	rect.h = H;

	cc.x = rect.x - 10;
	cc.y = rect.y - 10;
	cc.w = rect.w + 10;
	cc.h = rect.h + 10;


	weight = Weight;
	Xroughness = 10;
	int Oxspeed = 0;

	ObjectType = blockType;
}
void Block::Shot(float dx, float dy) {
	Xspeed = dx*1000;
	Yvelocity = dy* -1000;
	std::cout << "dx:" << dx << "dy" << dy << std::endl;

}
void Block::move(float dt) {
	if (Xmovable) {
		x += Xspeed * dt;
	
		if (Xpotentioal != 0) {
			if (Xpotentioal > 0) {
				Xpotentioal -= 70;
				Xspeed += 70;
			}
			if (Xpotentioal < 0) {
				Xpotentioal += 70;
				Xspeed -= 70;
			}

		}

		//
		
			if (Xspeed < 0)
				Xspeed += 10;
			if (Xspeed > 0)
				Xspeed -= 10;

			
		

		if (Xspeed > 0 && Xspeed < 29)
			Xspeed = 0;
		if (Xspeed < 0 && Xspeed > -29)
			Xspeed = 0;

		if (Xpotentioal < 70)
			Xpotentioal = 0;
		if (Xpotentioal > -70)
			Xpotentioal = 0;

		//
		if (Xspeed > 600)
			Xspeed = 600;
		if (Xspeed < -600)
			Xspeed = -600;
	}
	if (Ymovable) {
		y -= Yspeed * dt;

		if (Ypotentioal != 0) {
			if (Ypotentioal > 0) {
				Ypotentioal -= 70;
				Yspeed += 70;
			}
			if (Ypotentioal < 0) {
				Ypotentioal += 70;
				Yspeed -= 70;
			}

		}

		//

		if (Yspeed < 0)
			Yspeed += 10;
		if (Yspeed > 0)
			Yspeed -= 10;




		if (Yspeed > 0 && Yspeed < 29)
			Yspeed = 0;
		if (Yspeed < 0 && Yspeed > -29)
			Yspeed = 0;

		if (Ypotentioal < 70)
			Ypotentioal = 0;
		if (Ypotentioal > -70)
			Ypotentioal = 0;

		//
		if (Yspeed > 600)
			Yspeed = 600;
		if (Yspeed < -600)
			Yspeed = -600;
	}


	
}
void Block::Frender(SDL_Renderer* renderer,
	int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);
};
void Block::Update(float dt) {
	if ((y + rect.h) > 4470)
		onGround = true;
	else
		onGround = false;
	move(dt);
	Gravity(dt);
}
void Block::Gravity(float dt) {
	y -= Yvelocity * dt;
	if (onGround) {
		Yvelocity = 0;
	}
	else {
		if(fallable)
		Yvelocity -= gravitySpeed * dt;
	}
}
bool Block::CheckGround(const std::vector<Block>& blocks) {
	SDL_Rect groundCheck;
	groundCheck.x = rect.x + 5;
	groundCheck.y = rect.y + rect.h + 1;
	groundCheck.w = rect.w - 10;
	groundCheck.h = 2;
	for (const Block& block : blocks) {
		if (SDL_HasIntersection(&groundCheck, &block.rect)) {
			return true;
		}

	}
	return false;


}
void Block::Render(
	SDL_Renderer* renderer,
	Camera& camera,
	SDL_Texture* texture,
	SDL_Rect* pos,
	float zoom

)
{
	rect.x = int(x - camera.x);
	rect.y = int(y - camera.y);


	SDL_RenderCopy(
		renderer,
		texture,
		pos,
		&rect
	);
}
