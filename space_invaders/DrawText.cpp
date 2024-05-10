#include <SFML/Graphics.hpp>

#include "DrawText.h"

using namespace sf;

void draw_text(short x_, short y_, const std::string& text_, RenderWindow& window_, const Texture& font_texture_) {
	short character_x = x_; // местоположение на экране по икс
	short character_y = y_; // местоположение на экране по игрек

	unsigned char character_height = font_texture_.getSize().y; 
	unsigned char character_width = font_texture_.getSize().x / 96; // отделение одного символа (всего 96)

	Sprite character_sprite(font_texture_);

	for (auto i = text_.begin(); i != text_.end(); i++) {
		character_sprite.setPosition(character_x, character_y);
		character_sprite.setTextureRect(IntRect(character_width * (*i - 32), 0, character_width, character_height));
		character_x += character_width;
		window_.draw(character_sprite);
	}
}