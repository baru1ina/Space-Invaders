#include <SFML/Graphics.hpp>
#include <cmath>

#include "Constants.h"
#include "Bullet.h"

Bullet::Bullet(float i_step_y, short i_x, short i_y) :
	dead(0),
	real_x(i_x),
	real_y(i_y),
	step_y(i_step_y),
	x(i_x),
	y(i_y)
{
	previous_x.fill(x);
	previous_y.fill(y);
}

void Bullet::update() {
	if (!dead) {
		real_y += step_y;
		for (auto i = 0; i < previous_x.size() - 1; i++) {
			previous_x[i] = previous_x[1 + i];
			previous_y[i] = previous_y[1 + i];
		}
		previous_x[previous_x.size() - 1] = x;
		previous_y[previous_y.size() - 1] = y;
		y = round(real_y);

		if (x <= -BASE_SIZE || y <= -BASE_SIZE || SCREEN_HEIGHT <= y || SCREEN_WIDTH <= x) dead = 1;
	}
}

sf::IntRect Bullet::get_hitbox() const {
	return sf::IntRect(x + 0.375f * BASE_SIZE, y + 0.375f * BASE_SIZE, 0.25f * BASE_SIZE, 0.25f * BASE_SIZE);
}