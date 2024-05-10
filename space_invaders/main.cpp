#include <array>
#include <chrono>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "DrawText.h"
#include "Constants.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GroupOfEnemies.h"
#include "Player.h"

int main() {
	bool game_over = 0;
	bool next_level = 0;

	unsigned short level = 0;
	unsigned short next_level_timer = NEXT_LEVEL_TRANSITION;

	std::chrono::microseconds lag(0);
	std::chrono::steady_clock::time_point previous_time;
	std::mt19937_64 random_engine;

    Event event;

	RenderWindow window(VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "Space Invaders", Style::Close);
	window.setView(View(FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));

	Sprite background_sprite;
	Sprite powerup_bar_sprite;

	Texture background_texture;
	background_texture.loadFromFile("Background.png");

	Texture font_texture;
	font_texture.loadFromFile("Font.png");

	GroupOfEnemies enemy_manager;

	Player player;

	background_sprite.setTexture(background_texture);

	previous_time = std::chrono::steady_clock::now();

	while (window.isOpen()) {

		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (FRAME_DURATION <= lag) {
			lag -= FRAME_DURATION;

			while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();

			if (player.get_dead_animation_over() == 1) game_over = 1;

			if (enemy_manager.reached_player(player.get_y())) player.die();

			if (!game_over) {
				if (!enemy_manager.get_enemies().size()) {
					if (!next_level_timer) {
						next_level = 0;
						level++;
						next_level_timer = NEXT_LEVEL_TRANSITION;
						player.reset();
						enemy_manager.reset(level);
					}
					else {
						next_level = 1;
						next_level_timer--;
					}
				}
				else {
					player.update(enemy_manager.get_enemy_bullets(), enemy_manager.get_enemies());
					enemy_manager.update(random_engine);
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				game_over = 0;

				level = 0;

				player.reset();

				enemy_manager.reset(level);

			}

			if (FRAME_DURATION > lag) {
				window.clear();

				window.draw(background_sprite);

				if (!player.get_dead()) enemy_manager.draw(window);

				player.draw(window);

				draw_text(5.0f * BASE_SIZE, 0.25f * BASE_SIZE, "score: " + std::to_string(player.get_score()), window, font_texture);
				draw_text(20.0f * BASE_SIZE, 0.25f * BASE_SIZE, "health: " + std::to_string(player.get_health()), window, font_texture);
				draw_text(0.25f * BASE_SIZE, 0.25f * BASE_SIZE, "level: " + std::to_string(level), window, font_texture);

				if (1 == game_over) draw_text(0.5f * (SCREEN_WIDTH - 5 * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE), "Game over!", window, font_texture);
				else if (1 == next_level) draw_text(0.5f * (SCREEN_WIDTH - 5.5f * BASE_SIZE), 0.5f * (SCREEN_HEIGHT - BASE_SIZE), "Next level!", window, font_texture);

				window.display();
			}
		}
	}
}