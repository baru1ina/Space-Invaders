#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>
#include <random>
#include <iostream>

#include "Animation.h"
#include "Constants.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GroupOfEnemies.h"

GroupOfEnemies::GroupOfEnemies() :
	shoot_distribution(0, ENEMY_SHOOT_CHANCE)
{
	reset(0);
	enemy_bullet_texture.loadFromFile("EnemyBullet.png");
	enemy_bullet_sprite.setTexture(enemy_bullet_texture);
	for (unsigned char i = 0; i < ENEMY_TYPES; i++)
		enemy_animations.push_back(Animation(1 + move_pause, BASE_SIZE, "Enemy" + std::to_string(static_cast<unsigned short>(i)) + ".png"));
}

bool GroupOfEnemies::reached_player(unsigned short player_y_) const {
	for (const Enemy& enemy : enemies) if (enemy.get_y() > player_y_ - 0.5f * BASE_SIZE) return 1;
	return 0;
}

std::vector<Bullet>& GroupOfEnemies::get_enemy_bullets() {
	return enemy_bullets;
}

std::vector<Enemy>& GroupOfEnemies::get_enemies() {
	return enemies;
}

void GroupOfEnemies::draw(RenderWindow& window_) {
	for (const Bullet& bullet : enemy_bullets) {
		enemy_bullet_sprite.setPosition(bullet.x, bullet.y);
		enemy_bullet_sprite.setTextureRect(sf::IntRect(BASE_SIZE * bullet.previous_x.size(), 0, BASE_SIZE, BASE_SIZE));
		window_.draw(enemy_bullet_sprite);
	}

	for (Enemy& enemy : enemies) {
		Color enemy_color = Color(255, 255, 255);
		if (0 == enemy.get_hit_timer()) {
			switch (enemy.get_type()) {
			case 0: enemy_color = Color(0, 255, 255); break;
			case 1: enemy_color = Color(255, 0, 255); break;
			case 2: enemy_color = Color(0, 255, 0); break;
			}
		}
		enemy_animations[enemy.get_type()].draw(enemy.get_x(), enemy.get_y(), window_, enemy_color);
	}
}

void GroupOfEnemies::reset(unsigned short level_) {
	unsigned char enemy_x = 0;
	unsigned char enemy_y = 0;

	std::string level_sketch = "";

	move_pause = std::max<short>(ENEMY_MOVE_PAUSE_START_MIN, ENEMY_MOVE_PAUSE_START - ENEMY_MOVE_PAUSE_DECREASE * level_);

	shoot_distribution = std::uniform_int_distribution<unsigned short>(0, ENEMY_SHOOT_CHANCE);

	for (Animation& enemy_animation : enemy_animations) enemy_animation.reset();
	enemy_bullets.clear();
	enemies.clear();
	 
	if (TOTAL_LEVELS <= level_) level_ = level_ - TOTAL_LEVELS * (level_ % TOTAL_LEVELS);

	switch (level_) {
	case 0: {
		level_sketch = "0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0";
		//level_sketch = "0";
		break;
	}
	case 1: {
		level_sketch = "0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0";
		//level_sketch = "0 0";
		break;
	}
	case 2: {
		level_sketch = "1 0 1 0 1 0 1 0 1 0 1\n0 1 0 1 0 1 0 1 0 1 0\n1 0 1 0 1 0 1 0 1 0 1\n0 1 0 1 0 1 0 1 0 1 0\n1 0 1 0 1 0 1 0 1 0 1";
		break;
	}
	case 3: {
		level_sketch = "1 1 1 1 1 1 1 1 1 1 1\n1 1 1 1 1 1 1 1 1 1 1\n1 1 1 1 1 1 1 1 1 1 1\n1 1 1 1 1 1 1 1 1 1 1\n1 1 1 1 1 1 1 1 1 1 1";
		break;
	}
	case 4: {
		level_sketch = "2 2 2 2 2 2 2 2 2 2 2\n1 1 1 1 1 1 1 1 1 1 1\n1 0 1 0 1 0 1 0 1 0 1\n0 1 0 1 0 1 0 1 0 1 0\n0 0 0 0 0 0 0 0 0 0 0";
		break;
	}
	}

	for (char sketch_character : level_sketch) {
		enemy_x++;
		switch (sketch_character) {
		case '\n': {
			enemy_x = 0;
			enemy_y++;
			break;
		}
		case '0': enemies.push_back(Enemy(0, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y))); break;
		case '1': enemies.push_back(Enemy(1, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y))); break;
		case '2': enemies.push_back(Enemy(2, BASE_SIZE * (1 + enemy_x), BASE_SIZE * (2 + enemy_y))); break;
		}
	}
}

void GroupOfEnemies::update(std::mt19937_64& random_engine_) {
	std::vector<Enemy>::iterator dead_enemies_start = enemies.end();

	if (0 == move_timer) { // двигаем энеми когда обнуляется счетчик "тактов"
		move_timer = move_pause; // move_pause - интервал
		for (Enemy& enemy : enemies) enemy.move();
		for (Animation& enemy_animation : enemy_animations) enemy_animation.change_current_frame();
	}
	else move_timer--;

	for (Enemy& enemy : enemies) {
		enemy.update();
		if (!shoot_distribution(random_engine_)) enemy.shoot(enemy_bullets);
	}

	for (auto i = enemies.begin(); i != enemies.end(); ++i) {
		if ((*i).get_health() == 0) {
			enemies.erase(i);
			break;
		}
	}

	move_pause = std::max<int>(ENEMY_MOVE_PAUSE_MIN, move_pause);

	for (Bullet& enemy_bullet : enemy_bullets) enemy_bullet.update();

	for (auto i = enemy_bullets.begin(); i != enemy_bullets.end(); ++i) {
		if ((*i).dead == 1) {
			enemy_bullets.erase(i);
			break;
		}
	}
}