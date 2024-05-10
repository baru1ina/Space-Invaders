#pragma once

using namespace sf;

class GroupOfEnemies {
	unsigned short move_pause;
	unsigned short move_timer;

	std::uniform_int_distribution<unsigned short> shoot_distribution;

	std::vector<Animation> enemy_animations;

	std::vector<Bullet> enemy_bullets;

	std::vector<Enemy> enemies;

	Sprite enemy_bullet_sprite;

	Texture enemy_bullet_texture;
public:
	GroupOfEnemies();

	bool reached_player(unsigned short player_y_) const;

	void draw(RenderWindow& window_);
	void reset(unsigned short level_);
	void update(std::mt19937_64& random_engine_);

	std::vector<Bullet>& get_enemy_bullets();

	std::vector<Enemy>& get_enemies();
};