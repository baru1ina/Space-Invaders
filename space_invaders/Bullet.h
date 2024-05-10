#pragma once

#include <array>

using namespace sf;

class Bullet {
	float real_x;
	float real_y;
	float step_y;
public:
	bool dead;
	short x;
	short y;

	std::array<short, 3> previous_x;
	std::array<short, 3> previous_y;

	Bullet(float i_step_y, short i_x, short i_y);
	void update();
	IntRect get_hitbox() const;
};
