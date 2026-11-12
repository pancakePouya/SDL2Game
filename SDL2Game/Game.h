#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include <cmath>
#include "Player.h"
#include "Camera.h"
#include "Collision.h"
#include "Block.h"
#include "Text.h"

#include "Item.h"
struct CollisionInfo {
	CollisionSide side;
	Block* block;
};

class Game {
private:
	Player player;
	std::string text = "babaBarikala";
	Camera camera;
	CollisionSide sidee;
	Collision collisioN;
	Collision collider;
	CollisionSide sid;
	std::vector<Block> blocks;
	CollisionSide OldSide = CollisionSide::None;
	int screenWidth = 1080;
	int screenHeight = 500;
	Type CT = Type::grass;

	bool ac = true;
	std::string matn = " nice";
	std::string Fmatn;
	SDL_Rect pos = { 0,0,719,479 };
	float underlineDelay = 0;
	float animationDelay = 0.1f;
	int positionX = 0;
	//Event
	SDL_Event event;
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	SDL_Window* mamad = nullptr;
	SDL_Renderer* ali = nullptr;
	TTF_Font* font  = nullptr;
	SDL_Color color;
	SDL_Surface* surface = nullptr;

	//Creating Textures
	SDL_Texture* tex = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture2 = nullptr;
	SDL_Texture* texture3 = nullptr;
	SDL_Texture* lightTexture = nullptr;
	SDL_Texture* darknessTexture = nullptr;
	SDL_Texture* SwordTexture = nullptr;
	SDL_Rect fant;
	SDL_Rect mouseR;
	SDL_Rect light = {0,0,0,0};
	SDL_Rect darknessRect = { 0,0,50,50 };
	SDL_Rect swordR = { 0,0,50,50 };
	int MBW = 100;
	int MBH = 100;


	int al = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	bool a = false;
	bool chatMode = false;
	SDL_Rect norm;
	std::string guideT = "noWay";
	Uint32 lastTime;
	Uint32 CurrentTime;
	float deltatime;
	Block backGround;
	Block darkness;
	Text TEXT;
	Text guide;
	

public:
	Game();
	bool Init();
	void Input();
	void Update();
	void Render();
	void Destroy();
	bool run = true;
	void WorldSetup();
	float scale = 1;
	float Zoom = 1;
	//test1
	SDL_Rect disX = {0,0,0,0};
	SDL_Rect disY = {0,0,0,0};
	float s = 100;
	float 	normalizedDy = 1;
	float 	normalizedDx = 1;
	float L = 1;
	float newDx = 1;
	float newDy = 1;
	float mX =0;
	float mY =0;
	float playerCenterX = 0;
	float playerCenterY = 0;
	Block newB;
	std::vector<CollisionInfo> collisions;

	Item item;
	
};