#include "Game.h"



Game::Game(){}

bool Game::Init() {
	
	
	//
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);


	mamad = SDL_CreateWindow(
		"game",
		100,
		100,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN
	);
	ali = SDL_CreateRenderer(
		mamad,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	//surfaces
	font = TTF_OpenFont("fiont.ttf", 30);
	color = { 255,255,255,255 };

	surface = IMG_Load("pil.png");
	texture = SDL_CreateTextureFromSurface(ali, surface);

	SDL_FreeSurface(surface);

	surface = IMG_Load("map.png");
	texture2 = SDL_CreateTextureFromSurface(ali, surface);

	SDL_FreeSurface(surface);

	surface = IMG_Load("shokhi.png");
	texture3 = SDL_CreateTextureFromSurface(ali, surface);

	SDL_FreeSurface(surface);

	surface = TTF_RenderText_Solid(
		font,
		text.c_str(),
		color
	);
	tex = SDL_CreateTextureFromSurface(
		ali,
		surface
	);
	fant = { 40,40,surface->w,surface->h };
	SDL_FreeSurface(surface);
	surface = IMG_Load("light.png");
	lightTexture = SDL_CreateTextureFromSurface(ali, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("sword.png");
	SwordTexture = SDL_CreateTextureFromSurface(ali, surface);
	SDL_FreeSurface(surface);
	/*surface = IMG_Load("darkness.png");
	darknessTexture = SDL_CreateTextureFromSurface(ali, surface);
	SDL_FreeSurface(surface);*/
	//Errors
	std::cout << IMG_GetError() << std::endl;
	//
	mouseR = { 0,0,100,100 };
	norm = { 0,300,1080,1080 };
	TEXT = Text(matn, 10, 10);
	guide = Text(guideT, 0, 0);
	
	//
	SDL_StopTextInput();
	//deltaTime setup
	lastTime = SDL_GetTicks();
	return true;
}
void Game::Update() {
	//deltatime Updatinh...
	CurrentTime = SDL_GetTicks();

	deltatime = (CurrentTime - lastTime) / 1000.0f;
	lastTime = CurrentTime;
	TEXT.value = matn;
	//
	//Text Updating...
	TEXT.Update(font, color, ali);

	guideT = std::to_string(int(player.Hp));
	guide.value = guideT;
	
	guide.x = (player.x - camera.x);
	guide.y = ((player.y - 50) - camera.y);
	guide.Update(font, color, ali);
	//
	if (Fmatn == " a")
		run = false;

	
	
	//Collisions...

	player.Update(deltatime, keyboard, sidee, blocks, CT);
	player.stuck = false;
	collisions.clear();
	for (Block& block : blocks) {
		sidee = collider.Check(player, block);
		block.Update(deltatime);
		if (sidee == CollisionSide::None)
			continue;
		
		collisions.push_back({ sidee , &block});
	}
	player.onGround = false;
	for (const CollisionInfo& hit : collisions) {
		//Corrections come first
		collider.Collide(hit.side, player, *hit.block);
		if (hit.side == CollisionSide::Top){
			player.onGround = true;
		}
		if (hit.side == CollisionSide::Bottom)
			player.Yvelocity = 0;
		//Then, moves
		collider.MoveObjects(hit.side, player, *hit.block, deltatime);
		if (hit.side == CollisionSide::Right && !hit.block->Xmovable) {
			player.stuck = true;
		}

	}


	if (OldSide != sidee) {
		switch (sidee) {
		case CollisionSide::Top:
			std::cout << "Top" << std::endl;
			break;
		case CollisionSide::Bottom:
			std::cout << "Bottom" << std::endl;
			break;
		case CollisionSide::Left:
			std::cout << ":Left" << std::endl;
			break;
		case CollisionSide::Right:
			std::cout << "Right" << std::endl;
			break;
		case CollisionSide::None:
			break;
		}
	}

	//Positions
	camera.x = (player.x * scale) - 540;//1080 , 500
	camera.y = (player.y * scale) - 250;
	//update players camera
	player.UpdateScreenPosision(camera);
	//test...

	 playerCenterX = int(player.x - camera.x) + (player.rect.w/2);
	 playerCenterY = int(player.y - camera.y) + (player.rect.h / 2);

	

	float dx = (mX - playerCenterX);
	float dy = (mY - playerCenterY);



	L = sqrt((dx * dx) + (dy * dy));
	if (L != 0) {
		normalizedDx = dx / L;
		normalizedDy = dy / L;
	}
		newDx = normalizedDx * s;
		newDy = normalizedDy * s;
		if(keyboard[SDL_SCANCODE_9])
		std::cout << L << std::endl;//newDx ham manfi ham +

		if (L > s) {
			mouseR.x = int((playerCenterX + newDx));
			mouseR.y = int((playerCenterY + newDy));
		
		}
		
		//
		disX.x = playerCenterX;
		disX.y = playerCenterY;
		disX.w = newDx;
		disX.h = 1;

		disY.x = playerCenterX;
		disY.y = playerCenterY;
		disY.w = 1;
		disY.h = newDy;

		
}
void Game::Input() {
	while (SDL_PollEvent(&event)) {
	if (event.type == SDL_KEYDOWN) {
		if (keyboard[SDL_SCANCODE_RSHIFT]) {
			
		}

		if (event.key.keysym.sym == SDLK_F5){
			player.Hp = 100;
			player.x = 0;
			player.y = 0;
		}
		if (event.key.keysym.sym == SDLK_F1) {
			SDL_StartTextInput();
			std::cout << "TextInput started!" << std::endl;
			chatMode = true;
		}
		if (event.key.keysym.sym == SDLK_F2) {
			SDL_StopTextInput();
			std::cout << "TextInput Ended!" << std::endl;

			chatMode = false;
		}

		if (event.key.keysym.sym == SDLK_BACKSPACE && matn.size() > 1) {

			if (!matn.empty())
				matn.pop_back();
		}
		if (event.key.keysym.sym == SDLK_0) {
			run = false;
		}
		if (event.key.keysym.sym == SDLK_RETURN) {
			matn += '\n';
			Fmatn = matn;
			std::cout << Fmatn << std::endl;

		}
		
	}//<--keydown


	if (event.type == SDL_QUIT) {
		run = false;
	}
	//mouse
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			int x = event.button.x + camera.x;
			int y = event.button.y + camera.y;
			blocks.push_back(Block(mouseR.x + camera.x, mouseR.y + camera.y, MBW, MBH, 10, Type::cactus));

			std::cout << "blockLocated:\n" << "X:" << mouseR.x   << '\n' << "Y : " << player.y << std::endl;
		}	if (event.button.button == SDL_BUTTON_RIGHT) {
			blocks.emplace_back(mouseR.x + camera.x, mouseR.y + camera.y, MBW, MBH, 10, Type::cactus);
			blocks.back().fallable = true;
			blocks.back().Shot(normalizedDx,normalizedDy);
			
			

		}
	}
	if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y > 0) {
			MBW += 10;
			MBH += 10;
			mouseR.w += 10;
			mouseR.h += 10;
		}
		if (event.wheel.y < 0) {
			MBW -= 10;
			MBH -= 10;
			mouseR.w -= 10;
			mouseR.h -= 10;
		}
	}

	if (event.type == SDL_MOUSEMOTION) {
		mouseR.x = event.motion.x;
		mouseR.y = event.motion.y;
		//test
		mX = event.motion.x;
		mY = event.motion.y;
	}
	//textInput
	if (event.type == SDL_TEXTINPUT) {
		std::cout << event.text.text << std::endl;
		matn += event.text.text;
	}
	
}
	if (keyboard[SDL_SCANCODE_J]) {
		s += 1;
	}
	if (keyboard[SDL_SCANCODE_H]) {
		s -= 1;
	}
	

	player.Input(keyboard, !chatMode);
	//test
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(mamad, mouseR.x, mouseR.y);
}
void Game::Render() {
	// ۱. پاک کردن صفحه اصلی با رنگ سیاه
	SDL_SetRenderDrawColor(ali, 0, 0, 0, 255);
	SDL_RenderClear(ali);

	// ۲. رندر کردن پس‌زمینه
	backGround.Render(ali, camera, texture2, &pos, Zoom);

	// ۳. رندر کردن تمام بلاک‌ها و آپدیت دوربین آن‌ها
	for (Block& block : blocks) {
		if (block.visible)
			block.Render(ali, camera, texture3, &pos, Zoom);
	}

	blocks[2].rect.x = int(blocks[2].x - camera.x);
	blocks[2].rect.y = int(blocks[2].y - camera.y);

	// ۴. رندر کردن کاراکتر
	player.Render(ali, texture, deltatime, Zoom);

	// ۵. رندر متن‌ها و راهنمای بازی
	TEXT.Render(ali);
	guide.Render(ali);

	// ۶. مدیریت حالت چت و زیرخط (Underline)
	SDL_Rect underRect = { 0, TEXT.y, 1, 20 };
	if (chatMode) {
		underlineDelay += deltatime;
		if (underlineDelay > 1) {
			SDL_SetRenderDrawColor(ali, 255, 255, 0, 255);
			SDL_RenderFillRect(ali, &underRect);
		}
		if (underlineDelay > 2) {
			SDL_SetRenderDrawColor(ali, 255, 255, 0, 0);
			SDL_RenderFillRect(ali, &underRect);
			underlineDelay = 0;
		}
	}

	SDL_SetTextureAlphaMod(texture3, 50);
	SDL_RenderCopy(ali, texture3, nullptr, &mouseR);
	SDL_SetTextureAlphaMod(texture3, 255);

	
	SDL_SetRenderDrawColor(ali, 0, 0, 255, 0);
	SDL_RenderFillRect(ali, &disX);
	SDL_RenderFillRect(ali, &disY);

	SDL_RenderCopy(ali, SwordTexture, nullptr, &item.rect);
	
	SDL_RenderPresent(ali);
	SDL_Delay(16);
}
void Game::Destroy() {
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
	SDL_DestroyTexture(tex);
	if (font) {
		TTF_CloseFont(font);
	}
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(ali);
	SDL_DestroyWindow(mamad);
	SDL_Quit();
	
}
void Game::WorldSetup() {
	blocks.push_back(Block(200, 450, 500, 100, 50, Type::grass));
	blocks.push_back(Block(400, 600, 100, 100, 10, Type::grass));
	blocks.push_back(Block(0, 4478, 10000, 40, 50, Type::grass));
	blocks.push_back(Block(player.x, player.y -500, 50, 500, 50, Type::grass));
	blocks[2].visible = false;
	backGround = Block(0, 0, 10000, 5000, 0, Type::grass);
	backGround.collidable = false;

	blocks[3].Xmovable = false;
	/*darkness = Block(0, 0, 10000, 5000, 0, Type::grass);
	darkness.collidable = false;*/
	

}