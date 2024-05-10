#include <SFML/Graphics.hpp>
#include "Animation.h"

Animation::Animation(unsigned short animation_speed_, unsigned short frame_width_, const std::string& texture_location_) :
	animation_iterator(0),
	animation_speed(std::max<unsigned short>(1, animation_speed_)),
	current_frame(0),
	frame_width(frame_width_)
{
	texture.loadFromFile(texture_location_);
	total_frames = texture.getSize().x / frame_width;
}

bool Animation::change_current_frame() {
	current_frame++;
	if (current_frame == total_frames) {
		current_frame = 0;
		return 1;
	}
	return 0;
}

bool Animation::update() {
	bool output = false;
	animation_iterator++; 
	while (animation_iterator >= animation_speed){
		animation_iterator -= animation_speed;
		current_frame++;
		if (current_frame == total_frames){
			output = true;
			current_frame = 0;
		}
	}
	return output;
}

void Animation::draw(short x_, short y_, RenderWindow& window_, const Color& color_){
	sprite.setColor(color_);
	sprite.setPosition(x_, y_);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(current_frame * frame_width, 0, frame_width, texture.getSize().y));
	window_.draw(sprite);
}

void Animation::reset() {
	animation_iterator = 0;
	current_frame = 0;
}