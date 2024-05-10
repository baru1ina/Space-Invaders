#pragma once

using namespace sf;

class Enemy {
    char direction;
	unsigned short health;
	unsigned short hit_timer;
	unsigned short type;
	unsigned short x;
	unsigned short y;
public:
	Enemy(unsigned short type_, unsigned short x_, unsigned short y_);

	unsigned short get_health() const;
	unsigned short  get_hit_timer() const;
	unsigned short get_type() const;
	unsigned short get_x() const;
	unsigned short get_y() const;

	void hit();
	void move();
	void shoot(std::vector<Bullet>& enemy_bullets_);
	void update();

	IntRect get_hitbox() const;
};