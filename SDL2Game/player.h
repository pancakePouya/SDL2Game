#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Block.h"
#include "Collision.h"


enum class PlayerTmove {
	real,
	game
};
enum class PlayerMove {
	Right,
	Left,
	Top,
	Down,
	Idle
};
enum class PlayerState {
	Idle,
	Walk,
	Jump,
	Fall,
	Hovering,
	Soar,
	PrepareJump,
};
class Player : public GameObject {
public:
	SDL_Rect HpBar = { 0,0,Hp,30 };
	float airK = 10;
	float gK = 30;
	int R = 0;

	bool stuck = false;
	bool stuckWall = false;

	PlayerState state = PlayerState::Idle;
	PlayerState OldState = PlayerState::Idle;
	PlayerTmove Tmove = PlayerTmove::game;
	Collision collision;

	bool onGround = true;
	bool jump = false;

	bool damaging = false;

	int Hp = 100;

	int Yvelocity = 0;
	
	int gravitySpeed = 500;

	int currentFrame = 0;
	float animationTimer = 0.0f;

	float frameDuration = 0.1f;


	int startX;

	float jumpDelay = 0.4f;

	SDL_Rect position = { 0,0,30,40 };
	bool Jump;
	Player() {
		x = 2000;
		y = 4400;
		oldX = 0;
		oldY = 0;
		rect.x = 0;
		rect.y = 0;
		rect.w = 51;
		rect.h = 51;
		Xfriction = 100;

	};
	
	void Update(float dt, const Uint8* keyboard,CollisionSide side, const std::vector<Block>& blocks,Type CT);
	void Render(SDL_Renderer* renderer, SDL_Texture* texture, float dt, float zoom);
	void Input(const Uint8* keyboard,bool inputAcc);
	void animation(float dt);
	void JumpPhysics(const Uint8* keyboard, float dt, CollisionSide side);
	void UpdateState();
	void UpdateScreenPosision(Camera& camera);
	void Move(float dt);
	void CheckCollision(Block& block);
	void Collide(CollisionSide side,GameObject& object);
	void MoveObjects(CollisionSide& side,GameObject& object,float dt);
	bool CheckGround(const std::vector<Block>& blocks);
	float Xf();
	void Damage();
	bool CheckDamage(Type& CT);
};