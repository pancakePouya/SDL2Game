#pragma once
#include <string>
#include "Block.h"
struct Item {
public:

	int damage;
	std::string name;
	SDL_Rect rect = { 0,0,50,50 };
	Item();
	Item(int x, int y, std::string n, int d) {
		rect.x = x;
		rect.y = y;
		name = n;
		damage = d;
	}

};


