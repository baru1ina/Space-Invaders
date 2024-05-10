#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Constants.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

Player::Player() :
	explosion(EXPLOSION_ANIMATION_SPEED, BASE_SIZE, "Explosion.png"),
	health(3),
	score(0)
{
	reset();

	bullet_texture.loadFromFile("PlayerBullet.png");
	texture.loadFromFile("Player.png");

	bullet_sprite.setTexture(bullet_texture);
	sprite.setTexture(texture);
}

bool Player::get_dead() const {
	return dead;
}

bool Player::get_dead_animation_over() const {
	return dead_animation_over;
}

unsigned short Player::get_y() const {
	return y;
}

unsigned short Player::get_health() const {
	return health;
}

unsigned short Player::get_score() const {
	return score;
}

void Player::die() {
	dead = 1;
}

void Player::draw(RenderWindow& window_) {
	if (!dead) {
		sprite.setPosition(x, y);
		sprite.setTextureRect(IntRect(BASE_SIZE*3, 0, BASE_SIZE, BASE_SIZE));
		for (const Bullet& bullet : bullets) {
			bullet_sprite.setPosition(bullet.x, bullet.y);
			window_.draw(bullet_sprite);
		}
		window_.draw(sprite);
	}
	else if (!dead_animation_over) explosion.draw(x, y, window_, Color(255, 36, 0));
}

void Player::reset() {
	dead = 0;
	dead_animation_over = 0;
	if (health == 0) score = 0;
	health = 3;
	reload_timer = 0;

	x = 0.5f * (SCREEN_WIDTH - BASE_SIZE);
	y = SCREEN_HEIGHT - 2 * BASE_SIZE;

	bullets.clear();
	explosion.reset();
}

void Player::update(std::vector<Bullet>& enemy_bullets_, std::vector<Enemy>& enemies_) {
	if (!dead) {
		if (Keyboard::isKeyPressed(Keyboard::Left)) x = std::max<int>(x - PLAYER_MOVE_SPEED, BASE_SIZE);
		if (Keyboard::isKeyPressed(Keyboard::Right)) x = std::min<int>(PLAYER_MOVE_SPEED + x, SCREEN_WIDTH - 2 * BASE_SIZE);
		if (0 == reload_timer) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				reload_timer = RELOAD_DURATION;
				bullets.push_back(Bullet(-PLAYER_BULLET_SPEED, x, y));
			}
		}
		else reload_timer--;

		for (Bullet& enemy_bullet : enemy_bullets_) {
			if (get_hitbox().intersects(enemy_bullet.get_hitbox())) {
				if (health > 1) {
					health--;
				}
				else {
					health--;
					dead = 1;
				}
				enemy_bullet.dead = 1;
				break;
			}
		}
	}
	else if (!dead_animation_over) dead_animation_over = explosion.update();

	for (Bullet& bullet : bullets) bullet.update();

	for (Enemy& enemy : enemies_) {
		for (Bullet& bullet : bullets) {
			if (0 == bullet.dead && 1 == enemy.get_hitbox().intersects(bullet.get_hitbox())) {
				bullet.dead = 1;
				score += 100;
				enemy.hit();
				break;
			}
		}
	}

	for (auto i = bullets.begin(); i != bullets.end(); ++i) {
		if ((*i).dead == 1) {
			bullets.erase(i);
			break;
		}
	}
}

IntRect Player::get_hitbox() const {
	return IntRect(x + 0.125f * BASE_SIZE, y + 0.125f * BASE_SIZE, 0.75f * BASE_SIZE, 0.75f * BASE_SIZE);
} 