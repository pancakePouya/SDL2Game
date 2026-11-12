#pragma once
#include "Game.h"
class Animate {
private:

public:
	Animate();
	int currentFrame = 0;
	float animationTimer = 0.0f;
	float frameDuration = 0.1f;
};