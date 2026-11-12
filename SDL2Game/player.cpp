#include "Player.h"
#include "Collision.h"
#include "Camera.h"
#include "Object.h"


void Player::Input(const Uint8* keyboard,bool inputAcc) {
	
	if (inputAcc) {
		if (keyboard[SDL_SCANCODE_RSHIFT]) {

		}
		if (keyboard[SDL_SCANCODE_O]) {
			rect.w += 10;
		}
		if (keyboard[SDL_SCANCODE_L]) {
			rect.w -= 10;
		}
	if (keyboard[SDL_SCANCODE_U]) {
		std::cout << Yvelocity << std::endl;
	}
	if (keyboard[SDL_SCANCODE_K]) {
		x = 0;
		y = 0;
		Yvelocity = 0;
		Hp = 500;
		
	}
	
		if (keyboard[SDL_SCANCODE_D]) {
			moveRight = true;
		}
		else {
			moveRight = false;
		}
		if (keyboard[SDL_SCANCODE_A]) {
			moveLeft = true;
		}
		else {
			moveLeft = false;
		}
		if (keyboard[SDL_SCANCODE_W]) {
			moveTop = true;
		}
		else {
			moveTop = false;
		}
		if (keyboard[SDL_SCANCODE_S]) {
			moveDown = true;
		}
		else {
			moveDown = false;
		}
		if (keyboard[SDL_SCANCODE_SPACE]) {
			jump = true;
		}
		else {
			jump = false;
		}
	}//<-- move
}

