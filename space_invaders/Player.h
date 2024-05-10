#pragma once

using namespace sf;

class Player {
private:
	bool dead;
	bool dead_animation_over;
	unsigned short health;
	unsigned short score;
	unsigned short reload_timer;
	unsigned short x;
	unsigned short y;

	std::vector<Bullet> bullets;

	Sprite bullet_sprite;
	Sprite sprite;

	Texture bullet_texture;
	Texture texture;

	Animation explosion;
public:
	Player();

	bool get_dead() const;
	bool get_dead_animation_over() const;

	unsigned short get_y() const;
	unsigned short get_health() const;
	unsigned short get_score() const;

	void die();
	void draw(RenderWindow& window_);
	void reset();
	void update(std::vector<Bullet>& enemy_bullets_, std::vector<Enemy>& enemies_);

	IntRect get_hitbox() const;
};