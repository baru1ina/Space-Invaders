#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <array>
#include <chrono>
#include <random>

#include "Constants.h"
#include "Bullet.h"
#include "Enemy.h"

Enemy::Enemy(unsigned short type_, unsigned short x_, unsigned short y_) :
	direction(0),
	health(1 + type_),
	hit_timer(0),
	type(type_),
	x(x_),
	y(y_)
{
}

unsigned short Enemy::get_health() const {
	return health;
}

unsigned short Enemy::get_hit_timer() const {
	return hit_timer;
}

unsigned short Enemy::get_type() const {
	return type;
}

unsigned short Enemy::get_x() const {
	return x;
}

unsigned short Enemy::get_y() const {
	return y;
}

void Enemy::hit() {
	hit_timer = ENEMY_HIT_TIMER_DURATION;
}

void Enemy::move() {
	if (0 != direction) {
		if ((1 == direction && x == SCREEN_WIDTH - 2 * BASE_SIZE) || (-1 == direction && x == BASE_SIZE)) {
			direction = 0;
			y += ENEMY_MOVE_SPEED;
		}
		else {
			if (x + ENEMY_MOVE_SPEED * direction < BASE_SIZE) x = BASE_SIZE;
			else if (x + ENEMY_MOVE_SPEED * direction > SCREEN_WIDTH - 2 * BASE_SIZE) x = SCREEN_WIDTH - 2 * BASE_SIZE;
			else x = x + ENEMY_MOVE_SPEED * direction;
		}
	}
	else {
		y =  BASE_SIZE * (y / static_cast<float>(BASE_SIZE));
		if (y == BASE_SIZE * (y / static_cast<float>(BASE_SIZE))) direction = 1 == (y / BASE_SIZE) % 2 ? -1 : 1;
	}
}
 
void Enemy::shoot(std::vector<Bullet>& enemy_bullets_) {
	switch (type) {
	case 0: {
		enemy_bullets_.push_back(Bullet(ENEMY_BULLET_SPEED, x, y));
		break;
	}
	case 1: {
		enemy_bullets_.push_back(Bullet(ENEMY_BULLET_SPEED, x, y));
		enemy_bullets_.push_back(Bullet(ENEMY_BULLET_SPEED, x, y));
		break;
	}
	case 2: {
		enemy_bullets_.push_back(Bullet(ENEMY_BULLET_SPEED, x, y));
		enemy_bullets_.push_back(Bullet(ENEMY_BULLET_SPEED, x, y));
		enemy_bullets_.push_back(Bullet(ENEMY_BULLET_SPEED, x, y));
	}
	}
}

void Enemy::update() {
	if (0 < hit_timer) {
		if (1 == hit_timer) health = std::max(0, health - 1);
		hit_timer--;
	}
}

IntRect Enemy::get_hitbox() const {
	return IntRect(x + 0.25f * BASE_SIZE, y + 0.25f * BASE_SIZE, 0.5f * BASE_SIZE, 0.5f * BASE_SIZE);
}