void Player::Move(float dt) {
	
	
	y -= Yspeed * dt;
	x += Xspeed * dt;
	
	//
	if (Tmove == PlayerTmove::real) {
		if (onGround) {
			if (moveRight)
				Xspeed += 60;
			if (moveLeft)
				Xspeed -= 60;
			//restriction
			if (Xspeed < 0)
				Xspeed += 30;
			if (Xspeed > 0)
				Xspeed -= 30;
		}
		else {
			if (moveRight)
				Xspeed += 10;
			if (moveLeft)
				Xspeed -= 10;
			//restriction
			if (Xspeed < 0)
				Xspeed += 100 * dt;
			if (Xspeed > 0)
				Xspeed -= 100 * dt;
		}
		if (!moveLeft && !moveRight) {
			if (Xspeed > 0 && Xspeed < 30)
				Xspeed = 0;
			if (Xspeed < 0 && Xspeed > -30)
				Xspeed = 0;
		}
		//Xspeed Restriction
		if (Xspeed > 600)
			Xspeed = 600;
		if (Xspeed < -600)
			Xspeed = -600;
	}
		if (Tmove == PlayerTmove::game) {
				if (moveRight)
					Xspeed = 350;
				if (moveLeft)
					Xspeed = -350;
				if (!moveRight && !moveLeft)
					Xspeed = 0;
				if (moveTop)
					Yspeed = 350;
				if (moveDown)
					Yspeed = -350;
				if (!moveTop && !moveDown)
					Yspeed = 0;
	}
	
};
void Player::UpdateState() {
	
	if (jump && onGround) {
		state = PlayerState::Jump;
	}
	else  if (onGround) {
		if (moveRight || moveLeft) {
			state = PlayerState::Walk;
		}
		else { state = PlayerState::Idle; }
	}

	if (state != OldState) {
		currentFrame = 0;
		OldState = state;

	}
}
void Player::MoveObjects(CollisionSide& side,GameObject& object,float dt) {
	//age be chapesh khodram va ham zaman dashtam be samtesh miraftam herekatesh bede
	if (side == CollisionSide::Left && moveRight) {
		object.Xfriction = object.weight * object.Xroughness;
		float reduceSpeed = Xspeed - object.Xfriction;
		Xspeed -= object.weight;
		object.x = x + rect.w;
	}
	
	//وقتی به یه چیزی برخورد میکنی میگم خب بستگی
	//داره که به چه چیزی با چه جرمی برخورد کنی
	// ولی ما جرم همه چیز رو اینحا کم میگیریم 
	// پس همه چیز باید حرکت کنه 
	// وقتی یه جیزیو حرکت میدم سرعت دستمم کم میشه ولی 
	// سرعتم با سرعت اون جسم برا برمیشه
	// 
	// 
	//

	if (side == CollisionSide::Right && moveLeft) {
		object.Xfriction = object.weight * object.Xroughness;
		float reduceSpeed = Xspeed - object.Xfriction;
		object.x = x - object.rect.w ;
	}

}
void Player::Collide(CollisionSide side, GameObject& object){

	switch (side) {
	case CollisionSide::Top:
		y = object.y - rect.h;
		break;
	case CollisionSide::Bottom:
		Yvelocity = 0;
		y = object.y + object.rect.h;
		break;
	case CollisionSide::Left:
		if (!moveRight)
			x = object.x - rect.w;
		
		break;
	case CollisionSide::Right:
		if(!moveLeft)
		x = object.x + object.rect.w;
		Xspeed += object.weight;
		break;
	case CollisionSide::None:
		break;
	}
}
void Player::Render(SDL_Renderer* renderer, SDL_Texture* texture, float dt, float zoom)
{


	SDL_RenderCopy(
		renderer,
		texture,
		&position,
		&rect
	);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &HpBar);
}
void Player::animation(float deltatime)
{
	animationTimer += deltatime;

	if (animationTimer > frameDuration)
	{
		animationTimer = 0;
		currentFrame++;
	}


	switch (state) {
	case PlayerState::Jump:
		position.y = 47;
		startX = 402;
		frameDuration = 0.15f;
		if (currentFrame > 4) {
			currentFrame = 0;
		}
		break;
	case PlayerState::Walk:
		position.y = 53;
		startX = 81;
		frameDuration = 0.1f;
		if (currentFrame > 5) {
			currentFrame = 0;
		}
		break;
	case PlayerState::Idle:
		position.y = 295;
		startX = 83;
		frameDuration = 0.3f;
		if (currentFrame > 3) {
			currentFrame = 0;
		}
		break;
	case PlayerState::Fall:
		position.y = 47;
		startX = 602;
		frameDuration = 0.1f;
		if (currentFrame > 2) {
			currentFrame = 2;
			frameDuration = 1000;
		}
		break;
	}


	position.x = startX + (currentFrame * 40);

}
void Player::JumpPhysics(const Uint8* keyboard, float dt, CollisionSide side) {

	if (keyboard[SDL_SCANCODE_P]) {
		Yvelocity += 60;
	}
	if (stuck) { 
		if (jump) {
			Yvelocity = 500;
			stuck = false;
		}
		else {
			Yvelocity = 0;
		}

	}else{

		if (onGround) {
			if (jump) {
				Yvelocity = 500;
				onGround = false;
			}
			else {
				Yvelocity = 0;
			}
		}
		else {

			Yvelocity -= gravitySpeed * 3 * dt;
		}
	}
	
	y -= Yvelocity * dt;
};
void Player::UpdateScreenPosision(Camera& camera) {
	rect.x = int(x - camera.x);
	rect.y = int(y - camera.y);
}
bool Player::CheckGround(const std::vector<Block>& blocks) {
	SDL_Rect groundCheck;
	groundCheck.x = rect.x + 5;
	groundCheck.y = rect.y + rect.h ;
	groundCheck.w = rect.w - 10;
	groundCheck.h = 1;
	for (const Block& block : blocks) {
		if (SDL_HasIntersection(&groundCheck, &block.rect)) {
			return true;
		}

	}
	return false;

	
 }
bool Player::CheckDamage(Type& CT) {
	if (CT == Type::cactus)
		return true;
	return false;
}
void Player::Damage() {
	if (Hp > 0) {
		Hp -= 10;
		std::cout << "damagin" << std::endl;
	}
	
}
void Player::Update(float dt, const Uint8* keyboard,CollisionSide side,const std::vector<Block>& blocks,Type CT) {
	HpBar.w = Hp;
	oldX = x;
	oldY = y;
	
	damaging = CheckDamage(CT);
	if (damaging)
		Damage();

	Move(dt);

	UpdateState();
	animation(dt);
}